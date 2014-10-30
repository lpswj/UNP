#include <stdio.h>
#include <stdlib.h>

char *GetMemory(void)
{
	char p[] = "hello world";
	return p;
}

void GetMemory2(char **p,int num)
{
	*p = (char *)malloc(num);
}

int main()
{
	char *str = (char *)malloc(100);
	strcpy(str,"hello");
	free(str);

	if(str != NULL)
	{
		strcpy(str,"world");
		printf(str);
	}
}
