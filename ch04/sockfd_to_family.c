#include "unp.h"

int sock_to_family(int fd)
{
	struct sockaddr_storage ss;
	socklen_t len;

	len = sizeof(ss);
	if(getsockname(fd,(SA *)&ss,&len) < 0)
		return(-1);
	return(ss.sin_family);
}
