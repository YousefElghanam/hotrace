/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 18:04:23 by flenski           #+#    #+#             */
/*   Updated: 2026/03/15 17:38:55 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <stddef.h>
#include <unistd.h>

void	buffered_flush(char *buf, size_t *pos)
{
	if (*pos)
	{
		write(1, buf, *pos);
		*pos = 0;
	}
}

void	buffered_write(const char *s, char *buf, size_t *pos)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		buf[*pos] = s[i++];
		(*pos)++;
		if (*pos == 32768)
			buffered_flush(buf, pos);
	}
}

void	buffered_out(const char *s, int flush, int nl)
{
	static char		buf[32768];
	static size_t	pos;

	buffered_write(s, buf, &pos);
	if (nl)
	{
		buf[pos++] = '\n';
		if (pos == 32768)
			buffered_flush(buf, &pos);
	}
	if (flush)
		buffered_flush(buf, &pos);
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

void	fill_map(char *buf, t_HashMap *hmap)
{
	char	*key;
	char	*val;

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
