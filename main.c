#include "get_next_line.h"
#include "hotrace.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#define E_EMPTY_LINE "Empty line read instead of value\n"
#define E_NOSEARCH "No keys provided to search for\n"
#define E_NOVAL "Each key needs a value on the following line\n"

void	ye_perror(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

int	read_db(void)
{
	char	*key = NULL;
	char	*value = NULL;
	while (1)
	{
		key = get_next_line(STDIN_FILENO);
		if (!key)
			return (ye_perror(E_EMPTY_LINE), 0);
		if (ft_strlen(key) == 1 && key[0] == '\n')
			return (free(key), 0);

		value = get_next_line(STDIN_FILENO);
		if (!value)
			return (ye_perror(E_NOVAL), free(key), 1);
		if (ft_strlen(value) == 1 && value[0] == '\n')
			return (ye_perror(E_NOVAL), free(value), 1);
		// add (key, value) pair to hash map;
		(free(key), free(value));
	}
	return (0);
}

int	main(void)
{
	if (read_db())
		return (1);
	return (0);
}
