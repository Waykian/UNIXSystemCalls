#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#define SIZE 12

void wait_child();

int pp[2];

int main(int argc, char* argv[]){
	//STUD è un file esistente con righe matricola:anno:media, di 11 caratteri
	//matricola 6 caratteri
	//V int <= 30
	// 1<=A<=3
	
	//stampare su stdout anno=a e media = v
	//p0 crea p1, p1 legge stud e così individua se la riga ha a e v
	//il padre p0 riceve la riga, se va bene, e la stampa
	//wait finale per il figlio
	
	if(argc != 4){
		perror("Numero di argomenti errato");
		exit(-2);
	}
	
	char* existingFile = argv[1];
	char A[2];
	strcpy(A, argv[2]);
	char V[3];
	strcpy(V, argv[3]);
	
	char riga[12];
	char anno[2];
	char voto[3];
	anno[1] = '\0';
	voto[2] = '\0';
	int pid;
	
	if(pipe(pp) < 0){
		perror("Errore nell'apertura della pipe");
		exit(-3);
	}
	
	pid = fork();
	
	if(pid == 0){
		close(pp[0]);
		FILE* mainText = fopen(existingFile, "r");
		if(mainText == NULL){
			perror("Impossibile aprire il file");
			exit(-1);
		}
		while((fgets(riga, SIZE, mainText))!=NULL){
			char c = fgetc(mainText);
			if(strlen(riga) != 11){
				printf("%s\n", riga);
				perror("Stringa con lunghezza errata");
				printf("Lunghezza: %d", strlen(riga));
				printf("Riga: %s", riga);
				exit(-1);
			}
			//printf("Riga: %s\n", riga);
			anno[0] = riga[7];
			voto[0] = riga[9];
			voto[1] = riga[10];
			if(!strcmp(anno, A) && !(strcmp(voto, V))){
				write(pp[1], riga, SIZE);
			}
		}
		close(pp[1]);
		exit(0);
	}else if(pid < 0){
		perror("Errore nella fork");
		exit(-1);
	}
	close(pp[1]);
	while((read(pp[0], riga, SIZE))!=0){
		//printf("%s\n", riga);
		write(1, riga, SIZE);
	}
	
	exit(0);
}

void wait_child() {
    int pid_terminated,status;
    pid_terminated=wait(&status);
    if(WIFEXITED(status))
        printf("PADRE: terminazione volontaria del figlio %d con stato %d\n",
                pid_terminated, WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("PADRE: terminazione involontaria del figlio %d a causa del segnale %d\n",
                pid_terminated,WTERMSIG(status));
}
