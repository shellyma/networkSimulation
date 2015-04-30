#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>



#define LOAD 999
#define MAX_QUEUE 10000000        /* max number of buffered frames */
#define QUEUE 1024


typedef enum {frame_arrival, cksum_err, timeout, network_layer_ready, ack_timeout} event_type;
typedef unsigned long bigint;	/* bigint integer type available */
//typedef enum {false, true} boolean;	/* boolean type */
typedef unsigned int seq_nr;	/* sequence or ack numbers */
typedef struct {
int eop;
char load[24]; } packet;	/* packet definition */

int counter=0;
int count=0;
int newcount=0;
long filesize;
int nr=0;
int seven=0; 
int ft=0;

int i2=0;
int accum=0;
int filenum=0;
int tlc=0;
int mem=0;
int m=0;
typedef enum {data, ack} frame_type;	/* frame_kind definition */

typedef struct {	/* frames are transported in this layer */
  frame_type type;	/* what kind of a frame is it? --1 byte*/  
  seq_nr seq;   	/* sequence number --2-byte*/
  packet data;  	/* the network layer packet   --24-byte per pkt*/
  int eop;   /* if this the last frame of a pkt  --1 byte*/
  unsigned  char checksum;   	/* error check   --1 byte*/
} frame;              /* a frame is 29 bytes*/
frame w;


frame message[1];
unsigned int pktnumber=0;
unsigned int next_net_pkt;      /* seq of next network packet to fetch */
unsigned int last_pkt_given= 0;        /* seq of last pkt delivered*/
frame last_frame;               /* arrive frames are kept here */
packet last_packet;


/*Buffers*/
packet nq[MAX_QUEUE];  /*network layer buffer*/
frame dq[MAX_QUEUE];   /*datalink layer buffer*/
char tq[QUEUE];			/*tansport layer buffer*/
frame qq[40];			/*GBN window*/
char newq[1008];



/*Buffer indexes*/
int head=0,tail=0,current=0;    /*for nq[]*/
int nextt=0,curr=0;    /* for tq[]*/
int qh=0,qt=0;    /*for dq[]*/
int indexi=0;   /*for qq[]*/
int ii=0;
int stops=0;
int nnext=0;

int here=0;

int feop=0;
int res,cnt;
int totalsize;
int flag=0;
int closef=0;
int tqcount=0;

/*Function Prototypes*/
void enframe(packet p,int seq);

void init_frame(frame *s);
unsigned int pktnum();
/*for network layer*/
void dequeue(void);
void stuff(void);
packet gettop(void);
void enqueue(packet p);
/**/

void clearbuffer(void);
/*for transport layer*/
void enqueuet(char msg[]);
void dequeuet(char temp[]);
void clearbuf(void);
/**/
 unsigned char XOR(frame s);
 /*for datalink layer*/
 void enqueued(frame s);
 frame get(void);
 void dequeued(void);
 /**/
 /*for GBN window*/
 void enqueuef(frame s);
 void dequeuef(void);
 /**/
 frame ackframe(frame s);
 
packet enp(frame s);
 frame error(frame s);
 int to_transport_layer(char msg[]);
 void to_tansport_layerc(packet p);
 void from_transport_layer(char msg[]);
 void fillbuffer(packet p);
/* Wait for an event to happen; return its type in event. */
void wait_for_event(event_type *event);

/* Fetch a packet from the network layer for transmission on the channel. */
packet from_network_layer(void);

/* Deliver information from an inbound frame to the network layer. */
void to_network_layer(packet p);
void to_network_layerc(packet p);

/* Fetch a packet from the datalink layer for transmission on the channel. */
void from_datalink_layer(packet p);

/* Deliver information from an inbound frame to the network layer. */
void to_datalink_layer(packet p,int seq);
void to_datalink_layerc(packet p);

/* Go get an inbound frame from the physical layer and copy it to r. */
int from_physical_layer(int expected);

/* Pass the frame to the physical layer for transmission. */
void to_physical_layer(frame s);

/* Pass the frame to the physical layer for transmission(GBN)*/
void to_physical_layergbn(void);



void init_max_seqnr(unsigned int o);
unsigned int get_timedout_seqnr(void);

void GBN(void);


