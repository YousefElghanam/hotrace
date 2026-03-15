#include <stdio.h>

#define SIZE 1000000

int main()
{
	int i = -1;

	while(++i < SIZE)
		printf("key %i\nvalue %i\n", i, i);
	printf("\n");
	i = 0;
	while(++i < SIZE)
		printf("key %i\n", i);
}
