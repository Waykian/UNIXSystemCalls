#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int);

int main(){
	if(signal(SIGUSR1, handler) == SIG_ERR){
		perror("Prima signal non riuscita \n");
	}
	if(signal(SIGUSR2, handler) == SIG_ERR){
		perror("Seconda signal non riuscita \n");
	}
	for( ; ; );
}

void handler(int sig){
	if(sig == SIGUSR1) {
		printf("ricevuto sigusr1\n");
	}else if (sig == SIGUSR2) {
		printf("ricevuto sigusr2\n");
	}
}
