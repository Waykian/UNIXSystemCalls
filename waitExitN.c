#define N 100
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int pid[N], status, i, k; 
	for(i = 0; i < N; i++){
		pid[i] = fork();
		if(pid[i] == 0){
			printf("Figlio numero %d con pid %d\n", i+1, getpid());
			exit(0);
		}
	}
	
	for(i = 0; i < N; i++){
		k = wait(&status);
		if(WIFEXITED(status)){
			printf("Terminazione volontaria del processo %d con stato %d\n", k, WEXITSTATUS(status));
		}else if(WIFSIGNALED(status)){
			printf("Terminazione involontaria del processo %d con stato %d\n", k, WTERMSIG(status));
		}
	}
	return 0;
}
