#include "unp.h"

int main()
{
	int sockfd,recvbuf;
	struct sockaddr_in servaddr;
	socklen_t len;

	sockfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	len = sizeof(servaddr);
	Bind(sockfd,(SA *)&servaddr,len);

	Listen(sockfd,LISTENQ);

	len = sizeof(recvbuf);
	Getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvbuf,&len);

	printf("the recvbuff is %d\n",recvbuf);


}
