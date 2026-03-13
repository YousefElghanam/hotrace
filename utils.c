/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:53:04 by flenski           #+#    #+#             */
/*   Updated: 2026/03/13 19:56:48 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
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
