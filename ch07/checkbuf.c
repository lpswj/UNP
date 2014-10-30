//ex7.1
#include "unp.h"

int main()
{
	int fd,recvbuff,sendbuff;
	socklen_t len;
	len = sizeof(int);
	
	//for tcp
	fd = Socket(AF_INET,SOCK_STREAM,0);
	if(getsockopt(fd,SOL_SOCKET,SO_RCVBUF,&recvbuff,&len)  == -1)
		err_ret("getsockopt error");
	else
		printf("tcp default recvbuff = %d\n",recvbuff);

	if(getsockopt(fd,SOL_SOCKET,SO_SNDBUF,&sendbuff,&len)  == -1)
		err_ret("getsockopt error");
	else
		printf("tcp default sendbuff= %d\n",sendbuff);

	//for udp
	fd = Socket(AF_INET,SOCK_DGRAM,0);
	if(getsockopt(fd,SOL_SOCKET,SO_RCVBUF,&recvbuff,&len)  == -1)
		err_ret("getsockopt error");
	else
		printf("udp default recvbuff = %d\n",recvbuff);

	if(getsockopt(fd,SOL_SOCKET,SO_SNDBUF,&sendbuff,&len)  == -1)
		err_ret("getsockopt error");
	else
		printf("udp default sendbuff= %d\n",sendbuff);



}
