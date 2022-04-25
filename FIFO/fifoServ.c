#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define DIM 32


void main(int argc, char** argv){
	if(argc != 3){
		printf("Numero di argomenti diverso da 3");
		exit(EXIT_FAILURE);
	}
	
	int fdin, pid, stato;
	char comando[DIM];
	char fileout[DIM];
	
	if((fdin = mkfifo("server.in", 0777)) < 0){	//creazione FIFO
		perror("La fifo esiste già");
	}
	if((fdin = open("server.in", O_RDONLY)) < 0){	//apertura FIFO in modalità sola lettura
		perror("Errore nell'apertura della fifo");
		exit(EXIT_FAILURE);
	}
	read(fdin, comando, DIM);	//lettura comando
	read(fdin, fileout, DIM);	//lettura nome del file
	close(fdin);
	
	pid=fork();
	if(pid == 0){
		close(1);
		fdin = creat(fileout, 0777); //ridirezione output perché lo mette al posto 1 nella tabella dei file attivi
		execlp(comando, comando, (char*)0);
		perror("Errore nella exec");
		exit(-1);
	}else{
		sleep(2);
		wait(&stato);
		printf("Stato del figlio %d\n", stato>>8);
		exit(0);
	}
	
	
}
