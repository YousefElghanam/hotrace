/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:04:23 by flenski           #+#    #+#             */
/*   Updated: 2026/03/14 19:54:28 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <unistd.h>

/* Global or static buffer for writing */
void	buffered_out(const char *s, int flush)
{
	static size_t	pos = 0;
	size_t			len;
	static char		out_buf[32768];

	if (flush)
	{
		write(1, out_buf, pos);
		pos = 0;
		return ;
	}
	len = ft_strlen(s);
	if (pos + len + 1 >= 32768)
	{
		write(1, out_buf, pos);
		pos = 0;
	}
	if (len + 1 >= 32768)
	{
		write(1, s, len);
		write(1, "\n", 1);
		return ;
	}
	while (*s)
		out_buf[pos++] = *s++;
	out_buf[pos++] = '\n';
}

/* Counts keys by counting newlines in the DB section */
size_t	count_entries(char *buf)
{
	size_t	lines;

	lines = 0;
	while (*buf)
	{
		if (*buf == '\n')
			lines++;
		buf++;
	}
	return (lines / 2);
}

static char	*terminate_and_next(char *s)
{
	while (*s && *s != '\n')
		s++;
	if (*s == '\n')
		*s++ = '\0';
	return (s);
}

void	fill_map(char *buf, t_HashMap *hmap)
{
	char	*key;
	char	*val;

	while (buf && *buf)
	{
		key = buf;
		buf = terminate_and_next(key);
		if (!*buf)
			break ;
		val = buf;
		buf = terminate_and_next(val);
		hashmap_set(hmap, key, val);
	}
}
