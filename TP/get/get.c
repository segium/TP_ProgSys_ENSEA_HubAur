/*
 * Code wirte by Robin Auriac aka Xteck in ENSEA during the curse of  programmation system 
*/


//______ INCLUDE ________
#include "get.h"
#define BUF_SIZE 126


//_______ ERROR FUNCTION ________

int ERR_WRITE(){
	perror("Write problem\n");
	return(EXIT_FAILURE);
	}
	
int ERR_ARGU(){
	perror("Wrong argument\n");
	return(EXIT_FAILURE);
	}	
int ERR_ADDR(){
	perror("Wrong address");
	return(EXIT_FAILURE);
	}	
	
int ERR_COMM(){
	perror("no co");
	return(EXIT_FAILURE);
	}	
	
void JUMP_LINE(){
	if(write(1,"\n",strlen("\n"))==-1){perror("NO_JUMP");}
	}



	

struct addrinfo GET_Info(char* host){
	
	// THis functions create a addrinfo struct with the name host
	
	struct addrinfo hints, *res;
	memset(&hints,0,sizeof(hints));
	hints.ai_family =AF_UNSPEC;  // 
	hints.ai_socktype =SOCK_STREAM; //
	if(getaddrinfo(host,"1069",&hints,&res)==-1){ERR_ADDR();} // because my server port was on the 1069 port, srvtpinfo1.ensea.fr
	return(*res);
	}


int OpenSocket(struct addrinfo addr){
	
	// creat a socket with addrinfo and return the 
	
	int sfd;
	if((sfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP))==-1){ERR_COMM();} // SOCK_GRAM= connect with UDP protocol 
	return(sfd);
	}




int gettftp(int argc, char* argv[]){
	
	if(argc!=3){ERR_ARGU();}
	char Host[BUF_SIZE];
	char File[BUF_SIZE];
	strcpy(Host,argv[1]);  // host should represent the domain's name or domain's IP
	strcpy(File,argv[2]);

	
	if(write(1,Host,strlen(Host))==-1){return(ERR_WRITE());}
	JUMP_LINE();
	if(write(1,File,strlen(File))==-1){return(ERR_WRITE());}
	JUMP_LINE();
	
	struct addrinfo add_network=GET_Info(Host);
	if(write(1,add_network.ai_canonname,sizeof(add_network.ai_canonname))==-1){return(ERR_WRITE());}
	JUMP_LINE();
	
	return(EXIT_SUCCESS);
		
	}
	

int RRQ (int sfd,const void* buf,int SIZE_BUF, struct addrinfo add){
	if(sendto(sfd,buf,BUF_SIZE,0,add.ai_addr, add.ai_addrlen)==-1){return(ERR_WRITE());};
	return(EXIT_SUCCESS);
	}
	
	
	
int main(int argc ,char* argv[]){
	
	return(gettftp(argc,argv));
	
	}
