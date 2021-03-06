#include "unp.h"

void sig_chld(int signo)
{
	pid_t pid;
	int stat;

	pid = wait(&stat);
	printf("child %d terminated\n",pid);
	return;
}

int main(int argc,char **argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in servaddr,cliaddr;

	listenfd = Socket(AF_INET,SOCK_STREAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	Listen(listenfd,LISTENQ);
	signal(SIGCHLD,sig_chld);

	for( ; ; ){
		clilen = sizeof(cliaddr);
		if( (connfd = accept(listenfd,(SA *)&cliaddr,&clilen)) < 0){
			if(errno == EPROTO)
				err_sys("EPROTO error");
			else if(errno == ECONNABORTED)
				err_sys("ECONNABORTED error");
			else
				err_sys("accept error");
		}
		if( (childpid = Fork()) == 0){			/* child process */
			Close(listenfd);			/* closing listening socket */
			str_echo(connfd);			/* process the request */
			exit(0);
		}
		Close(connfd);
	}
}
