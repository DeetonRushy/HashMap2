#pragma once
#include <stddef.h>

#define HM_SIZE 5000
#define HM_FILL_DEFAULT -1

typedef unsigned char uint8_t;
typedef unsigned long long hash_t;

typedef enum { False, True } boolean;

typedef struct {
    uint8_t* bytes;
    size_t size;
} hm_value;
typedef struct {
    hash_t hash;
    hm_value value;
} hm_bucket;
typedef struct {
    hm_bucket** buckets;
    size_t count;
    size_t max_count;
} hm;

hash_t hm_hash(uint8_t* bytes, int count);
hash_t hm_hash_terminated(uint8_t* bytes);

void hm_initialize(hm*);
void hm_destroy(hm*);
void hm_fill(hm*, uint8_t* value, size_t size);

// usage

void hm_set(hm* map, const char* key, uint8_t* value, size_t size);

hm_bucket* hm_find(hm* map, const char* key);
boolean hm_contains(hm* map, const char* key);

// helpers

void hm_initialize_then_fill(hm* map, uint8_t* value, size_t size);
boolean hm_try_find(hm* map, const char* key, hm_bucket* bucket);
