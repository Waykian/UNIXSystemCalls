#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void main(int argc, char **argv){
	if(argc < 4){
		printf("Non abbastanza argomenti");
		exit(1);
	}
	char *dir_1 = argv[1];
	char *dir_2 = argv[2];
	if( access( dir_1, F_OK ) != 0 ||  access( dir_2, F_OK ) != 0 ){
		printf("Le directories non esistono");
	}
	int i;
	int n_file = argc-3;
	int stato;
	int pid[n_file];
	char *filePath = (char*)malloc(strlen(dir_1) + 25*sizeof(char));
	
	for(i = 0; i < n_file; i++){
		pid[i] = fork();
		
		if(pid[i]==0){
			strcpy(filePath, dir_1);
			strcat(filePath, "/");
			strcat(filePath, argv[i+3]);
			printf("Pid: %d\n", getpid());
			if(getpid()%2==0){
				execl("/usr/bin/cp", "cp", filePath, dir_2, (char*)0);
				exit(1);
			}else{
				execl("/usr/bin/rm", "rm", filePath, (char*)0);
				exit(1);
			}
		}
	}
	
	for(i = 0; i < n_file; i++){
		pid[i] = wait(&stato);
		if(WIFSIGNALED(stato)){
			printf("Terminazione involontaria del processo con stato %d\n", pid[i], WTERMSIG(stato));
		}
	}
	
	execl("/usr/bin/ls", "ls", "-l", dir_2, (char*)0);
	exit(1);
}
