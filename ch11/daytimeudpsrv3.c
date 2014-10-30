//ex11.9
#include "unp.h"
#include <time.h>

int main(int argc,char **argv)
{
	int sockfd,optval;
	ssize_t n;
	socklen_t len;
	char buff[MAXLINE];
	time_t ticks;
	struct sockaddr_storage cliaddr;

	if(argc == 2)
		sockfd = Udp_server(NULL,argv[1],NULL);
	else if(argc == 3)
		sockfd = Udp_server(argv[1],argv[2],NULL);
	else
		err_quit("usage:daytimeudpsrv2 [ <host> ] <service or port#>");

	optval = 1;
	Setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
	Setsockopt(sockfd,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));
	for( ; ; ){
		len = sizeof(cliaddr);
		n = Recvfrom(sockfd,buff,MAXLINE,0,(SA *)&cliaddr,&len);
	
		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		Sendto(sockfd,buff,strlen(buff),0,(SA *)&cliaddr,len);

		Close(sockfd);
	}
}
