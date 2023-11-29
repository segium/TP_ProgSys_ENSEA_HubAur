#include "enseash.h"

int basic_print_test(){
	int win=write(1,"welcome_in_the_SCAPWORLD",strlen("welcome_in_the_SCAPWORLD")-1);
	if (win==strlen("welcome_in_the_SCAPWORLD")-1){return(1);}
	else{return(0);}
	
	}
