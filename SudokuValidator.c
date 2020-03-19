#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define ROW 9
#define COLUMN 9

char sudoku[ROW][COLUMN];

/* Map string to bidimensinal array representing sudoku */
void  map_sudoku(int fd) {
    struct stat stat_s;
    int status = fstat(fd, &stat_s); /* Get the file info, including size*/
    int size = stat_s.st_size;
    
    /* Read all data of file to f*/
    char *f = (char *) mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    /* Map file data to ROW x COLUMN matrix*/
    int string_counter = 0;
    for(int i = 0; i < ROW; i++){
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
            if(found == 0) return -1;
        }
    }
    return 0;
}

/*
Verify that all columns are valid
returns 0 if valid -1 otherwise
*/
int verify_columns() {
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
            if(found == 0) return -1;
        }
    }
    return 0;
}


int main(int argc, char *argv[]) {
    
    /* Verify sudoku file is being passed */
    if(argc < 2) {
        printf("No sudoku file was passed"); return 1;
    }

    int input;
    if( (input = open(argv[1], O_RDONLY) ) < 0) {
		perror("Error opening source file");
		return 1;
	} else  {
        map_sudoku(input);
        //int v_rows = verify_rows();
        //int v_cols = verify_columns();
    }
}   