#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAX_CHILDREN 100

int OKF = 0;

void sig_usr1_handler(int sig){
	printf("Processo %d: ricevuto SIGUSR(%d). Termino.\n", getpid(), sig);
	//aggiungo la exit in caso si attivi prima della pause nella funzione wait_for_signal
	exit(0);
}

void figlio_ok(int sig){
	OKF++;
}

void wait_for_signal(){
	signal(SIGUSR1, sig_usr1_handler);
	kill(getppid(), SIGUSR2);
	pause();
	exit(0);
}

void sleep_and_terminate(){
	sleep(5);
	printf("Processo %d: sleep di 5 secondi finita. Termino.\n", getpid());
	exit(0);
}

int main(int argc, char** argv){
	if(argv[1] == NULL || argv[2] == NULL){
		return -1;
	}
	int N = atoi(argv[1]);
	int K = atoi(argv[2]);
	int pid[MAX_CHILDREN];
	int stato;
	signal(SIGUSR2, figlio_ok);
	for(int i = 0; i < N; i++){
		pid[i] = fork();
		if(pid[i] == 0){
			if(i < K){
				//aspetta il segnale SIGUSR1
				wait_for_signal();
			}else{
				//sleep(5) e termina
				sleep_and_terminate();
			}
		}else if(pid[i] > 0){
		}else{
			return -1;
		}
	}
	while(OKF<K){
		pause();
	}
	for(int i = 0; i < K; i++){
		kill(pid[i], SIGUSR1);
	}
	
	for(int i = 0; i < N; i++){
		pid[i] = wait(&stato);
		printf("\nTerminato processo %d\n", pid[i]);
		if(WIFEXITED(stato)){
			printf("Terminazione volontaria del processo %d con stato %d\n", pid[i], WEXITSTATUS(stato));			
		}
		if(WIFSIGNALED(stato)){
			printf("Terminazione involontaria del processo %d con stato %d\n", pid[i], WTERMSIG(stato));
		}
	}

}
