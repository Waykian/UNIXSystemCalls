#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (){
	int pid;
	pid = fork();
	
	if(pid == 0){
		printf("Ciao da figlio\n");
	}else if(pid > 0){
		printf("Ciao da padre\n");
	}else{
		printf("Errore");
	}
	return 0;
}
