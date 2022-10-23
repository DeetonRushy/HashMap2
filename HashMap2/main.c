#include "HashMap.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
    hm dict;
    hm_initialize(&dict);

    hm_set(&dict, "some key", "some value", 11);
    hm_set(&dict, "argc", argc, sizeof(int));
    hm_bucket* bucket = hm_find(&dict, "some key");

    if (!bucket) {
        printf("failed to find bucket..");
        return;
    }

    printf("value: %s\n", bucket->value.bytes);
    bucket = hm_find(&dict, "argc");

    printf("argc: %i\n", (int)bucket->value.bytes);

    hm_destroy(&dict);

    return 0;
}