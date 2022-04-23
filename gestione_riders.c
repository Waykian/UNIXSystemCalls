#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAXNUM 36

void main(int argc, char **argv){
	int G, N, stato, pid[N];

	if(argc != 3){
		printf("Numero di parametri errati");
		exit(-1);
	}
	G = atoi(argv[1]);
	N = atoi(argv[2]);
	if(G>7 || G <= 0||N<=0){
		printf("Parametri errati");
		exit(-1);
	}
	srand(time(NULL));
	int matrix[N][G];
	for(int i = 0; i < N; i++){
		for(int j = 0; j < G; j++){
			matrix[i][j] = rand()%MAXNUM;
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	int earning[N];
	for(int i = 0; i < N; i++){
		pid[i] = fork();
		
		if(pid[i]<0){
			perror("Errore fork\n");
			exit(1);
		}
		if(pid[i] == 0){
			earning[i] = 0;
			for(int j = 0; j < G; j++){
				earning[i] += matrix[i][j];
			}
			printf("\nIl rider %d ha guadagnato %d\n", i, earning[i]);
			exit(earning[i]);
		}
	}
	
	for(int i = 0; i< N; i++){
		pid[i] = wait(&stato);
		printf("\nTerminato processo %d\n", pid[i]);
		if(WIFEXITED(stato)){
			printf("\nL'indice del rider e' %d\nGuadagno finale %d\n", i, WEXITSTATUS(stato));
			printf("Terminazione volontaria del processo %d con stato %d\n", pid[i], WEXITSTATUS(stato));			
		}
		if(WIFSIGNALED(stato)){
			printf("Terminazione involontaria del processo %d con stato %d\n", pid[i], WTERMSIG(stato));
		}
	}
}
