#include "HashMap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

hash_t hm_hash(uint8_t* bytes, int count)
{
    hash_t hash = 0;
    for (int i = 0; i < count; ++i) {
        hash += bytes[i];
    }
    return hash % HM_SIZE;
}

hash_t hm_hash_terminated(uint8_t* bytes)
{
    hash_t hash = 0;
    for (int i = 0; bytes[i]; ++i) {
        hash += bytes[i];
    }
    return hash;
}

void hm_initialize(hm* map)
{
    if (!map) {
        printf("invalid map passed to hm_initialize!");
        return;
    }

    map->buckets = (hm_bucket**)malloc(sizeof(hm_bucket*) * HM_SIZE);

    if (!map->buckets) {
        printf("failed to allocate memory for buckets!");
        return;
    }

    for (int i = 0; i < HM_SIZE; ++i) {
        map->buckets[i] = NULL;
    }

    map->count = 0;
    map->max_count = HM_SIZE;
}

void hm_destroy(hm* hm)
{
    if (!hm) {
        printf("null map passed into hm_destroy!");
        return;
    }

    if (!hm->buckets) {
        printf("hashmap buckets have already been destroyed.");
        return;
    }

    for (int i = 0; i < HM_SIZE; ++i) {
        hm_bucket* current = hm->buckets[i];
        if (current) {
            free(current);
        }
    }

    free(hm->buckets);
    hm->count = 0;
}

void hm_set(hm* map, const char* key, uint8_t* value, size_t size)
{
    hash_t hash = hm_hash_terminated(key);
    map->buckets[hash] = (hm_bucket*)malloc(sizeof(hm_bucket));

    if (!map->buckets[hash]) {
        printf("failed to allocate space for a new bucket!");
        return;
    }

    map->buckets[hash]->hash = hash;

    hm_value val = {
        value,
        size
    };

    memcpy(&map->buckets[hash]->value, &val, sizeof(hm_value));
    map->count++;
}

hm_bucket* hm_find(hm* map, const char* key)
{
    hash_t hash = hm_hash_terminated(key);
    return map->buckets[hash];
}

boolean hm_contains(hm* map, const char* key)
{
    hm_bucket* b = hm_find(map, key);
    return (b == NULL) ? False : True;
}