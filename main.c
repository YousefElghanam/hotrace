/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:59:38 by flenski           #+#    #+#             */
/*   Updated: 2026/03/14 18:49:09 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <unistd.h>

static char	*exec_search(char *buf, t_HashMap *hmap)
{
	char	*val;
	char	*next;

	while (buf && *buf)
	{
		next = buf;
		while (*next && *next != '\n')
			next++;
		if (*next == '\n')
		{
			*next = '\0';
			val = (char *)hashmap_get(hmap, buf);
			if (val)
				buffered_out(val, 0);
			else
				buffered_out("Not found", 0);
			buf = next + 1;
		}
		else
			break ;
	}
	return (buf);
}

static void	search_loop(char *leftover, t_HashMap *hmap)
{
	char	*rem;
	ssize_t	ret;
	size_t	len;
	char	buf[16384];

	rem = exec_search(leftover, hmap);
	len = ft_strlen(rem);
	ft_memmove(buf, rem, len);
	while (1)
	{
		ret = read(0, buf + len, 16383 - len);
		if (ret <= 0)
			break ;
		buf[len + ret] = '\0';
		rem = exec_search(buf, hmap);
		len = ft_strlen(rem);
		ft_memmove(buf, rem, len);
	}
	buffered_out(NULL, 1);
}

static void	get_search_ptr(char **buf, char **search_ptr)
{
	ssize_t	ret;
	int		total;

	total = 0;
	*search_ptr = NULL;
	while (1)
	{
		ret = read(0, *buf + total, 1024 * 1024);
		if (ret <= 0)
			break ;
		total += ret;
		(*buf)[total] = '\0';
		*search_ptr = ft_strstr(*buf, "\n\n");
		if (*search_ptr)
			break ;
	}
}

int	main(void)
{
	char		*buf;
	char		*search_ptr;
	t_HashMap	*hmap;

	search_ptr = NULL;
	buf = malloc(1024 * 1024 * 1024);
	if (!buf)
		return (1);
	get_search_ptr(&buf, &search_ptr);
	if (!search_ptr)
		return (free(buf), 0);
	*search_ptr = '\0';
	search_ptr += 2;
	hmap = hashmap_create(count_entries(buf) * 2);
	fill_map(buf, hmap);
	search_loop(search_ptr, hmap);
	hashmap_destroy(hmap);
	return (free(buf), 0);
}
