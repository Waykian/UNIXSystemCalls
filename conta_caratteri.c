#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int counter1, counter2;

void father_handler(int sig){
	switch(sig){
		case SIGUSR1:
			counter1++;
			break;
		case SIGUSR2:
			counter2++;
			break;
		default:
			fprintf(stderr, "Segnale inaspettato\n");
			exit(-1);
	
	}
}

void figlio(char* input, char to_check, int limit, int sig_to_send){
	int fd, counter, nread;
	char read_char;
	fd = open(input, O_RDONLY);
	counter = 0;
	
	while(nread = read(fd, &read_char, sizeof(char)) > 0){
		if(read_char == to_check){
			counter++;
		}
		if(read_char == '\n'){	//linea terminata
			if(counter > limit){
				kill(getppid, sig_to_send);
				sleep(1);
			}
			counter = 0;
		}
	}
	close(fd);
}

void print_output(char* pathname, int n, char* c){
	fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 00640);
	if(fd < 0){
		exit(-1);
	}
	char* buf;
	sprintf(buf, "trovate piu occorrenze di %c\n", c[0]);
	written = write(fd, buf, strlen(buf));
	if(written < 0){
		exit(-1);
	}
	//stessa cosa per p2
}

int main(int argc, char** argv){
	int pid, N, i;
	char to_check[2];
	char file_in[100], file_out[100];
	
	signal(SIGUSR1, father_handler);
	signal(SIGUSR2,father_handler);
	
	//se il padre crea file prima di creare i figli, accedono allo stesso I/O point, ma serve separato
	
	for(i = 0; i < 2; i++){
		pid = fork();
		if(pid < 0){
			exit(-1);
		}else if(pid == 0){
			int sig_to_send;
			sig_to_send = (i == 0)?SIGUSR1:SIGUSR2;
			figlio(file_in, to_check[i], N, sig_to_send);
			exit(0);
		}else{
		
		}
	}
	
	
	for(i = 0; i < 2; i++){
		wait_child();
		print_output(file_out, N, to_check);
		return 0;
	}
	

}
