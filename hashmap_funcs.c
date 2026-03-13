/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:52:50 by flenski           #+#    #+#             */
/*   Updated: 2026/03/13 22:13:06 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t	hash_string(const char *s)
{
	uint64_t	h;

	h = 1469598103934665603ULL;
	while (*s)
	{
		h ^= (unsigned char)*s++;
		h *= 1099511628211ULL;
	}
	return (h);
}

static size_t	next_pow2(size_t v)
{
	size_t	p;

	p = 1;
	while (p < v)
		p <<= 1;
	return (p);
}

t_HashMap	*hashmap_create(size_t capacity)
{
	t_HashMap	*map;
	size_t		i;

	map = malloc(sizeof(t_HashMap));
	if (!map)
		return (0);
	capacity = next_pow2(capacity);
	map->entries = malloc(sizeof(t_HashEntry) * capacity);
	if (!map->entries)
	{
		free(map);
		return (0);
	}
	i = -1;
	while (++i < capacity)
	{
		map->entries[i].key = 0;
		map->entries[i].value = 0;
		map->entries[i].hash = 0;
	}
	map->capacity = capacity;
	map->mask = capacity - 1;
	map->count = 0;
	return (map);
}

void	hashmap_destroy(t_HashMap *map)
{
	size_t	i;

	if (!map)
		return ;
	i = -1;
	while (++i < map->capacity)
		if (map->entries[i].key)
		{
			free(map->entries[i].key);
			free(map->entries[i].value);
		}
	free(map->entries);
	free(map);
}

int	hashmap_delete(t_HashMap *map, const char *key)
{
	uint64_t	hash;
	size_t		i;

	hash = hash_string(key);
	i = hash & map->mask;
	while (map->entries[i].key)
	{
		if (map->entries[i].hash == hash && ft_streq(map->entries[i].key, key))
		{
			free(map->entries[i].key);
			map->entries[i].key = 0;
			map->entries[i].value = 0;
			map->entries[i].hash = 0;
			map->count--;
			return (1);
		}
		i = (i + 1) & map->mask;
	}
	return (0);
}
