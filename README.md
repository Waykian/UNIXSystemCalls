# System calls in UNIX
Project regarding system calls in UNIX for the "Operating Systems" course of the University of Bologna.
Implementation of pipes, directories, FIFO, files, creation of children from main process, etc.
Entirely written in C on a Kali Linux virtual machine (VirtualBox), and GCC compiler.

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
