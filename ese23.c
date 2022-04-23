#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define MAX_STRING 200

void main(int argc, char **argv){
	if(argc < 4){
		printf("Non ci sono abbastanza argomenti");
		exit(EXIT_FAILURE);
	}

	char *dir_1 = argv[1];
	char *dir_2 = argv[2];

	if( access( dir_1, F_OK ) != 0 ||  access( dir_2, F_OK ) != 0 ){
		perror("Le directories non esistono");
		exit(EXIT_FAILURE);
	}

	int n_file = argc-3;
	int i, stato, pid[n_file];
	char filePath[MAX_STRING], filePath2[MAX_STRING], pidNipote[MAX_STRING];
	char* buff;
	
	for(i = 0; i < n_file; i++){
		pid[i]=fork();
		if(pid[i] == 0){
			pid[i] = fork();
			if(pid[i] < 0){
				perror("Errore nella fork\n");
				exit(EXIT_FAILURE);
			}
			if(pid[i] == 0){
				//Copia del file nella directory 2 da parte del nipote
				strcpy(filePath, dir_1);
				strcat(filePath, "/");
				strcat(filePath, argv[i+3]);
				execl("/usr/bin/cp", "cp", filePath, dir_2, (char*)0);
				
				sprintf(buff, "Nipote %d: impossibile copiare il file %s\n", i+1, filePath);
                		perror(buff);
                		exit(EXIT_FAILURE);
			}
			pid[i] = wait(&stato);
			if(WIFSIGNALED(stato)){
				sprintf(buff, "Terminazione involontaria del processo con stato %d\n", pid[i], WTERMSIG(stato));		
				perror(buff);
                		exit(EXIT_FAILURE);
			}
			
			sprintf(pidNipote, "%d", getpid());
			strcat(pidNipote, ".txt");
			strcpy(filePath, dir_1);
			strcat(filePath, "/");
			strcpy(filePath2, filePath);
			
			//Aggiunta dell'ultimo pezzo del path in entrambi i filepath
			strcat(filePath, argv[i+3]);
			strcat(filePath2, pidNipote);
			
			//Rinomina del file nella directory 1 da parte del figlio
			printf("filePath: %s\nfilePath2: %s\n",filePath, filePath2);
			execl("/usr/bin/mv", "mv", filePath, filePath2, (char*)0);
			
			sprintf(buff, "Figlio %d: impossibile rinominare il file %s\n", i+1, filePath);
                	perror(buff);
                	exit(EXIT_FAILURE);
		}
	}
	
	//Attesa dei figli e controllo terminazioni
	for(i = 0; i < n_file; i++){
		pid[i] = wait(&stato);
		if(WIFSIGNALED(stato)){
			printf("Terminazione involontaria del processo con stato %d\n", pid[i], WTERMSIG(stato));
		}
	}
	
	//Stampa degli elementi presenti nella directory 2 da parte del padre
	execl("/usr/bin/ls", "ls", "-l", dir_2, (char*)0);
	perror("Impossibile stampare gli elementi presenti nella directory 2\n");
	exit(EXIT_FAILURE);

}
