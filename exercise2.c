#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv){
	int pid[argc-1];
	int stato, atteso;
	
	for(int i = 1; i < argc;i++){
		pid[i-1] = fork();
		if(pid[i-1]<0){
			perror("Fork\n");
			exit(1);
		}
		if(pid[i-1] == 0){
			printf("Comando %d:\n", i);
			execlp(argv[i], argv[i], (char*)0);
			perror("Errore\n");
			exit(-1);
		}
	}
	for(int i = 1; i< argc; i++){
		pid[i-1] = wait(&stato);
		printf("Terminato processo %d\n", pid[i-1]);
		if(WIFEXITED(stato)){
			printf("Terminazione volontaria del processo %d con stato %d\n", pid[i-1], WEXITSTATUS(stato));			
		}
		if(WIFSIGNALED(stato)){
			printf("Terminazione involontaria del processo %d con stato %d\n", pid[i-1], WTERMSIG(stato));
		exit(1);
		}
	}

	return 0;
}
