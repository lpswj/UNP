#include "unp.h"
#include <limits.h>			/* for OPEN_MAX */

int main(int argc,char **argv)
{
	int i,maxi,maxfd,listenfd,connfd,sockfd;
	int nready,open_max;
	ssize_t n;
	char buf[MAXLINE];
	socklen_t clilen;
	open_max = sysconf(_SC_OPEN_MAX);
	struct pollfd client[open_max];
	struct sockaddr_in cliaddr,servaddr;

	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);

	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);

	client[0].fd = listenfd;
	client[0].events = POLLRDNORM;
	for(i=1;i < open_max;i++)
		client[i].fd = -1;		/* -1 indicates available entry */
	maxi = 0;					/* maxi index into client[] entry */

	for( ; ; ){
		nready = Poll(client,maxi + 1,INFTIM);

		if(client[0].revents & POLLRDNORM){		/* new connection */
			clilen = sizeof(cliaddr);
			connfd = Accept(listenfd,(SA *)&cliaddr,&clilen);

			for(i = 1;i < open_max;i++)
				if(client[i].fd < 0){
					client[i].fd = connfd;		/* save descriptor */
					break;
				}
			if(i == open_max)
				err_quit("too many clients");

			client[i].events = POLLRDNORM;
			if(i > maxi)
				maxi = i;		/* max index in client[] array */

			if(--nready <= 0)
				continue;		/* no more readable descriptors */
		}

		for(i = 1;i <= maxi;i++){		/* check all clients for data */
			if( (sockfd = client[i].fd) < 0)
				continue;
			if(client[i].revents & (POLLRDNORM | POLLERR)){
				if( (n = Read(sockfd,buf,MAXLINE)) < 0){
					if(errno == ECONNRESET){
						/* connection reset by client */
						Close(sockfd);
						client[i].fd = -1;
					}else
						err_sys("read error");
				}else if(n == 0){
					/* connection closed by client */
					Close(sockfd);
					client[i].fd = -1;
				}else
					Writen(sockfd,buf,n);

				if(--nready <= 0)
					break;			/* no more readable descriptors */
			}
		}
	}
}
