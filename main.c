#include "enseash.h"

int main(){
	
	char buf[BUFSIZE];
	ssize_t entryREAD;
	
	int returnCode = 0;	
	
	struct timespec start_time, end_time;
    long time_elapsed = 0;
	
	//SHELL EXECUTION
	
	while(1){
		
		//RETURN OF SIGNAL/EXIT CODE
		
		char extPROMPT[BUFSIZE];
		
		exit.time_print(); //Prompt with Exit/Sign + time of last command
		
		write(1,PROMPT,strlen(PROMPT));
		
		entryREAD = read(0, buf, sizeof(buf));
		
		//ERROR CHECK//
		
		error_check();
		
		//CTRL D CHECK//
		
		ctrlD();
				
		//Remove \n for execution//
		
        buf[strcspn(buf, "\n")] = '\0';

		//EXIT CHECK//
		
		if (strncmp(buf,"exit",strlen("exit"))==0){
			write(1,BYE,strlen(BYE));
			return(EXIT_SUCCESS);
			
		}

        //COMMANDS EXECUTION//
        
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        
        
	}
	return(1);
}



