#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#define SIZE 12

void figlio(int fd_out, char filein[], char word[]);
void wait_child();

int pp[2];

int main(int argc, char* argv[]){
	//STUD è un file esistente con righe matricola:anno:media, di 11 caratteri
	//matricola 6 caratteri
	//V int <= 30
	// 1<=A<=3
	
	//stampare su stdout anno=a e media = v
	//p0 crea p1, p1 legge stud e così individua con grep se la riga ha a e v
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
	
	if(pipe(pp) < 0){
		perror("Errore nell'apertura della pipe");
		exit(-3);
	}
	
	int pid;
	pid = fork();
	
	if(pid == 0){
	
		printf("Sto cercando");
		close(pp[0]);
		
		
		char* stringToSearch;
		strcpy(stringToSearch, A);
		strcat(stringToSearch, ":");
		strcat(stringToSearch, V);
		
		printf("Sto cercando: %s...\n", stringToSearch);
		figlio(pp[1], existingFile, stringToSearch);
		close(pp[1]);
		exit(0);
	}else if(pid < 0){
		perror("Errore nella fork");
		exit(-1);
	}
	close(pp[1]);
	sleep(2);
	char c;
	read(pp[0], &c, 1);
	printf("Numero occorrenze: %c\n", &c);
	write(1, &c, 1);
	
	exit(0);
}

void figlio(int fd_out, char filein[], char word[])
{ 
  // ridirezione output su lato scrittura pipe:
  close(1); 
  dup(fd_out);
  close(fd_out);
  // esecuzione grep:
  execl("/bin/grep", "grep", "-c", word, filein, (char*)0);
  perror("Execl fallita");
  exit(-1);
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
