#include "unp.h"

int main(int argc,char *argv[])
{
	int listenfd,connfd;
	struct sockaddr_in cliaddr,servaddr;

	listenfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(21);		/* ftp port */
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

	for( ; ; ){
		connfd = Accept(listenfd,(SA *)&cliaddr,sizeof(cliaddr));
		if( (pid = Fork()) == 0){
			Close(listenfd);
			//ftp process
			serv_client(listenfd);
			Close(connfd);
			exit(0);
		}
		Close(connfd);
	}
}
