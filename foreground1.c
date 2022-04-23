#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
	int stato, atteso, pid;
	char st[80];
	for(;;){
		if((pid = fork())<0){
			perror("Fork\n");
			exit(1);
		}
		if(pid==0){	//figlio che esegue i comandi
			printf("Inserire il comando da eseguire:\n");
			scanf("%s", st);
			execlp(st, st, (char*)0);
			perror("Errore\n");
			exit(0);
		}else{	//padre
			atteso = wait(&stato);
			//sincronizzazione figlio
			printf("Eseguire altro comando?\n");
			scanf("%s", st);
			if(strcmp(st, "si")){
				exit(0);
			}
		}
	}

	
}
