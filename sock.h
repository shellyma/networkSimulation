
/*  sock.h   

*/
#include <sys/time.h>
#include <sys/select.h>
#include<fcntl.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>   
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
//#include <time.h>


#define SEND 1
#define RECV 2
#define SERVER "Server"
#define CLIENT "Client"


#define IPADDR "130.215.36.18"        /****server is ccc2.wpi.edu***/
#define PORT 55552
#define LENGTH 1000
int app(char call[],char files[]);






