#include "unp.h"
#include <time.h>

int main(int argc,char **argv)
{
	int listenfd,connfd,i;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];
	char *ptr;
	time_t ticks;

	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(9999);		/* daytime server */
	
	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

	for( ; ; ){
		connfd = Accept(listenfd,(SA *)NULL,NULL);

		ticks = time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		ptr = buff;
		//my version
#ifndef DEBUG
		while( *ptr != '\0')
		{
			 Write(connfd,ptr,1);
			 ptr++;
		}
#endif

#ifdef DEBUG
		for(i = 0;i < strlen(buff);i++)
			Write(connfd,&buff[i],1);
#endif

		Close(connfd);
	}
}