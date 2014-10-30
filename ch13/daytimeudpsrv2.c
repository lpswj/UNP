//ex13.3
#include "unp.h"
#include <time.h>

int main(int argc,char **argv)
{
	int sockfd,optval;
	ssize_t n;
	socklen_t len;
	char buff[MAXLINE];
	time_t ticks;
	struct sockaddr_in cliaddr;

	if(argc == 2)
		sockfd = Udp_server(NULL,argv[1],NULL);
	else if(argc == 3)
		sockfd = Udp_server(argv[1],argv[2],NULL);
	else
		err_quit("usage:daytimeudpsrv2 [ <host> ] <service or port#>");

	Inet_pton(AF_INET,"192.168.25.198",&cliaddr.sin_addr);
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_port = htons(19);

	len = sizeof(cliaddr);
	char msg[10] = "123456";
	Sendto(sockfd,msg,strlen(msg),0,(SA *)&cliaddr,len);
	for( ; ; ){
		n = Recvfrom(sockfd,buff,MAXLINE,0,(SA *)&cliaddr,&len);
	
		Sendto(sockfd,buff,strlen(buff),0,(SA *)&cliaddr,len);

		Close(sockfd);
	}
}
