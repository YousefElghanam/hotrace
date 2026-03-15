/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:04:23 by flenski           #+#    #+#             */
/*   Updated: 2026/03/15 16:33:09 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <unistd.h>

/* Global or static buffer for writing */
void	buffered_out(const char *s, const int flush, int nl)
{
	static size_t	pos = 0;
	size_t			len;
	static char		out_buf[32768];

	if (s)
		len = ft_strlen(s);
	else
		len = 0;
	if (flush || pos + len + 1 >= 32768)
	{
		write(1, out_buf, pos);
		if (len + 1 >= 32768)
			write(1, "\n", 1);
		pos = 0;
		return ;
	}
	while (*s)
		out_buf[pos++] = *s++;
	if (nl == 1)
		out_buf[pos++] = '\n';
}

/* Counts keys by counting newlines in the DB section */
size_t	count_entries(const char *buf)
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

void fill_map(char *buf, t_HashMap *hmap)
{
	char    *key;
	char    *val;

	while (*buf)
	{
		key = buf;
		while (*buf && *buf != '\n')
			buf++;
		if (*buf)
			*buf++ = '\0';
		val = buf;
		while (*buf && *buf != '\n')
			buf++;
		if (*buf)
			*buf++ = '\0';
		hashmap_set(hmap, key, val);
	}
}
