#include "unp.h"

int main(int argc,char **argv)
{
	char ip[INET_ADDRSTRLEN];
	char ip1[INET_ADDRSTRLEN];
	char *new_ip;
	struct sockaddr_in serv;

	strcpy(ip,"192.168.1.1");
	inet_pton(AF_INET,ip,&serv.sin_addr);

	new_ip = inet_ntop(AF_INET,&serv.sin_addr,ip1,sizeof(ip1));
	printf("%s\n",ip1);



}

