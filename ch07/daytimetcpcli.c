//ex7.2
#include "unp.h"
#include <netinet/tcp.h>

int main(int argc,char **argv)
{
	int sockfd,n,count = 0;
	char recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
	int recvbuff,mss;
	socklen_t len;

	if(argc != 2)
		err_quit("usage:a.out < IPaddress >");

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
		err_sys("socket error");

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);		/* daytime server */
	if(inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s",argv[1]);

	len = sizeof(int);
	//output the recvbuff and mss
	printf("before connection:\n");
	if(getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvbuff,&len) == -1)
		err_ret("getsockopt error");
	else
		printf("recvbuff is %d\n",recvbuff);
	if(getsockopt(sockfd,IPPROTO_TCP,TCP_MAXSEG,&mss,&len) == -1)
		err_ret("getsockopt error");
	else
		printf("mss is %d\n",mss);

	if(connect(sockfd,(SA *)&servaddr,sizeof(servaddr)) < 0)
		err_sys("connect error");
	
	//output the recvbuff and mss again after connect
	printf("after connection:\n");
	if(getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvbuff,&len) == -1)
		err_ret("getsockopt error");
	else
		printf("recvbuff is %d\n",recvbuff);
	if(getsockopt(sockfd,IPPROTO_TCP,TCP_MAXSEG,&mss,&len) == -1)
		err_ret("getsockopt error");
	else
		printf("mss is %d\n",mss);

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
