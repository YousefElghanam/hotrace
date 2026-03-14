#include <stdio.h>

#define SIZE 100000

int	main(void)
{
	int	i;

	i = 0;
	while (i < SIZE)
	{
		printf("key %i\nvalue %i\n", i, i);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < SIZE)
	{
		printf("key %i\n", i);
		i++;
	}
}
