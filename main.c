/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:59:38 by flink             #+#    #+#             */
/*   Updated: 2026/03/15 21:53:35 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

static char	*exec_search(char *buf, t_HashMap *hmap, size_t *rem_len)
{
	char	*val;
	char	*n;
	char	*start;

	start = buf;
	while (*buf)
	{
		n = buf;
		while (*n && *n != '\n')
			n++;
		if (*n != '\n')
			break ;
		*n = '\0';
		val = (char *)hashmap_get(hmap, buf);
		if (val)
			buffered_out(val, 0, 1);
		else
			(buffered_out(buf, 0, 0), buffered_out(": Not found.", 0, 1));
		buf = n + 1;
	}
	*rem_len = ft_strlen(buf);
	return (buf);
}

static int	search_loop(char *rem, t_HashMap *hmap)
{
	char	*buf;
	ssize_t	ret;
	size_t	len;

	len = 0;
	if (*rem == '\n')
		return (1);
	buf = malloc(4294967296);
	if (!buf)
		return (write(2, "too big :(\n", 11), 1);
	rem = exec_search(rem, hmap, &len);
	ft_memmove(buf, rem, len);
	buffered_out(NULL, 1, 0);
	while (1)
	{
		ret = read(0, buf + len, 4294967295 - len);
		if (ret <= 0 || ret >= 4294967294
			|| *(buf + len) == '\n' || *buf == '\n')
			break ;
		buf[len + ret] = '\0';
		rem = exec_search(buf, hmap, &len);
		ft_memmove(buf, rem, len);
		buffered_out(NULL, 1, 0);
	}
	return (0);
}

static char	*get_db(char *buf, ssize_t tot)
{
	ssize_t	ret;
	ssize_t	i;

	while (1)
	{
		ret = read(0, buf + tot, 4294967296);
		if (ret <= 0 || (tot == 0 && *(buf + tot) == '\n') || ret >= 4294967294)
			return (write(2, "too big :(\n", 11), NULL);
		if (tot > 0)
			i = tot - 1;
		else
			i = 0;
		tot += ret;
		buf[tot] = '\0';
		while (i < tot - 1)
		{
			if (buf[i] == '\n' && buf[i + 1] == '\n')
			{
				buf[i] = '\0';
				return (buf + i + 2);
			}
			i++;
		}
	}
}

int	main(void)
{
	char		*buf;
	char		*search_ptr;
	t_HashMap	*hmap;
	size_t		lines;

	buf = malloc(4294967296);
	if (!buf)
		return (1);
	search_ptr = get_db(buf, 0);
	if (!search_ptr)
		return (free(buf), 0);
	lines = count_entries(buf);
	if (lines == 0)
	{
		free(buf);
		return (1);
	}
	hmap = hashmap_create(lines * 2);
	fill_map(buf, hmap);
	search_loop(search_ptr, hmap);
	hashmap_destroy(hmap);
	return (free(buf), 0);
}
