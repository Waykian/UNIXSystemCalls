
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char **argv){
    int digits = 0; 
    
    for(int i = 1; i<argc;i++){
        if((strncmp(argv[i], "MED", strlen("MED")))==0
            ||(strncmp(argv[i], "ING", strlen("ING")))==0
            ||(strncmp(argv[i], "ECO", strlen("ECO")))==0){
                //printf("%s\n", argv[i]);
                if(strlen(argv[i]) != 9){
                    printf("Codice matricola %d non valido\n", i);
                }else{
                    digits = 0;
                    for(int j = 3; j < strlen(argv[i]);j++){
                        if(isdigit(argv[i][j])==0){
                            printf("Codice matricola %d non valido\n", i);
                            break;
                        }else{
                            digits = digits + 1;
                        }
                    }
                    if(digits == 6){
                        printf("%s\n", argv[i]);
                    }
                }
                
        }else{
            printf("Codice matricola %d non valido\n", i);
        }
        
    }
    return 0;
}

