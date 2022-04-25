#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void esplora(char* d, char* f);

void main(int argc, char** argv){
	if(argc != 3){
		printf("Errore");
		exit(1);
	}
	if(chdir(argv[1])!=0){
		perror("Errore in chdir");
		exit(1);
	}
	esplora(argv[1], argv[2]);
}

void esplora(char* d, char* f){
	struct dirent* ff;
	char newdir[200];
	DIR* dir;
	dir = opendir(d);
	while((ff = readdir(dir))!=NULL){
		if((strcmp(ff->d_name, ".")!=0) && (strcmp(ff->d_name, "..")!=0)){ //salto . e ..
			if(chdir(ff->d_name) != 0){	//se è != 0 allora è un file
				if(strcmp(f, ff->d_name)==0){ //file trovato
					printf("Il file %s e' nella directory %s\n", f, d);
					exit(0);
				}
			}else{	//questa è una directory
				strcpy(newdir, d);
				strcat(newdir, "/");
				strcat(newdir, ff->d_name);
				esplora(newdir, f);	//quindi se trovo una directory ci entro
				chdir("..");	// alla fine della ricerca torno nella directory padre (salgo 1 livello)
			}
		}
	}
	closedir(dir);
}
