#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

char message[256];
struct addrinfo hints, *res;
int sockfd;

#define PORT "69"

//ERROR HANDLING//

void ERR_ARG(){
	
	char ERR_message[] = "Error : Incorrect use of puttftp. Correct use is ./puttftp <server/host> <file>.\n";
	write(1, ERR_message, strlen(ERR_message));
	exit(EXIT_FAILURE);
	
}

void ERR_GETADR(){
	
		char ERR_message[] = "Error when getting server adress.\n";
        write(1, ERR_message, strlen(ERR_message));
        exit(EXIT_FAILURE);
	
}

void ERR_SOCKET() {
    char ERR_message[] = "Error creating socket.\n";
    write(1, ERR_message, strlen(ERR_message));
    exit(EXIT_FAILURE);
}

void ERR_CONNECT() {
    char ERR_message[] = "Error connecting to the server.\n";
    write(1, ERR_message, strlen(ERR_message));
    exit(EXIT_FAILURE);
}


//Upload a file on the server. Take <host> and <file> as arguments

void GET_Info(char* host){
	
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; /// 
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host, NULL, &hints, &res) != 0) {
		
        ERR_GETADR();
        
    }
    freeaddrinfo(res);
}



void puttftp(char* host, char* file) {
	
	//Creation of the socket + error check
	
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        ERR_SOCKET();
    }

    GET_Info(host);

    // Connection to the server + error check
    
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        ERR_CONNECT();
    }

	sprintf(message, "Upload of %s on the server %s\n", file, host);
    write(1, message, strlen(message));
    
    close(sockfd);
    
}

int main(int argc , char* argv[]) {
	
	if (argc != 3) {
		
		ERR_ARG();
		
	}
	
	char* host = argv[1];
	char* file = argv[2];
	
	puttftp(host,file);
	
	return(0);

}

