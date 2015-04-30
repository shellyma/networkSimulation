
	#include "header.h"
	extern sock;
	extern size;
	extern psize;
	extern indexi;
	extern flag1;
	extern ack_expected;
	extern frame_sent;
	extern fileserv;
	
	extern  filecl;

	

	/*
		stuff(char pkt[])
		convert pkt to each 24-bytes frames
	*/
	int to_transport_layer(char m[]){
	int var;
	int length;

	tlc++;
	enqueuet(m);
	length=nextt/24;

	return length;


	}

	/**
	utilize tq[1024] to fill the buffer
	send,once index->1000, or EOF is detected
	*/
	void to_transport_layerc(packet p){	


		fillbuffer(p);
		
		app("Client","abc");
		

	}

	void from_transport_layer(char msg[]){
		
		
		int j;
		for(j=0;j<1000;j++){
			msg[j]=tq[j];
		}
		
		

	}

	/**
	 Fill the transport layer buffer, make msg(1000B)
	*/
	void fillbuffer(packet p){

		if(p.eop==1){
			feop=1;
			
		}else if(p.eop==0){
			
			feop=0;
		}else{
		printf("error, quit.......\n");
		exit(0);
		
		}	
		
		
		int i;
		for(i=0;i<24;i++){
			newq[nnext]=p.load[i];
			nnext++;  
			
		}
		
	}

	void clearbuffer(void){
		int j;
		
		for(j=0;j<1008;j++){
			newq[j]=(char)NULL;
		}
		nnext=0;

	}


	frame error(frame s){

	s.checksum =  s.checksum ^ (1UL << 1);
	return s;
	}



	void stuff(void){

	packet p;

	dequeuet(p.load);


	enqueue(p);

			counter++;
			newcount++;
			
			if(newcount==stops){
				newcount=1;
				ii++;
				p.eop=1;
				
				
			}else{
				p.eop=0;
				
			}
			
		to_network_layer(p);
		
		
		
	}

	void clearbuf(void){
	int i;
	for(i=0;i<1024;i++){
	tq[i]=(char)NULL;
	}
	nextt=0;

	}

	/*
		to_network_layer(packet *p)
		send a packet to network layer

	*/
	void to_network_layer(packet p)
	{
	  unsigned int num;
		//printf("last_pkt_given: %d\n",last_pkt_given);
		num = pktnum();
	  if (num != last_pkt_given + 1) {
		printf("\n packet %d out of order.\n",num);
		exit(0);
	  }
	  
	  last_pkt_given = num;


		
	to_datalink_layer(p,num); 


	}

	void to_network_layerc(packet p){

		to_transport_layerc(p);
	}


	/*
		to_datalink_layer(packet P)
		pump packets to datalink layer, where implements GO-Back-N protocol

	*/

	void to_datalink_layer(packet p,int seq){

	enframe(p,seq);

	}

	void to_datalink_layerc(packet p){

	to_network_layerc(p);


	}

	void enframe(packet p,int seq){

	 frame s;
		int i;
		s.checksum = (char)NULL;
		s.seq = 0;
		s.eop = 0;
		for (i = 0; i<=23;i++){
		s.data.load[i] = (char)NULL;
		}

		s.type=data;
		s.seq=seq;

		s.data=p;
		s.eop=p.eop;
		s.checksum=XOR(s);
		
		enqueued(s);
		enqueuef(s);
		
		if(seven==6){
			s = error(s);
			seven=0;
		}else{
			seven++;
		}
		

		to_physical_layer(s);

	}
	void to_physical_layergbn(void){

		frame s;
		s=qq[tail];
	
		
		if(tail==indexi){
		
			if(send(sock,&s,sizeof(frame),0)<0){
				perror("send sock");
				}else{
		
				}
				
			
			here=qq[indexi-1].seq;
			tail=0;
			
			//ack_expected=here+1;
			frame_sent=here;
		}else if(tail>indexi){
			
			printf("error\n");
			exit(0);
		}else{
			if(send(sock,&s,sizeof(frame),0)<0){
				perror("send sock");
				}else{
				tail++;
			
				}
			}
	}
	void to_physical_layer(frame s){
	
	nanosleep(10000000);  
	

	if((int)s.type==0){
		if(send(sock,&s,sizeof(frame),0)<0){
			perror("send sock");
			}else{
			
			dequeued();
			fprintf(fileserv,"Sent Frame:# %d\n",s.seq);
			
			}
		}else if((int)s.type==1){
				if(send(sock,&s,sizeof(frame),0)<0){
				perror("send ack");
				}else{
				time_t t=time(0);
			fprintf(filecl,"Sent ACK:# %d\n",s.seq);
		
			
		

				
				}
		}


	}

	int from_physical_layer(int expected){
	int flag=0;
	frame r;
	char u;
	unsigned char checkvalue;
	if(recv(sock,message,sizeof(frame),0)<0){
		perror("recv");
		}else{
		r=message[0];
		
		/*server checks ack*/
		if((int)message[0].type==1){
			
		
			if(expected == message[0].seq  ){	
					
					fprintf(fileserv,"ACKrecv:%d\n",message[0].seq);
					if(message[0].seq==here){
						here=0;
						flag1=0;
						tail-=1;
						
						printf("frame sent:%d\n",frame_sent);
						
						}
						
						dequeuef();
						
									
						expected++;
							}
							return expected;
							/*client receives frames*/
			}else if((int)message[0].type==0){

				 checkvalue = XOR(message[0]);
					
					if ((int)checkvalue==(int)r.checksum){
					
					}else{
					
					fprintf(filecl,"Problem!!  checkvalue %d\n",(int)checkvalue);
					fprintf(filecl,"checksum %d\n",(int)r.checksum);
					
					}
					
					if((r.seq==expected)&&((int)checkvalue==(int)r.checksum)){
					
						fprintf(filecl,"recvframe:%d\n",message[0].seq);
						
						frame a;
						a=ackframe(r);	
						
						/*send ACK*/
						to_physical_layer(a);
						expected++;
						packet pc;
						
						pc=enp(r);
						to_datalink_layerc(pc);
						
						
						return expected;
					}else{

						perror("Error occured upon receiving, cannot send to datalink layer!");
					
					}

		
		}else{
		perror("Error occured upon receiving!");
		}
	}	
}

	packet enp(frame s){

	packet p;

	p=s.data;

	return p;
	}


	frame ackframe(frame s){

	frame r;

	r.type=ack;
	r.seq=s.seq;

	r.eop=s.eop;

	r.checksum=s.checksum;

	return r;
	}


	/*******************************************************
		Byte-by-Byte XOR for error detection field
		
	********************************************************/
	 unsigned char XOR(frame s)
	{
		unsigned char seqn[1];
		unsigned char check, temp0, temp1, temp2, temp3, temp4;
		int i;
		memcpy( seqn, &s.seq, 2 );
		temp0 = s.type;
		temp1 = seqn[0] ;
		temp2 = seqn[1];
		check = temp0^temp1;
		check = temp2^check;
		if (s.type == data){
			for (i = 0; i<=23;i++){
				temp3 = s.data.load[i];
				check = temp3^check;}}
				temp4 = s.eop;
				check = temp4^check;
	  return check;
	  }

	/*
		from_network_layer(void)
		fetch a packet from network layer

	*/

	packet from_network_layer(void){

		packet p;

		p=gettop();
		dequeue();
		next_net_pkt++;

	return p;
	}


	/*
		enqueue(packet p)
		insert a incoming packet to the buffer at network layer

	*/
	void enqueued(frame s){

	if(qh==MAX_QUEUE){
		printf("Out of Boundary(enqueued)!\n\n");
		exit(0);
		}
		dq[qh]=s;
		qh++;
	}

	void enqueuef(frame s){

		if(indexi==40){
		printf("Out of Boundary(enqueuef)!\n\n");
		exit(0);
		}
		
		qq[indexi]=s;
		indexi++;
	}

	frame getf(void){
	return qq[0];
	}

	void dequeuef(void){
		int i;

	for(i=0;i<indexi-1;i++){
	qq[i]=qq[i+1];

	}

	indexi-=1;
	if(tail>0){
	tail-=1;
	}
	
	
	}

	frame get(void){

	return dq[0];


	}

	void dequeued(void){
	int i;

	for(i=1;i<qh-1;i++){
	dq[i]=dq[i+1];

	}

	qh-=1;

	}
	void enqueue(packet p){

	if(head==MAX_QUEUE){
		printf("Out of Boundary!\n\n");
		exit(0);
		}
		nq[head]=p;
		current=head; /*the top one*/
		head++;

	}

	void reset(void){
	int p;

	for(p=0;p<QUEUE;p++){
	tq[p]=(char)NULL;
	}

	}



	/*always hold 1016 bytes of msg, 16 from last and 1000 from new*/

	void dequeuet(char temp[]){
	int q;
	int t=0;
		int j;
		
		for(j=0;j<24;j++){
			temp[j]=tq[j];
		}
		
		for(q=24;q<nextt;q++){
			tq[t]=tq[q];
			t++;
			}
		
			nextt-=24;
		}
		


	void enqueuet(char pkt[]){

		if(nextt==QUEUE+1){
		printf("Out of Boundary!\n\n");
		exit(0);
		}else{
			int i;
			for(i=0;i<1000;i++){
			tq[nextt]=pkt[i];
			nextt++;
			}
			
			
		}

	}

	void enqueuetc(packet p){
		if(nextt==QUEUE+1){
		printf("Out of Boundary!\n\n");
		exit(0);
		}else{
			int i;
			for(i=0;i<24;i++){
				tq[nextt]=p.load[i];
				nextt++;
			}
		
		}
	}

	


	/*
		gettop(void)
		get the first packet of the buffer at network layer

	*/

	packet gettop(void){

	return nq[current];

	}


	/*
		dequeue()
		pop the first packet of buffer at the network layer

	*/

	void dequeue(void){
	int i;

	for(i=1;i<current;i++){
	nq[i]=nq[i+1];

	}

	head-=1;
	current=head-1;


	}


	/*
		pktnum()
		track the num of  packets, also assigned as sequence numbers for frames to datalink layer

	*/

	unsigned int pktnum()
	{
	/* Extract packet number from packet. */

	  pktnumber++;
	return pktnumber;
	}
