/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:52:58 by flenski           #+#    #+#             */
/*   Updated: 2026/03/13 19:53:50 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

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