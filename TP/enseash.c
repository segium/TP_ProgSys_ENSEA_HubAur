#include "enseash.h"

int basic_print_test(){
	int win=write(1,"welcome_in_the_SCAPWORLD",strlen("welcome_in_the_SCAPWORLD")-1);
	if (win==strlen("welcome_in_the_SCAPWORLD")-1){return(1);}
	else{return(0);}
	
	}

int basic_interaction_shell(){
	char buf[BUFSIZE];
	while(strcmp(buf,"exit")==0){
		if(read(1,buf,BUFSIZE)==-1){
			if(write(1,"Problem to read your commande sir",strlen("Problem to read your commande sir")==-1)){
				printf("CAN'T READ OR WRITE SIR");   // this line if print in the only and critical case of the user cann't read and write
				return(0);
				}
			}
		if(write(1,"enseash%",strlen("enseash%"))==-1){
				printf("problem sir");
				return(0);
				}
	}
	return(1);
}