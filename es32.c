#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int figli_terminati = 0;
double S = 0.0;
int i = 0;
int pid[2];
int esci = 0;

void sig_usr1_handler(int sig){
	printf("Processo %d: ricevuto SIGUSR1(%d).\n", getpid());
	S += 1/(i + 1);
	i++;
}

void sig_usr2_handler(int sig){
	printf("Processo %d: ricevuto SIGUSR2(%d).\n", getpid());
	S += (i + 2)/(i + 1);
	i++;
}

void sig_alrm_handler(int sig){
	printf("Somma S: %d\nValore di i: %d\n", S, i);
	kill(pid[0], SIGKILL);
	kill(getppid(), SIGALRM);
	exit(0);
}

void termina_padre(int sig){
	figli_terminati++;
	exit(0);
}

int main(int argc, char** argv){
	if(argv[1] == NULL){
		return -1;
	}
	
	int N = atoi(argv[1]);
	
	if(N <= 0){
		return -1;
	}
	signal(SIGCHLD, termina_padre);
	
	//P1
	pid[0] = fork();
	if(pid[0] == 0){
		int p3 = fork();
		if(p3 == 0){
			execl("/usr/bin/top", "top", (char*)0);
		}else if(p3>0){
			pause();
			kill(p3, SIGKILL);
			exit(0);
		}else{
			perror("Errore nella fork");
			exit(1);
		}

	}else if(pid[0] < 0){
		perror("Errore nella fork");
		exit(1);
	}
	
	//P2
	pid[1] = fork();
	if(pid[1] == 0){
		signal(SIGUSR1, sig_usr1_handler);
		signal(SIGUSR2, sig_usr2_handler);
		signal(SIGALRM, sig_alrm_handler);
		alarm(N);
		
	}else if(pid[1] < 0){
		perror("Errore nella fork");
		exit(1);	
	}
	
	if(pid[1]>0){
		while(figli_terminati != 1){
			if(getpid()%2==0){
				kill(pid[1], SIGUSR2);
			}else{
				kill(pid[1], SIGUSR1);
			}
			printf("PID padre: %d\n", getpid());
			sleep(2);
		}
	}



}
