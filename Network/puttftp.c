#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

char message[256];
struct addrinfo hints, *res;
int sockfd;

#define DATASIZE 1024
#define PORT "1069"

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

void ERR_SEND_WRQ() {
    char ERR_message[] = "Error sending data to the server. Check WRQ.\n";
    write(1, ERR_message, strlen(ERR_message));
    exit(EXIT_FAILURE);
}

void ERR_SEND_data() {
    char ERR_message[] = "Error sending data to the server. Check the data transfer.\n";
    write(1, ERR_message, strlen(ERR_message));
    exit(EXIT_FAILURE);
}

void ERR_RECEICVE_ack() {
    char ERR_message[] = "Error with the recption of ack.\n";
    write(1, ERR_message, strlen(ERR_message));
    exit(EXIT_FAILURE);
}

void ERR_OPEN() {
    char ERR_message[] = "Error when opening file.\n";
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

void SEND_data(int sockfd, const char *data, size_t size) {
	
    if (sendto(sockfd, data, size, 0, res->ai_addr, res->ai_addrlen) == -1) {
		
        ERR_SEND_data();
        
    }
}

void puttftp(char* host, char* file) {
	
	//Creation of the socket + error check
	
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		
        ERR_SOCKET();
        
    }

    GET_Info(host);

	sprintf(message, "Upload of %s on the server %s\n", file, host);
    write(1, message, strlen(message));
    
    //OPEN FILE//
    
    FILE *fp = fopen(file, "rb");
    
    if (!fp) {
        
        ERR_OPEN();
        
    }
    
    char buffer[DATASIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        SEND_data(sockfd, buffer, bytesRead);
    }
   
    fclose(fp);
  
}

void SEND_WRQ(int sockfd, char *file) {
	
    char wrq[DATASIZE];
    sprintf(wrq, "WRQ %s\n.", file);
    write(1, wrq, strlen(wrq));

     if (sendto(sockfd, wrq, strlen(wrq), 0, res->ai_addr, res->ai_addrlen) == -1) {
        
        ERR_SEND_WRQ();
	}
	
	close(sockfd);
}

int main(int argc , char* argv[]) {
	
	if (argc != 3) {
		
		ERR_ARG();
		
	}
	
	char* host = argv[1];
	char* file = argv[2];
	
	puttftp(host,file);
	
	SEND_WRQ(sockfd, file);
	
	return(0);

}

