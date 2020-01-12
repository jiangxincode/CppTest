#include <stdio.h>

void main()
{
	int i;
	int k;
	for(i = 0; i < 100; i++) {
		k = getchar();
		printf("%d\n", k);
	}
}

