#
# Makefile
#

CC = gcc

all: newmain

newmain: newmain.c  socket.o  work.o app.o sock.h 
	$(CC) -o newmain newmain.c socket.o work.o app.o

socket: socket.c sock.h
	$(CC) -c socket.c

 work: work.c header.h
	$(CC) -c work.c

app: app.c sock.h
	$(CC) -c app.c

clean:
	/bin/rm -rf newmain.o sock.o work.o app.o newmain


