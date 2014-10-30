//ex 8.7
#include "unp.h"

static void recvfrom_int(int);
static int count;

void dg_echo(int sockfd,SA *pcliaddr,socklen_t clilen)
{
	socklen_t len;
	char mesg[MAXLINE];

	Signal(SIGINT,recvfrom_int);

	for( ; ; ){
		len = clilen;
		Recvfrom(sockfd,mesg,MAXLINE,0,pcliaddr,&len);
		printf("one datagram recived\n");

		count++;
	}
}

static void recvfrom_int(int singo)
{
	printf("\nreceived %d datagrams\n",count);
	exit(0);
}
