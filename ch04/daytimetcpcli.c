#include "unp.h"

int main(int argc,char **argv)
{
	int sockfd,n,count = 0;
	char recvline[MAXLINE + 1];
	socklen_t len;
	struct sockaddr_in servaddr,cliaddr;

	if(argc != 2)
		err_quit("usage:a.out < IPaddress >");

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		err_sys("socket error");

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);		/* daytime server */
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s",argv[1]);

	if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr)) < 0)
		err_sys("connect error");

	//new add,use getsockname to return the local ip addr and port.
	len = sizeof(cliaddr);
	if(getsockname(sockfd,(SA *)&cliaddr,&len) < 0)
		err_sys("getsockname error");

	printf("local connection is %s.\n",
			sock_ntop((SA *)&cliaddr,len));

	while((n = read(sockfd,recvline,MAXLINE)) > 0){
		count++;
		recvline[n] = 0;		/* null terminate */
		if(fputs(recvline,stdout) == EOF)
			err_sys("fputs error");
	}
	if(n < 0)
		err_sys("read error");

	printf("the count is %d\n",count);

	exit(0);
}
