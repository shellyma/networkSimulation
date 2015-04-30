///////////////////////////////////////////////////////////////////////////////////////////////
//           Author:	Xiaoli Ma, Daniel Harty												 //
//           Date:	    2/12/2010														     //		
//           CS Class:	CS513/ECE506		                                                 //
//			 Project:   Webpage-Interaction  Server-Client Model                             //
///////////////////////////////////////////////////////////////////////////////////////////////

#include "sock.h"
int sock, cnt, count, s, clilen, newsock;
struct hostent *hp;
struct sockaddr_in cli_addr, serv_addr;

void clearscreen(void);

/* sockcreate -- Create socket from which to read.
   return socket descriptor if ok, -1 if not ok.  
   */
int sockcreate(int type, char *addr, int port) {
/* set up socket */
s = socket(AF_INET, SOCK_STREAM, 0);
addr = "ccc2.wpi.edu";
if (s < 0) {
perror("socket");
exit(1);}

else{
printf("socket setting up....\n");}

if (type == SEND) {
/* bind our local address so client can connect to us */
bzero((char *) &serv_addr, sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
serv_addr.sin_port = htons(port);  
 
if (bind(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
perror("can't bind to local address");
exit(1);}
printf("Socket created! Accepting connections.\n\n");
listen(s, 5);
clilen = sizeof(cli_addr);
newsock = accept(s, (struct sockaddr *) &cli_addr, &clilen);

if (newsock < 0) {
perror("accepting connection\n");
exit(1);}

else{
return newsock;}
}else {
bzero((void *) &serv_addr, sizeof(serv_addr));
printf("Looking up %s...\n", addr);

if ((hp = gethostbyname(addr)) == NULL) {
perror("host name error");
exit(1);}
bcopy(hp->h_addr, (char *) &serv_addr.sin_addr, hp->h_length);
printf("\nFound it.  Setting port connection to %d...\n", port);
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(port);		
printf("Open. Trying connection to server...\n");

if (connect(s, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
perror("can't connect");
exit(1);}
printf("\nConnection established!\n");
return s;}}


void clearscreen() {  
if (system( "clear" )) system( "cls" ); 
 }




 
 

 
 
 

 
