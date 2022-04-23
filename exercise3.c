#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define DIM 20

typedef char stringa[80];
typedef stringa strvett[DIM];

void gestoresequenza(int N, strvett vett);
int gest_stato(int S, int pid);

int main(int argc, char **argv){
	int pid, ncom, stato, i;
	strvett vstr;
	ncom = argc-1;
	
	for(i = 0; i < ncom; i++){
		strcpy(vstr[i], argv[i+1]);
	}
	
	gestoresequenza(ncom-1, vstr);
	pid = wait(&stato);
	gest_stato(stato, pid);
}

void gestoresequenza(int N, strvett vett){
	int pid;
	pid = fork();
	if(pid == 0){
		if(N==-1){ //processo foglia
			printf("\nProcesso finale %d\n", getpid());
			exit(0);
		}else{
			printf("\nProcesso %d per comando %s\n", getpid(), vett[N]);
			gestoresequenza(N-1, vett);
			execlp(vett[N], vett[N], (char*)0);
			perror("\nexec fallita\n");
			exit(-1);
		}
	}
}

int gest_stato(int S, int pid){
	printf("Terminato figlio %d\n", pid);
	if(WIFEXITED(S)){
		printf("Terminazione volontaria con stato %d\n", WEXITSTATUS(S));			
	}else{
		printf("Terminazione involontaria con stato %d\n", WTERMSIG(S));
	}
}
