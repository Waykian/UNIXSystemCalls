#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


typedef struct{
	int giorno;
	int importo;
}info;

int main(int argc, char** argv){
	
	if(argc < 4){
		return -1;
	}
	
	char* existingFile = argv[1]; //file con riga strutturata come tipo-giorno-importo
	char* file1 = argv[2];
	char* file2 = argv[3];
	
	FILE* mainText = fopen(existingFile, "r");
	int fde = open(file1, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	int fdu = open(file2, O_CREAT|O_WRONLY|O_TRUNC, 0777);
	
	
	char tipo;
	char giorno[2];
	char importo[6];
	char throw;
	int nread;
	
	int i, j;
	
	if(mainText == NULL){
		perror("Impossibile aprire il file");
		exit(-1);
	}
	char buffer[35];
	char c;
	while(fgets(buffer, sizeof(buffer), mainText) != NULL){
		printf("%s", buffer);
		tipo = buffer[0];
		throw = buffer[1];
		i = 2;
		j = 0;
		while(buffer[i]!='-'){
			giorno[j] = buffer[i];
			j++;
			i++;
		}
		i++;
		j = 0;
		for(;i < strlen(buffer); i++){
			importo[j] = buffer[i];
			j++;
		}
		
		info operazione;
		operazione.giorno = atoi(giorno);
		operazione.importo = atoi(importo);
		
		switch(tipo){
			case 'E':
				write(fde, &operazione, sizeof(info));
				break;
			case 'U':
				write(fdu, &operazione, sizeof(info));
				break;
			default:
				printf("Carattere non riconosciuto\n");
		
		}
		
    		printf("%c-%s-%s", tipo, giorno, importo);
	}
	

	
	/*
	Tipo è un singolo carattere con valore ’E’ (nel caso la riga riporti un’entrata) oppure ‘U’
	(nel caso di uscita)
	• Giorno è una stringa di 1 o 2 caratteri che rappresenta l’intero (compreso tra 1 e 31) che
	indica il giorno in cui si è svolta l’operazione;
	• Importo è una stringa di lunghezza variabile (da 1 a 6 caratteri) che rappresenta
	
	l’importo dell’operazione (espresso tramite un intero).
	/
	
	/*
	int VAR;
	
	//creare file binario con una sequenza di interi
	int fd;	//file descriptor
	fd = creat("Premi", 0777); //leggibile, scrivibile, eseguibile per tutti, e si chiama "premi"
	printf("Immetti una sequenza di interi (alla fine premi CTRL+D): ");
	//CTRL+D significa EOF (end of file)
	
	int k;
	char buff[25] = "";
	while(k = read(0, buff, 25)>0){
		VAR = atoi(buff);
		write(fd, &VAR, sizeof(int));
	}
	
	//lettura di un file binario di int con fd file descriptor
	/*read(fd, &VAR, sizeof(int));*/
	fclose(mainText);
	close(fde);
	close(fdu);
	return 0;
}
