/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flink <flink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:52:50 by flenski           #+#    #+#             */
/*   Updated: 2026/03/15 16:45:37 by flink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashmap.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

// wyhash
// static inline uint64_t mix(uint64_t a, uint64_t b)
// {
//     __uint128_t r = (__uint128_t)a * b;
//     return (uint64_t)r ^ (uint64_t)(r >> 64);
// }

// static inline uint64_t read64(const unsigned char *p)
// {
//     return *(const uint64_t*)p;
// }

// uint64_t hash_string(const char *s)
// {
//     const unsigned char *p = (const unsigned char*)s;
//     uint64_t seed = 0xa0761d6478bd642fULL;

//     while (p[0] && p[1] && p[2] && p[3] &&
//            p[4] && p[5] && p[6] && p[7])
//     {
//         uint64_t v = read64(p);
//         seed = mix(v ^ seed, 0xe7037ed1a0b428dbULL);
//         p += 8;
//     }

//     while (*p)
//         seed = mix(seed ^ *p++, 0xa0761d6478bd642fULL);

//     return seed;
// }

//xxHash
// static inline uint64_t	rotl(uint64_t x, int r)
// {
// 	return (x << r) | (x >> (64 - r));
// }

// uint64_t	hash_string(const char *s)
// {
// 	const unsigned char	*p = (const unsigned char *)s;
// 	uint64_t			h;
// 	uint64_t			v;

// 	h = 0x9e3779b185ebca87ULL;
// 	while (*p && p[1] && p[2] && p[3] && p[4] && p[5] && p[6] && p[7])
// 	{
// 		v = *(uint64_t *)p;
// 		h ^= v * 0xc2b2ae3d27d4eb4fULL;
// 		h = rotl(h, 31);
// 		h *= 0x9e3779b185ebca87ULL;
// 		p += 8;
// 	}
// 	while (*p)
// 	{
// 		h ^= *p++;
// 		h *= 0x100000001b3ULL;
// 	}
// 	return (h);
// }

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
