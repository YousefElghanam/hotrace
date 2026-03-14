/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:59:38 by flenski           #+#    #+#             */
/*   Updated: 2026/03/14 19:21:09 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <unistd.h>

static char	*exec_search(char *buf, t_HashMap *hmap, size_t *rem_len)
{
	char	*val;
	char	*n;

	while (buf && *buf)
	{
		n = buf;
		while (*n && *n != '\n')
			n++;
		if (*n == '\n')
		{
			*n = '\0';
			val = (char *)hashmap_get(hmap, buf);
			if (val)
				buffered_out(val, 0);
			else
				buffered_out("Not found", 0);
			buf = n + 1;
		}
		else
			break ;
	}
	*rem_len = 0;
	if (buf && *buf)
		while (buf[*rem_len])
			(*rem_len)++;
	return (buf);
}

static void	search_loop(char *rem, t_HashMap *hmap)
{
	char	buf[16384];
	ssize_t	ret;
	size_t	len;

	rem = exec_search(rem, hmap, &len);
	ft_memmove(buf, rem, len);
	buffered_out(NULL, 1);
	while (1)
	{
		ret = read(0, buf + len, 16383 - len);
		if (ret <= 0)
			break ;
		buf[len + ret] = '\0';
		rem = exec_search(buf, hmap, &len);
		ft_memmove(buf, rem, len);
		buffered_out(NULL, 1);
	}
}

static char	*get_db(char *buf)
{
	ssize_t	ret;
	int		tot;
	int		i;

	tot = 0;
	while (1)
	{
		ret = read(0, buf + tot, 1048576);
		if (ret <= 0)
			return (NULL);
		i = (tot > 0) ? tot - 1 : 0;
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

	buf = malloc(1024 * 1024 * 512);
	if (!buf)
		return (1);
	search_ptr = get_db(buf);
	if (!search_ptr)
		return (free(buf), 0);
	hmap = hashmap_create(count_entries(buf) * 2);
	fill_map(buf, hmap);
	search_loop(search_ptr, hmap);
	hashmap_destroy(hmap);
	return (free(buf), 0);
}
