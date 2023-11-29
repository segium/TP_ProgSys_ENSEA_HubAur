#include "enseash.h"

int basic_interaction_shell(){
	char buf[BUFSIZE];
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
	
	return(1);
}
