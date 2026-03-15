/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:52:50 by flink             #+#    #+#             */
/*   Updated: 2026/03/15 21:08:05 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// FNV-1a
uint64_t	hash_string(const char *s)
{
	const uint64_t	prime = 1099511628211ULL;
	uint64_t		h;

	h = 1469598103934665603ULL;
	while (*s && *(s + 1) && *(s + 2) && *(s + 3))
	{
		h = (h ^ (unsigned char)*s++) * prime;
		h = (h ^ (unsigned char)*s++) * prime;
		h = (h ^ (unsigned char)*s++) * prime;
		h = (h ^ (unsigned char)*s++) * prime;
	}
	while (*s)
		h = (h ^ (unsigned char)*s++) * 1099511628211ULL;
	return (h);
}

static size_t	next_pow2(size_t v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v |= v >> 32;
	return (++v);
}

t_HashMap	*hashmap_create(size_t capacity)
{
	t_HashMap	*map;
	size_t		i;

	map = malloc(sizeof(t_HashMap));
	if (!map)
		return (NULL);
	capacity = next_pow2(capacity);
	map->entries = malloc(sizeof(t_HashEntry) * capacity);
	if (!map->entries)
		return (free(map), NULL);
	i = 0;
	while (i < capacity)
	{
		map->entries[i].key = NULL;
		map->entries[i].value = NULL;
		map->entries[i].hash = 0;
		i++;
	}
	map->capacity = capacity;
	map->mask = capacity - 1;
	map->count = 0;
	return (map);
}

/* map->entries[i].key and value belong to the big buffer handled in main() */
void	hashmap_destroy(t_HashMap *map)
{
	if (!map)
		return ;
	free(map->entries);
	free(map);
}
