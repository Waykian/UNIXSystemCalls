#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int pid = fork();
	if(pid == 0){
		printf("Sono figlio ed eseguo ls\n");
		execl("/bin/ls", "ls", "-l", (char*)0);
		printf("Errore in execl\n");
		exit(1);
	}
	if(pid>0){
		printf("Padre\n");
		exit(0);
	}
	if(pid<0){
		printf("Errore in fork\n");
		exit(1);
	}

}
