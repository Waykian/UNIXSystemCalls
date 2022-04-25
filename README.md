# System calls in UNIX
Projects containing the use of system calls in UNIX, entirely written in C. Creation of children, pipes, directories, FIFOs, etc.

Headers:
* #include <sys/types.h>
* #include <dirent.h>
* #include <fcntl.h>
* #include <stdlib.h>
* #include <stdio.h>
* #include <string.h>
* #include <unistd.h>
* #include <sys/wait.h>
* #include <signal.h>

Examples of system calls used:
* fork();
* wait();
* pause();
* alert();
* mkfifo();
* open();
* close();
* signal();
* exit();
* write();
* read();

To create the C source code
```
gcc filename.c -o filename
```
To run the C code
```
./filename arguments...
```
