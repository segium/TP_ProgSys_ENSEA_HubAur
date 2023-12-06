#include "enseash.h"



int basic_print_test(){
	int win=write(1,"welcome_in_the_SCAPWORLD",strlen("welcome_in_the_SCAPWORLD")-1);
	if (win==strlen("welcome_in_the_SCAPWORLD")-1){return(1);}
	else{return(0);}
	
	}

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
		if (WIFEXITED(returnCode)) {
			
			snprintf(extPROMPT, BUFSIZE, "(Exit: %d|%ld ms) ", WEXITSTATUS(returnCode),time_elapsed);
			
		} else {
			
			snprintf(extPROMPT, BUFSIZE, "(Sign: %d|%ld ms) ", WTERMSIG(returnCode),time_elapsed);
			
		}
		
		write(1, extPROMPT, strlen(extPROMPT));
		
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
        
        clock_gettime(CLOCK_MONOTONIC, &start_time);
        
        int PID = fork();
        
        if (PID == 0) {
			
            execlp("/bin/sh", "sh", "-c", buf, NULL);
            perror("Error with execlp");
            _exit(1);
            
        } else if (PID < 0) {
			
            perror("Error in the fork process");
            
        } else {
            // Wait for the son to end//
            
            wait(&returnCode);
            clock_gettime(CLOCK_MONOTONIC, &end_time);
			time_elapsed = ((end_time.tv_nsec - start_time.tv_nsec) / 1e6);//for ms conversion
        }
	}
	return(1);
}
