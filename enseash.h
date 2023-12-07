#include <string.h>
/*#include <sys/type.h>*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZE 256
#define PROMPT "enseah % "
#define HELLO "Welcome to the custom shell \r\Enter exit to shutdown the shell \r\ enseash %"
#define BYE "\r\Shell closed. \n"

#define ERR_READ "Error reading input"


/*functions*/

int basic_print_test(); 
void exit.time_print();
void error_check();
void ctrlD();
void returnCodeVar();
void exec_command();
