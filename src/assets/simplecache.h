#pragma once
#ifndef SIMPLECACHE_H
#define SIMPLECACHE_H

struct SimpleCacheEntry {
    char filename[256];
    void* item;
    struct SimpleCacheEntry* next;
};

#define SIMPLE_CACHE_SIZE 50
struct SimpleCache {
    struct SimpleCacheEntry* table[SIMPLE_CACHE_SIZE];
};

void* simple_cache_get(struct SimpleCache* cache, const char* filename);
void simple_cache_put(struct SimpleCache* cache, const char* filename, void* item);

#endif //SIMPLECACHE_H
