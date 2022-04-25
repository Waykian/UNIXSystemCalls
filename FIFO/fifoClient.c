#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define DIM 32

void main(int argc, char** argv){
	int fd;
	char com[DIM], fileout[DIM];
	if (argc!=3){
		printf("errore sintattico");
		exit(-1);
	}
	sprintf(com,"%s",argv[1]);
	sprintf(fileout,"%s", argv[2]);
	
	if ((fd=open("server.in", O_WRONLY))<0){
		perror("client-open fifo in: ");
		exit(-1);
	}
	
	write(fd, com, DIM); /* send com */
	write(fd, fileout, DIM); /* send fileout */
	close(fd);
	unlink("server.in");

}
