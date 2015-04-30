#include "sock.h"

int gbn;
extern indexi;
int sock,cnt,var2;
char selection[100];
char msg[24];
int flag1 = 0;
int ack_expected = 1;
int var, res;

int sock,cnt,var2;
char selection[100];
char msg[24];

char buffer[LENGTH];
long psize;
int size;

int MAX_SEQ = 5;

FILE *fp, *file ,*fileserv, *filecl;

char video[3][100];
char recvv[3][100];
extern filesize;
extern stops;
extern counter;
extern count;
extern here;
extern i2;
extern filenum;
extern accum;
extern nextt;
int filef=0;
int filec=0;
int frame_expected = 1;
int frame_sent = 0;
extern w;
long sizeaccum;
extern message;
long fsize[3];
int length1 = 0;

/*
extern LENGTH;
char buffer[LENGTH];
*/

int main(void){
int try=0;

	printf("\nAre you a Server or Client?\nEnter 'Server' or 'Client'\n");
	scanf("%s",selection);

				/********************SERVER******************************/
if((strcmp(selection,SERVER)==0 )|| (strcmp(selection,"server")==0)){
fileserv=fopen("/home/mxlai/CS513/pj2/harty/server.txt","wb");
if(fileserv==NULL){
perror("log file");
}
fputs("\nI am a server!\n",fileserv);
printf ("\nI am a server!\n");
		
strcpy(video[0],"/home/mxlai/CS513/pj2/harty/mpeg/aliensong.mpeg.mpg");
strcpy(video[1],"/home/mxlai/CS513/pj2/harty/mpeg/fordka-bird.mpeg.mpg");
strcpy(video[2],"/home/mxlai/CS513/pj2/harty/mpeg/woodpecker.mpeg.mpg");

strcpy(recvv[0],"/home/mxlai/CS513/pj2/harty/recv/aliensong.mpeg.mpg");
strcpy(recvv[1],"/home/mxlai/CS513/pj2/harty/recv/fordka-bird.mpeg.mpg");
strcpy(recvv[2],"/home/mxlai/CS513/pj2/harty/recv/woodpecker.mpeg.mpg");

fsize[0]=3201028;
fsize[1]=1095684;
fsize[2]=2768962;
 
sock=sockcreate(SEND,IPADDR,PORT);
printf("\nI'm waiting for clients.....(Call from DataLink layer....:P)\n");
fputs("\nI'm waiting for clients.....(Call from DataLink layer....:P)\n",fileserv);
  
while(filenum<3){
	file=fopen(video[filenum],"rb");	 
	if(file==NULL){
		perror("fopen");
	}else{
	fseek(file,0,SEEK_END);
	psize=ftell(file);
	rewind(file);
	size=psize/LENGTH+1;
	stops=psize/24+1;	
	if(fclose(file)!=0){
	perror("fclose");
	}else{
	
	printf("fclosed!\n");
	}

		}
	int var2=0;
	filef=0;
	
	while(var2<size+1){	
		
		
			var = 0;
			length1 = app(SERVER,video[filenum]);
				
		
			while(var<length1){ 
				
				struct timeval tv;
				fd_set sockread, sockwrite;
				tv.tv_sec = 1.6;
				tv.tv_usec = 500000;
				
				FD_ZERO(&sockread);
				FD_ZERO(&sockwrite);
					FD_SET(sock, &sockread);
					FD_SET(sock, &sockwrite);
				
				res = select(sock+1, &sockread, &sockwrite, NULL, &tv);
		
				if (res == -1){
				   perror("Socket Error");
				}
		
				if (FD_ISSET(sock, &sockread)){
					ack_expected = from_physical_layer(ack_expected);
					if(ack_expected==here){
					flag1=0;
					
					}
				}
						if(frame_sent-ack_expected+1<MAX_SEQ){
								
				if(FD_ISSET(sock, &sockwrite)){
				
					
					if (flag1 == 1){
					
					to_physical_layergbn();
					
					
						
					} else if (flag1 == 0){
						
						
							stuff();
						
							var++;
							frame_sent++;
							
						
					}else{
					printf("error GBN,quit....\n");
					exit(1);
					}
				}
			}
					 
				
				else{
					frame_sent = ack_expected;
					flag1 = 1;
					gbn = 0;

				}
			}	
			
			var2++;
	}
	
	clearbuf();



filenum++;
}
fclose(fileserv);
}


/********************CLIENT******************************/
					
	else{
			filecl=fopen("/home/mxlai/CS513/pj2/harty/client.txt","wb");
			printf ("\nI am a client!\n");
			fputs("\nI am a client!\n",filecl);	
			if((sock=sockcreate(RECV,IPADDR,PORT))<0){
			exit(1);
			}		
			else{		
				printf("\nSocket is set up .\n");
				
			
			while(frame_expected<=294405 ){
			
				frame_expected=from_physical_layer(frame_expected);
				
			}
			
		}
	}			
	fclose(filecl);
}
		
