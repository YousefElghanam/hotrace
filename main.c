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

#define E_EMPTY_VAL "Empty line read instead of value\n"
#define E_NOSEARCH "No keys provided to search for\n"
#define E_NOVAL "Each key needs a value on the following line\n"
#define E_MALLOC "Allocation failed\n"
#define E_TOOBIG_INPUT "Input is too big\n"

void	ye_perror(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}

int	parse_key_value(t_HashMap *hmap, char *buf, ssize_t bytes_read)
{
	ssize_t	i;
	ssize_t	len;
	char	*key;
	char	*value;

	i = 0;
	while (i < bytes_read)
	{
		len = 0;
		while (i < bytes_read)
		{
			if (buf[i] == '\n')
			{
				if (len == 0)
					return (printf("found empty line\n"), 0);
				break ;
			}
			len++;
			i++;
		}
		if (buf[i] != '\n')
			return (ye_perror("Missing newline while reading key\n"), 1);
		buf[i] = '\0';
		key = &buf[i - len];
		printf("read key (%s)\n", key);


		// "key\0val\0"
		len = 0;
		i++;
		while (i < bytes_read)
		{
			if (buf[i] == '\n')
			{
				if (len == 0)
					return (ye_perror(E_EMPTY_VAL), 1);
				break ;
			}
			len++;
			i++;
		}
		if (buf[i] != '\n')
			return (ye_perror("Missing newline while reading value\n"), 1);
		buf[i] = '\0';
		value = &buf[i - len];
		printf("read value (%s)\n", value);
		if (!hashmap_set(hmap, key, ft_strdup(value)))
			return (ye_perror(E_MALLOC), 1);
		i++;
	}
	return (0);
}

int	read_input(t_HashMap *hmap, char *buf)
{
	// char	*key = NULL;
	// char	*value = NULL;
	ssize_t	bytes_read;

	bytes_read = read(STDIN_FILENO, buf, BUF_SIZE);
	if (bytes_read == -1 || bytes_read > BUF_SIZE)
		return (ye_perror(E_TOOBIG_INPUT), 1);
	buf[bytes_read] = '\0';
	if (parse_key_value(hmap, buf, bytes_read))
		return (1);
	return (0);
	// while (1)
	// {
	// 	key = get_next_line(STDIN_FILENO);
	// 	if (!key)
	// 		return (ye_perror(E_EMPTY_VAL), 1);
	// 	if (ft_strlen(key) == 1 && key[0] == '\n')
	// 		return (free(key), 0);

	// 	value = get_next_line(STDIN_FILENO);
	// 	if (!value)
	// 		return (ye_perror(E_NOVAL), free(key), 1);
	// 	if (ft_strlen(value) == 1 && value[0] == '\n')
	// 		return (ye_perror(E_NOVAL), free(key), free(value), 1);
	// 	key[ft_strlen(key) - 1] = 0;
	// 	value[ft_strlen(value) - 1] = 0;
	// 	// printf("inserting key %s and value %s\n", key, value);
	// 	if (!hashmap_set(hmap, key, value))
	// 		return (ye_perror(E_MALLOC), free(key), free(value), 1);
	// 	free(key);
	// }
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
	char			*buf;

	clock_gettime(CLOCK_MONOTONIC, &start);
	hmap = hashmap_create(1024000);
	if (!hmap)
		return (ye_perror(E_MALLOC), 1);
	clock_gettime(CLOCK_MONOTONIC, &end);
	printf("hashmap_create time: %ld nanoseconds\n", diff(start, end) / 1000);

	buf = malloc(BUF_SIZE + 1);
	if (!buf)
		return (ye_perror(E_MALLOC), 1);
	// clock_gettime(CLOCK_MONOTONIC, &start);
	if (read_input(hmap, buf))
		return (free(buf), hashmap_destroy(hmap), 1);
	// clock_gettime(CLOCK_MONOTONIC, &end);
	// printf("read_input time: %ld nanoseconds\n", diff(start, end) / 1000);

	// clock_gettime(CLOCK_MONOTONIC, &start);
	// if (search_db(hmap, buf))
	// 	return (hashmap_destroy(hmap), 1);
	// clock_gettime(CLOCK_MONOTONIC, &end);
	// printf("search_db time: %ld nanoseconds\n", diff(start, end) / 1000);
	return (free(buf), hashmap_destroy(hmap), 0);
}
