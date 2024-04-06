#include <stddef.h>
#include <string.h>
#include <malloc.h>
#include "simplecache.h"

unsigned int simple_cache_hash(const char* filename) {
    unsigned int hash = 0;
    while (*filename) {
        hash = (hash * 31) + *filename++;
    }
    return hash % SIMPLE_CACHE_SIZE;
}

void* simple_cache_get(struct SimpleCache* cache, const char* filename) {
    unsigned int index = simple_cache_hash(filename);

    struct SimpleCacheEntry* entry = cache->table[index];
    while (entry != NULL) {
        if (strcmp(entry->filename, filename) == 0) {
            return entry->item;
        }
        entry = entry->next;
    }
    return NULL;
}

void simple_cache_put(struct SimpleCache* cache, const char* filename, void* item) {
    unsigned int index = simple_cache_hash(filename);

    struct SimpleCacheEntry* entry = malloc(sizeof(struct SimpleCacheEntry));

    strcpy(entry->filename, filename);
    entry->item = item;

    entry->next = cache->table[index];
    cache->table[index] = entry;
}