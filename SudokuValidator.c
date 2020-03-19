#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define ROW 9
#define COLUMN 9
#define true 1

char sudoku[ROW][COLUMN];
int vc, vr;

/* Map string to bidimensinal array representing sudoku */
void  map_sudoku(int fd) {
    omp_set_nested(true);
    omp_set_num_threads(9);
    struct stat stat_s;
    int status = fstat(fd, &stat_s); /* Get the file info, including size*/
    int size = stat_s.st_size;
    
    /* Read all data of file to f*/
    char *f = (char *) mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    /* Map file data to ROW x COLUMN matrix*/
    int string_counter = 0;
    int a[9];
    #pragma omp parallel for private(a)
    for(int i = 0; i < ROW; i++){
        #pragma omp parallel for
        for(int j = 0; j < COLUMN; j++){
            sudoku[i][j] = f[string_counter];
            string_counter++;
        }
    }
}

/*
Verify that all rows are valid
returns 0 if valid -1 otherwise
*/
int verify_rows() {
    omp_set_nested(true);
    omp_set_num_threads(9);
    int a[9];
    int valid = 0;
    #pragma omp parallel for private(a)
    for(int i = 0; i < ROW; i++) {
        /* Verify row has numbers from 1 to 9*/
        char string[] = "123456789";
        char* s;
        for(s=&string[0]; *s != '\0'; s++) {
            int found = 0;
            int counter = 0;
            while(found == 0 && counter < COLUMN){
                if(sudoku[i][counter] == *s) found = 1;
                counter++;
            }
            if(found == 0) valid= -1;
        }
    }
    return valid;
}

int verify_rows_args(char temp[ROW][COLUMN]) {
    omp_set_nested(true);
    omp_set_num_threads(9);
    int a[9];
    int valid = 0;
    #pragma omp parallel for private(a)
    for(int i = 0; i < ROW; i++) {
        /* Verify row has numbers from 1 to 9*/
        char string[] = "123456789";
        char* s;
        for(s=&string[0]; *s != '\0'; s++) {
            int found = 0;
            int counter = 0;
            while(found == 0 && counter < COLUMN){
                if(temp[i][counter] == *s) found = 1;
                counter++;
            }
            if(found == 0) valid = -1;
        }
    }
    return valid;
}

/*
Verify that all columns are valid
returns 0 if valid -1 otherwise
*/
int verify_columns() {
    omp_set_nested(true);
    omp_set_num_threads(9);
    int a[9];
    int valid = 0;
    #pragma omp parallel for private(a)
    for(int i = 0; i < COLUMN; i++) {
        /* Verify row has numbers from 1 to 9*/
        char string[] = "123456789";
        char* s;
        for(s=&string[0]; *s != '\0'; s++) {
            int found = 0;
            int counter = 0;
            while(found == 0 && counter < ROW){
                if(sudoku[counter][i] == *s) found = 1;
                counter++;
            }
            if(found == 0) valid = -1;
        }
    }
    return valid;
}

int verify_sub_matrix() {
    omp_set_nested(true);
    omp_set_num_threads(3);
    char temp_sudoku[ROW][COLUMN];
    int rc=0, cc=0;
    int a[9];
    #pragma omp parallel for private(a)
    for(int nr=0; nr<3; nr++) {
        #pragma omp parallel for
        for(int nc=0; nc<3; nc++) {
            #pragma omp parallel for
            for(int i=0; i<3; i++) {
                #pragma omp parallel for
                for(int j=0; j<3; j++) {
                    temp_sudoku[rc][cc] = sudoku[i+(nr*3)][j+(nc*3)];
                    cc++;
                }
            }
            cc=0; rc++;
        }
    }
    return verify_rows_args(temp_sudoku);
}

void *vcol_runner() {
    printf("vcol thread id: %d\n", syscall(SYS_gettid));
    vc = verify_columns();
    pthread_exit(0);
}

void *vrow_runner() {
    printf("vrow thread id: %d\n", syscall(SYS_gettid));
    vr = verify_rows();
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    omp_set_num_threads(1);
    
    /* Verify sudoku file is being passed */
    if(argc < 2) {
        printf("No sudoku file was passed"); return 1;
    }

    /* Load sudoku to memory */
    int input;
    if( (input = open(argv[1], O_RDONLY) ) < 0) {
		perror("Error opening source file");
		return 1;
	} else {
        map_sudoku(input);

        /* Get pid info*/
        pid_t parent_pid = getpid();
        
        int f = fork();
        if(f < 0) {
            perror("Error forking!");
            return 1;
        } else if(f == 0) { // Child process
            
            /* Convert pid to string */
            char p_pid[6];
            sprintf(p_pid, "%d", (int) parent_pid);
            execlp("ps","ps","-p", p_pid, "-lLf", NULL);

        } else { // Parent process

            /* Create and join column verify thread */
            pthread_t ver_cols;
            if(pthread_create(&ver_cols, NULL, vcol_runner, NULL)){ perror("Error creating thread"); return 1;}
            if(pthread_join(ver_cols, NULL)) { perror("Error joining thread"); return 1; }

            printf("main thread: %d\n", syscall(SYS_gettid));
            printf("waiting for child\n");
            usleep(30000);
            printf("children finished\n");

            /* Create and join row verify thread */
            pthread_t ver_row;
            if(pthread_create(&ver_row, NULL, vrow_runner, NULL)){ perror("Error creating thread"); return 1;}
            if(pthread_join(ver_row, NULL)) { perror("Error joining thread"); return 1; }

            /* Display if solution is valid or not */
            if(vr == 0 && vc == 0) {
                printf("--- * Valid solution * ---\n");
            } else {
                printf("--- * Invalid solution * ---\n");
            }
        }

        /* second fork */
        int ff = fork();
        if(ff == 0) { // Child process
            /* Convert pid to string */
            char p_pid[6];
            sprintf(p_pid, "%d", (int) parent_pid);
            execlp("ps","ps","-p", p_pid, "-lLf", NULL);
        } else {
            printf("waiting for child\n");
            usleep(30000);
            printf("children finished\n");
            return 0;
        }
    }
}