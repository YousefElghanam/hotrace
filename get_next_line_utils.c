/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 11:59:53 by flenski           #+#    #+#             */
/*   Updated: 2026/03/14 11:59:53 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (free(s1), NULL);
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	free(s1);
	return (res);
}
