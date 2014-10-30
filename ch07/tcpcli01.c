//ex7.3
#include "unp.h"

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;
	struct linger lin;
	socklen_t len;

	if(argc != 2)
		err_quit("usage:tcpcli < IPaddress >");

	sockfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	Inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	Connect(sockfd,(SA *)&servaddr,sizeof(servaddr));

	str_cli(stdin,sockfd);			/* do it all */

	len = sizeof(lin);
	lin.l_onoff = 1;
	lin.l_linger = 1;
	Setsockopt(sockfd,SOL_SOCKET,SO_LINGER,&lin,len);
	
	exit(0);
}
