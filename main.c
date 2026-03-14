/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:59:38 by flenski           #+#    #+#             */
/*   Updated: 2026/03/14 12:42:19 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stdlib.h>
#include <unistd.h>

/* Replaces the first newline with a null terminator
	and returns pointer to next char */
static char	*terminate_and_next(char *s)
{
	while (*s && *s != '\n')
		s++;
	if (*s == '\n')
		*s++ = '\0';
	return (s);
}

/* Pass 1: Count database entries and find where the search queries start */
static size_t	count_and_locate(char *buf, char **search_ptr)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (buf[i])
	{
		if (buf[i] == '\n' && buf[i + 1] == '\n')
		{
			buf[i] = '\0';
			*search_ptr = &buf[i + 2];
			return (count / 2 + 1);
		}
		if (buf[i] == '\n')
			count++;
		i++;
	}
	*search_ptr = &buf[i];
	return (count / 2);
}

/* Pass 2: Fill the map and then execute searches using the big buffer */
static void	process_data(char *buf, char *search_ptr, t_HashMap *hmap)
{
	char	*key;
	char	*val;

	while (buf && *buf)
	{
		key = buf;
		buf = terminate_and_next(key);
		val = buf;
		buf = terminate_and_next(val);
		hashmap_set(hmap, key, val);
	}
	while (search_ptr && *search_ptr)
	{
		key = search_ptr;
		search_ptr = terminate_and_next(key);
		val = (char *)hashmap_get(hmap, key);
		if (val)
		{
			write(1, val, ft_strlen(val));
			write(1, "\n", 1);
		}
		else
			write(1, "Not found\n", 10);
	}
}

int	main(void)
{
	char		*buf;
	char		*search_ptr;
	ssize_t		total;
	ssize_t		ret;
	t_HashMap	*hmap;

	buf = malloc(1024 * 1024 * 1024);
	if (!buf)
		return (1);
	total = 0;
	ret = read(0, buf, 1000000);
	while (ret > 0)
	{
		total += ret;
		ret = read(0, &buf[total], 1000000);
	}
	buf[total] = '\0';
	hmap = hashmap_create((count_and_locate(buf, &search_ptr) * 10) / 6);
	if (hmap)
		process_data(buf, search_ptr, hmap);
	hashmap_destroy(hmap);
	free(buf);
	return (0);
}
