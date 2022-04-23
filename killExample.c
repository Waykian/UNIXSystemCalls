#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cont = 0;

void handler(int sig){
	printf("Processo %d: ricevuti %d segnali %d\n", getpid(), cont++, sig);
	//loop
}

int main(){
	signal(SIGUSR1, handler);
	//signal(SIGCHLD, handler2);
	int pid;
	pid = fork();
	if(pid == 0){
		for( ; ; );
	}else{
		for( ; ; ){
			kill(pid, SIGUSR1);
		}
	}
	return 0;
}
