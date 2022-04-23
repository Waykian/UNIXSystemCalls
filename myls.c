#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void myls(char* name){
	DIR* dir;
	struct dirent* dd; //generic directory element
	char buff[80];
	dir = opendir(name);
	
	while((dd = readdir(dir))!=NULL){
		sprintf(buff, "%s\n", dd->d_name);
		
		//Write directory name in standard output (1)
		write(1, buff, strlen(buff));
	}
}

int main(int argc, char**argv){
	if(argc < 2){
		printf("Errore");
		exit(1);
	}
	myls(argv[1]);
	exit(0);
}
