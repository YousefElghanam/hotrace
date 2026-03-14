/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_funcs2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flenski <flenski@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:53:07 by flenski           #+#    #+#             */
/*   Updated: 2026/03/14 12:20:08 by flenski          ###   ########.fr       */
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

int	hashmap_set(t_HashMap *map, const char *key, void *value)
{
	uint64_t	hash;
	t_HashEntry	*e;

	hash = hash_string(key);
	e = hashmap_probe(map, key, hash);
	if (!e->key)
	{
		e->key = (char *)key;
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
		if (map->entries[i].hash == hash)
		{
			if (ft_streq(map->entries[i].key, key))
				return (map->entries[i].value);
		}
		i = (i + 1) & map->mask;
	}
	return (NULL);
}
