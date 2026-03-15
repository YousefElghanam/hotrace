/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:52:58 by flink             #+#    #+#             */
/*   Updated: 2026/03/15 19:37:06 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include <stdint.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_hashentry
{
	char		*key;
	void		*value;
	uint64_t	hash;
}				t_HashEntry;

typedef struct s_hashmap
{
	t_HashEntry	*entries;
	size_t		capacity;
	size_t		count;
	size_t		mask;
}				t_HashMap;

int				ft_streq(const char *a, const char *b);
uint64_t		hash_string(const char *s);
char			*ft_strdup(const char *s);

#endif