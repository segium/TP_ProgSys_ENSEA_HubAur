#include "enseash.h"


int basic_print_test(){
	int win=write(1,"welcome_in_the_SCAPWORLD",strlen("welcome_in_the_SCAPWORLD")-1);
	if (win==strlen("welcome_in_the_SCAPWORLD")-1){return(1);}
	else{return(0);}
	
	}

int main(){
	
	char buf[BUFSIZE];
	ssize_t entryREAD;
			
	//SHELL EXECUTION
	
	while(1){
		
		write(1,PROMPT,strlen(PROMPT));
		entryREAD = read(0, buf, sizeof(buf));
		
		//ERROR CHECK//
		if (entryREAD < 0){
			write(1,ERR_READ,strlen(ERR_READ));
		}
		
		//CTRL D CHECK//
		if (entryREAD == 0){
			write(1,BYE,strlen(BYE));
			return(EXIT_SUCCESS);
		}
				
		//Remove \n for execution//
        buf[strcspn(buf, "\n")] = '\0';

		//EXIT CHECK//
		if (strncmp(buf,"exit",strlen("exit"))==0){
			write(1,BYE,strlen(BYE));
			return(EXIT_SUCCESS);
			
		}

        //COMMANDS EXECUTION//
        
        int PID = fork();
        
        if (PID == 0) {
			
            execlp(buf, buf, NULL);
            perror("Error with execlp");
            _exit(1);
            
        } else if (PID < 0) {
			
            perror("Error in the fork process");
            
        } else {
            // Wait for the son to end//
            wait(NULL);
        }
	}
	return(1);
}
