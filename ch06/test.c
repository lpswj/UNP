#include "unp.h"

struct card{
	int point;
	char color[10];
};

void main()
{
	struct card card1,card2;
	card1.point = 10;
	snprintf(card1.color,6,"Heart");

	card2 = card1;
	return;
}
