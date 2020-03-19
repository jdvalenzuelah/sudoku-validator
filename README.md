# Laboratorio #5
## Autores
- Josue Valenzuela

##### Ejemplo archivo de entrada
```bash
$ cat sudoku 
624539187519728634837614295143865729958247361762391458371956842496182573285473916
```

##### Compilacion:
```bash
$ gcc -lpthread -o main.o SudokuValidator.c
```
##### Ejecucion
```bash
$ chmod +x main.o
$ ./main.o sudoku
```
##### Salida
```
vcol thread id: 25948
main thread: 25946
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   25946    4725   25946  0    1  80   0 - 19076 -      20:58 pts/1    00:00:00 ./main.o sudoku
children finished
vrow thread id: 25949
--- * Valid solution * ---
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   25946    4725   25946  0    1  80   0 - 19076 -      20:58 pts/1    00:00:00 ./main.o sudoku
children finished
```

##### Compilacion con Paralelización:
```bash
$ gcc -lpthread -fopenmp -o main.o SudokuValidator.c
```

##### Ejecucion
```bash
$ chmod +x main.o
$ ./main.o sudoku
```
##### Salida
```
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   26972    4725   26972  0    5  80   0 - 58029 -      21:16 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   26972    4725   26973  0    5  80   0 - 58029 -      21:16 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   26972    4725   26974  0    5  80   0 - 58029 -      21:16 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   26972    4725   26975  0    5  80   0 - 58029 -      21:16 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   26972    4725   26977  0    5  80   0 - 58029 -      21:16 pts/1    00:00:00 ./main.o sudoku
vcol thread id: 26977
main thread: 26972
waiting for child
children finished
vrow thread id: 26981
--- * Invalid solution * ---
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   26972    4725   26972  0    4  80   0 - 80586 -      21:16 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   26972    4725   26973  0    4  80   0 - 80586 -      21:16 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   26972    4725   26974  0    4  80   0 - 80586 -      21:16 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   26972    4725   26975  0    4  80   0 - 80586 -      21:16 pts/1    00:00:00 ./main.o sudoku
children finished
```

##### Salida con `omp_set_num_threads(1)`
```
vcol thread id: 27509
main thread: 27507
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   27507    4725   27507  0    1  80   0 - 25287 -      21:27 pts/1    00:00:00 ./main.o sudoku
children finished
vrow thread id: 27513
--- * Valid solution * ---
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   27507    4725   27507  0    1  80   0 - 25287 -      21:27 pts/1    00:00:00 ./main.o sudoku
children finished
```

##### Salida con `schedule(dynamic)`
```
vcol thread id: 27782
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   27780    4725   27780  0    5  80   0 - 25262 -      21:29 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   27780    4725   27782  0    5  80   0 - 25262 -      21:29 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   27780    4725   27783  0    5  80   0 - 25262 -      21:29 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   27780    4725   27784  0    5  80   0 - 25262 -      21:29 pts/1    00:00:00 ./main.o sudoku
1 R davalen+   27780    4725   27785  0    5  80   0 - 25262 -      21:29 pts/1    00:00:00 ./main.o sudoku
main thread: 27780
waiting for child
children finished
vrow thread id: 27786
--- * Valid solution * ---
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   27780    4725   27780  0    1  80   0 - 25288 -      21:29 pts/1    00:00:00 ./main.o sudoku
children finished
```

##### Salida sin `schedule(dynamic)`
```
vcol thread id: 28167
main thread: 28157
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   28157    4725   28157  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28158  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28159  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28160  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28161  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28162  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28163  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28164  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28165  0    9  80   0 - 238287 -     21:34 pts/1    00:00:00 ./main.o sudoku
children finished
vrow thread id: 28176
--- * Invalid solution * ---
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   28157    4725   28157  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28158  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28159  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28160  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28161  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28162  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28163  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28164  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28157    4725   28165  0    9  80   0 - 287439 -     21:34 pts/1    00:00:00 ./main.o sudoku
children finished
```

##### Salida sin `omp_set_nested(true);`
```
vcol thread id: 28508
main thread: 28426
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   28426    4725   28426  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28427  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28428  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28429  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28430  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28431  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28432  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28433  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28434  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
children finished
vrow thread id: 28517
--- * Invalid solution * ---
waiting for child
F S UID          PID    PPID     LWP  C NLWP PRI  NI ADDR SZ WCHAN  STIME TTY          TIME CMD
0 S davalen+   28426    4725   28426  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28427  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28428  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28429  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28430  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28431  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28432  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28433  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
1 S davalen+   28426    4725   28434  0    9  80   0 - 533200 -     21:37 pts/1    00:00:00 ./main.o sudoku
children finished
```