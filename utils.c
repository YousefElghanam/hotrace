/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:53:04 by flink             #+#    #+#             */
/*   Updated: 2026/03/15 19:36:42 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	if (!s)
	{
		return (0);
	}
	while (s[n])
		n++;
	return (n);
}

int	ft_streq(const char *a, const char *b)
{
	while (*a && *b)
	{
		if (*a != *b)
			return (0);
		a++;
		b++;
	}
	return (*a == *b);
}

char	*ft_strdup(const char *s)
{
	char	*out;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	out = malloc(len + 1);
	if (!out)
		return (0);
	i = -1;
	while (++i <= len)
		out[i] = s[i];
	return (out);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		d += len;
		s += len;
		while (len--)
			*--d = *--s;
	}
	return (dest);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (!*to_find)
		return (str);
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (str[i + j] && to_find[j] && str[i + j] == to_find[j])
				j++;
			if (!to_find[j])
				return (&str[i]);
		}
		i++;
	}
	return (0);
}
