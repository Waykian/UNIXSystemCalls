#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (){
	int pid, status;
	pid = fork();
	if(pid == 0){
		printf("Figlio con pid %d\n", pid);
		exit(0);
	}
	else{
		pid = wait(&status);
		printf("Terminato processo figlio numero %d\n", pid);
		if((char)status==0){	//quando si fa il cast si prendono solo gli 8 bit meno significativi
			printf("Terminazione volontaria con stato %d\n", status>>8); //spostiamo gli 8 bit di sinistra a destra
		}else{
			printf("Terminazione involontaria con stato %d\n", (char)status);
		}
	}
	
	return 0;
}
