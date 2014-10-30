#include <syslog.h>


int main()
{
	syslog(LOG_INFO|LOG_USER,"holy shit:%m");
	exit(0);
}
