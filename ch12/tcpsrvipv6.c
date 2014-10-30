//ex12.2
#include "unp.h"

int main(int argc,char *argv[])
{
	int listenfd,optval;
	struct sockaddr_in6 servaddr;

	if(argc != 2)
		err_quit("usage:tcpsrvipv4 <IPAddress>");

	listenfd = Socket(AF_INET6,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port = htons(9999);

	Inet_pton(AF_INET6,argv[1],&servaddr.sin6_addr);

	optval = 1;
	Setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

	pause();
}
