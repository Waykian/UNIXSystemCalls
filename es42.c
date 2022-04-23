#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct{
	int giorno;
	int importo;
}info;

int main(int argc, char** argv){
	if(argc < 5){
		return -1;
	}
	
	char* existingFile1 = argv[1];	//entrate dello stesso tipo dell'es1
	char* existingFile2 = argv[2];	//uscite dello stesso tipo dell'es1
	int giorno = atoi(argv[3]);
	int importo = atoi(argv[4]);
	int i, pid, stato;
	
	char* file1 = "/home/kali/University/temp1";
	char* file2 = "/home/kali/University/temp2";
	
	//apertura dei file in scrittura
	int temp1 = open(file1, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	int temp2 = open(file2, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	
	//apertura dei file in lettura
	int entrate = open(existingFile1, O_RDONLY);
	int uscite = open(existingFile2, O_RDONLY);
	
	info operazione;
	int readInfo, written;
	
	for(i = 0; i < 2; i++){
		pid = fork();
		if(pid == 0){
			switch(i){
				case 0:
					while(readInfo = read(entrate, &operazione, sizeof(info)) > 0){
						written = write(temp1, &operazione.giorno, sizeof(int));
						if (written < 0){
							perror("Errore\n");
							exit(1);
						}
						written = write(temp2, &operazione.importo, sizeof(int));
						if (written < 0){
							perror("Errore\n");
							exit(1);
						}
					}
					exit(0);
					break; //non serve in teoria
				case 1:
					while(readInfo = read(uscite, &operazione, sizeof(info)) > 0){
						written = write(temp1, &operazione.giorno, sizeof(int));
						if (written < 0){
							perror("Errore\n");
							exit(1);
						}
						written = write(temp2, &operazione.importo, sizeof(int));
						if (written < 0){
							perror("Errore\n");
							exit(1);
						}
					}
					exit(0); 
					break;	//non serve sempre in teoria
				default:
					perror("Errore\n");
					exit(1);
			}
		}
	}
	
	
	
	for(int i = 0; i < 2; i++){
		pid = wait(&stato);
		printf("\nTerminato processo %d\n", pid);
		if(WIFEXITED(stato)){
			printf("Terminazione volontaria del processo %d con stato %d\n", pid, WEXITSTATUS(stato));			
		}
		if(WIFSIGNALED(stato)){
			printf("Terminazione involontaria del processo %d con stato %d\n", pid, WTERMSIG(stato));
		}
	}
	close(temp1);
	close(temp2);
	return 0;
}
