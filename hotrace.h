/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:02:12 by flenski           #+#    #+#             */
/*   Updated: 2026/03/14 12:02:13 by flenski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include "get_next_line.h"
# include "hashmap.h"
# include <stdint.h>

size_t		ft_strlen(const char *s);

uint64_t	hash_string(const char *s);
void		hashmap_destroy(t_HashMap *map);
t_HashMap	*hashmap_create(size_t capacity);
int			hashmap_delete(t_HashMap *map, const char *key);

t_HashEntry	*hashmap_probe(t_HashMap *map, const char *key, uint64_t hash);
void		resize_init(int i, size_t newcap, t_HashEntry *new_entries,
				t_HashMap *map);
int			hashmap_set(t_HashMap *map, const char *key, void *value);
void		*hashmap_get(t_HashMap *map, const char *key);

char		*get_next_line(int fd);

#endif /* HOTRACE_H */
