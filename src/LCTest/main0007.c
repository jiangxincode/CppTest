#include <stdio.h>

int main()
{
	int i;
	int k;
	for(i = 0; i < 100; i++) {
		k = getchar();
		printf("%d\n", k);
	}
    return 0;
}

