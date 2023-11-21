#ifndef HASH
#define HASH

#include <stdio.h>
#include <ncurses.h>
#include "./types.h"

typedef struct entry {
  void *key;
  void *value;
  struct entry *next;
} Entry;

typedef struct hashtable {
  struct items_size {
    size_t key_s;
    size_t value_s;
  } items_size;

  size_t size;
  size_t length;
  Entry **buckets;
} HashTable;

HashTable *hs_create(size_t key_size, size_t value_size, size_t max_size);
void hs_free(HashTable*);

void  hs_insert(HashTable*, void *key, void *value);
Entry *hs_search(const HashTable *hs, const void *key);
void hs_delete(HashTable*, const void *key);

void hs_map(
  HashTable*,
  void (*callback)(Contact *, WINDOW *, int),
  WINDOW*
);

#endif // !HASH
