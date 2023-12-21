#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>

#define size char[256]

int ERR_WRITE();
int ERR_ARGU();
int ERR_ADDR();
int ERR_COMM();

struct addrinfo GET_Info(char* host);
int OpenSocket(struct addrinfo addr);
int RRQ (int sfd,const void* buf,int SIZE_BUF, struct addrinfo add);

int gettftp(int argc, char* argv[]);
int main(int argc, char* argv[]);
