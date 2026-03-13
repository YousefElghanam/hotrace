/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_funcs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:53:07 by flenski           #+#    #+#             */
/*   Updated: 2026/03/13 20:15:41 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stdint.h>

t_HashEntry	*hashmap_probe(t_HashMap *map, const char *key, uint64_t hash)
{
	size_t	i;

	i = hash & map->mask;
	while (map->entries[i].key)
	{
		if (map->entries[i].hash == hash && ft_streq(map->entries[i].key, key))
			return (&map->entries[i]);
		i = (i + 1) & map->mask;
	}
	return (&map->entries[i]);
}

static void	resize_init(ssize_t i, ssize_t newcap, t_HashEntry *new_entries,
		t_HashMap *map)
{
	while (++i < newcap)
	{
		new_entries[i].key = 0;
		new_entries[i].value = 0;
		new_entries[i].hash = 0;
	}
	map->entries = new_entries;
	map->capacity = newcap;
	map->mask = newcap - 1;
	map->count = 0;
}

// TODO Check if re-used cap variable does stupid stuff in case of errors
int	hashmap_resize(t_HashMap *map)
{
	ssize_t		cap;
	ssize_t		i;
	t_HashEntry	*new_entries;
	t_HashEntry	*old;
	t_HashEntry	*e;

	cap = map->capacity << 1;
	new_entries = malloc(sizeof(t_HashEntry) * cap);
	if (!new_entries)
		return (0);
	resize_init(-1, cap, new_entries, map);
	old = map->entries;
	cap = map->capacity;
	i = -1;
	while (++i < cap)
	{
		if (!old[i].key)
			continue ;
		e = hashmap_probe(map, old[i].key, old[i].hash);
		*e = old[i];
		map->count++;
	}
	free(old);
	return (1);
}

int	hashmap_set(t_HashMap *map, const char *key, void *value)
{
	uint64_t	hash;
	t_HashEntry	*e;

	if ((map->count * 10) / map->capacity > 7)
	{
		if (!hashmap_resize(map))
			return (0);
	}
	hash = hash_string(key);
	e = hashmap_probe(map, key, hash);
	if (!e->key)
	{
		e->key = ft_strdup(key);
		if (!e->key)
			return (0);
		e->hash = hash;
		map->count++;
	}
	e->value = value;
	return (1);
}

void	*hashmap_get(t_HashMap *map, const char *key)
{
	uint64_t	hash;
	size_t		i;

	hash = hash_string(key);
	i = hash & map->mask;
	while (map->entries[i].key)
	{
		if (map->entries[i].hash == hash && ft_streq(map->entries[i].key, key))
			return (map->entries[i].value);
		i = (i + 1) & map->mask;
	}
	return (0);
}
