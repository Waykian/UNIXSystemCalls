#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define DIM 20
#define MAXP 10

typedef char stringa[80];
typedef stringa strvett[DIM];
strvett vstr;
void gest_stato(int S, int pid);
void figlio(int i);

int main(int argc, char **argv){
	int pid[MAXP], ncom, stato, i;
	ncom = argc-1;
	for(i = 0; i < ncom; i++){
		strcpy(vstr[i], argv[i+1]);
	}
	for(i = 0; i < ncom; i++){
		if((pid[i]=fork())==0){
			figlio(i);
		}
	}
	for(i = 0; i < ncom; i++){
		pid[i] = wait(&stato);
		gest_stato(stato, pid[i]);
	}
}

void figlio(int i){
	printf("\nProcesso %d per comando %s", getpid(), vstr[i]);
	execlp(vstr[i], vstr[i], (char*)0);
	perror("\nexec fallita: ");
	exit(-1);
}

void gest_stato(int S, int pid){
	printf("Terminato processo figlio numero %d", pid);
	if(WIFEXITED(S)){
		printf("Terminazione volontaria con stato %d\n", WEXITSTATUS(S));			
	}else{
		printf("Terminazione involontaria con stato %d\n", WTERMSIG(S));
		exit(1);
	}
}
