#include "sock.h"

FILE * fp, * file;
extern ft;
extern filesize;
extern stops;
extern counter;
extern char newq[1008];
extern count;
extern size,psize,filesize;
int i=0;
extern i2;
extern nnext;
extern filenum;
extern accum;
extern nextt;
extern size;
extern feop;
int global=0;
extern frame_expected;
extern w;
extern video;
extern recvv;
extern fsize;
extern filef;
extern filec;
long sizeaccum;
extern message;
int length = 0;

char alien[]="/home/mxlai/CS513/pj2/harty/recv/alien.mpeg.mpg";
char bird[]="/home/mxlai/CS513/pj2/harty/recv/bird.mpeg.mpg";
char pecker[]="/home/mxlai/CS513/pj2/harty/recv/pecker.mpeg.mpg";

char buffer[LENGTH];
char msg[1008];

int app(char call[],char files[]){

				/********************SERVER******************************/
	if(strcmp(call,SERVER)==0 ){
	
		if(filef==0){
		global++;
			file=fopen(files,"rb");
			if(file ==NULL){
			perror("file open");
			}
			
			
		}else if(filef==size){
		
		filef=0;
		
		printf("filenum: %d\n",filenum);
	
			if(fclose(file)!=0){
			perror("file close");
			}else{
			printf("file closed!\n");
			
			}
			
			
		}
		filef++;
		fread(buffer,1,LENGTH,file);
	
		
			  
		length = to_transport_layer(buffer);

	
		
	return length;
	}
	
	

			/********************CLIENT******************************/
else if(strcmp(call,CLIENT)==0){

	
		//printf("filec%d\n",filec);
		
		if(filec==0){
				fp=fopen(alien,"wb");
				
				if(fp ==NULL){
				perror("file open client");
				}
			
			
			filec-=2;
			}else if(filec==1){
			
			
				fp=fopen(bird,"wb");
				
				if(fp==NULL){
				perror("file open client");
				}
			
			
			filec-=2;
			}else if(filec==2){
		
				fp=fopen(pecker,"wb");
				
				if(fp ==NULL){
				perror("file open client");
				}
			
			filec=5;
			
			}else if(filec==8){
			printf("Done!\n");
			exit(0);
			}

			
		
		if(ft==41){
				
			
			
				int i;
		
				for(i=0;i<nnext;i++){
					msg[i]=newq[i];	
				}
				
				fwrite(msg,1,1008,fp);
				ft=0;
				
			if(feop==1){
			
			
			int i;
				
				
				for(i=0;i<nnext;i++){
					msg[i]=newq[i];	
				}
				
				fwrite(msg,1,nnext,fp);
					
				fclose(fp);
				
				filec+=3;
			ft=0;
			
			}
			
			clearbuffer();
			
		}else{
	
			if(feop==1){
			
			
			int i;
				
				
				for(i=0;i<nnext;i++){
					msg[i]=newq[i];	
				}
		
				fwrite(msg,1,nnext,fp);
			
					
				fclose(fp);
					
					
				filec+=3;
				ft=0;
				clearbuffer();
			
				
			}else{
			
			ft++;
			}
		}
	}
}
	




