#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int status; 
	int pid = fork();
	if(pid == 0){
		printf("Figlio\n");
		exit(0);
	}
	if(pid>0){
		printf("Padre\n");
		pid = wait(&status);
		if(WIFEXITED(status)){
			printf("Processo %d terminato volontariamente con stato di terminazione %d\n", pid, WEXITSTATUS(status));
		}else if(WIFSIGNALED(status)){
			printf("Processo %d terminato involontariamente con stato di terminazione %d\n", pid, WTERMSIG(status));
		}
	}
	if(pid<0){
		printf("Errore nella creazione del figlio\n");
	}
	return 0;
}
