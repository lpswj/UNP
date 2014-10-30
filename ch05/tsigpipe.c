//ex5.6
//A SIGPIPE example 
#include "unp.h"

//signaction handler for SIGPIPE
void sig_pipe(int signo)
{
	printf("in sig_pipe\n");
	return;
}

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2)
		err_quit("usage:tcpcli < IPaddress >");

	sockfd = Socket(AF_INET,SOCK_STREAM,0);
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(13);
	Inet_pton(AF_INET,argv[1],&servaddr.sin_addr);

	Signal(SIGPIPE,sig_pipe);
	Connect(sockfd,(SA *)&servaddr,sizeof(servaddr));
	//wait for the server send daytime and FIN to close
	sleep(2);
	//the first write to server,server response with RST
	Writen(sockfd,"hello",5);
	//wait for the server RST
	sleep(2);
	//cause the SIGPIPE signal
	Writen(sockfd,"world",5);
	
	exit(0);
}
