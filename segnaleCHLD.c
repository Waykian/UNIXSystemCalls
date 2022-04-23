#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int);

int main(){ 
	int PID, i;
	signal(SIGCHLD,handler);
	PID=fork();
	if (PID>0) /* padre */{
		for (i=0; i<100; i++) /* attività del padre..*/
		printf("il padre sta lavorando...\n");
		exit(0);
	}
	else /* figlio */{ 
		signal(SIGCHLD,SIG_DFL);
		for (i=0; i<1000; i++); /* attività del figlio..*/
		exit(1);
	}
}

void handler (int signum){
	int status;
	wait(&status);
	if ((char)status==0)
		printf("term. volontaria con stato %d", status>>8);
	else
		printf("term. involontaria per segnale%d\n",(char)status);
}
