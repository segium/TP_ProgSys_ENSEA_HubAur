#include "enseash.h"

int basic_print_test(){
	int win=write(1,"welcome_in_the_SCAPWORLD",strlen("welcome_in_the_SCAPWORLD")-1);
	if (win==strlen("welcome_in_the_SCAPWORLD")-1){return(1);}
	else{return(0);}
	
	}

void exit.time_print(){
	if (WIFEXITED(returnCode)) {
			
			snprintf(extPROMPT, BUFSIZE, "(Exit: %d|%ld ms) ", WEXITSTATUS(returnCode),time_elapsed);
			
		} else {
			
			snprintf(extPROMPT, BUFSIZE, "(Sign: %d|%ld ms) ", WTERMSIG(returnCode),time_elapsed);
			
		}
		
		write(1, extPROMPT, strlen(extPROMPT));
}

void error_check(){
	
	if (entryREAD < 0){
			write(1,ERR_READ,strlen(ERR_READ));
		}
}

void ctrlD(){
	if (entryREAD == 0){
			write(1,BYE,strlen(BYE));
			return(EXIT_SUCCESS);
		}
}

void returnCodeVar(){
	wait(&returnCode);
    clock_gettime(CLOCK_MONOTONIC, &end_time);
	time_elapsed = ((end_time.tv_nsec - start_time.tv_nsec) / 1e6);//for ms conversion
}

void exec_command(){
	
	int PID = fork();
        
        if (PID == 0) {
			
            execlp("/bin/sh", "sh", "-c", buf, NULL);
            perror("Error with execlp");
            _exit(1);
            
        } else if (PID < 0) {
			
            perror("Error in the fork process");
            
        } else {
           
            returnCodeVar();
        }
}
