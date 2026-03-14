#include "get_next_line.h"
#include "hashmap.h"
#include "hotrace.h"
#include <bits/time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#define E_EMPTY_LINE "Empty line read instead of value\n"
#define E_NOSEARCH "No keys provided to search for\n"
#define E_NOVAL "Each key needs a value on the following line\n"
#define E_MALLOC "Allocation failed\n"

void	ye_perror(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

int	read_db(t_HashMap *hmap)
{
	char	*key = NULL;
	char	*value = NULL;

	while (1)
	{
		key = get_next_line(STDIN_FILENO);
		if (!key)
			return (ye_perror(E_EMPTY_LINE), 1);
		if (ft_strlen(key) == 1 && key[0] == '\n')
			return (free(key), 0);

		value = get_next_line(STDIN_FILENO);
		if (!value)
			return (ye_perror(E_NOVAL), free(key), 1);
		if (ft_strlen(value) == 1 && value[0] == '\n')
			return (ye_perror(E_NOVAL), free(key), free(value), 1);
		key[ft_strlen(key) - 1] = 0;
		value[ft_strlen(value) - 1] = 0;
		// printf("inserting key %s and value %s\n", key, value);
		if (!hashmap_set(hmap, key, value))
			return (ye_perror(E_MALLOC), free(key), free(value), 1);
		free(key);
	}
	return (0);
}

int	search_db(t_HashMap *hmap)
{
	char	*key = NULL;
	char	*value = NULL;
	while (1)
	{
		key = get_next_line(STDIN_FILENO);
		if (!key)
			return (0);
		if (ft_strlen(key) == 1 && key[0] == '\n')
			return (free(key), 0);
		key[ft_strlen(key) - 1] = 0;
		value = (char *)hashmap_get(hmap, key);
		// printf("searching for %s =>", key);
		// fflush(stdout);
		// write(1, "value is: ", 10);
		write(1, value, ft_strlen(value));
		write(1, "\n", 1);
		// free(key);
	}
	return (0);
}

long	diff(struct timespec start, struct timespec end)
{
	return ((end.tv_sec - start.tv_sec) * 1000000000L
			+ end.tv_nsec - start.tv_nsec);
}

int	main(void)
{
	t_HashMap		*hmap;
	struct timespec	start;
	struct timespec	end;

	clock_gettime(CLOCK_MONOTONIC, &start);
	hmap = hashmap_create(1024);
	if (!hmap)
		return (ye_perror(E_MALLOC), 1);
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("hashmap_create time: %ld nanoseconds\n", diff(start, end) / 1000);

	clock_gettime(CLOCK_MONOTONIC, &start);
	if (read_db(hmap))
		return (hashmap_destroy(hmap), 1);
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("read_db time: %ld nanoseconds\n", diff(start, end) / 1000);

	clock_gettime(CLOCK_MONOTONIC, &start);
	if (search_db(hmap))
		return (hashmap_destroy(hmap), 1);
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("search_db time: %ld nanoseconds\n", diff(start, end) / 1000);
	return (hashmap_destroy(hmap), 0);
}
