void Listen(int fd,int backlog)
{
	char *ptr;

	if((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if(listen(fd,backlog) < 0)
		err_sys("listen error");

}
