#include "HashMap.h"

#include <stdio.h>

#include <time.h>

int main(int argc, char* argv[])
{
    hm dict;
    hm_initialize(&dict);

    char val[] = "default value for pairs";
    hm_fill(&dict, val, sizeof(val));

    hm_destroy(&dict);

    return 1;
}