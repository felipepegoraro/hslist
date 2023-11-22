#ifndef HASH
#define HASH

#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "./types.h"

typedef struct entry {
  char *key;
  void *value;
  struct entry *next;
} Entry;

typedef struct hashtable {
  struct items_size {
    size_t value_s;
  } items_size;

  size_t size;
  size_t length;
  Entry **buckets;
} HashTable;

HashTable *hs_create(size_t value_size, size_t max_size);
void hs_free(HashTable*);

void hs_insert(HashTable*, const char *key, void *value);
Entry *hs_search(const HashTable *hs, const char *key);
void hs_delete(HashTable*, const char *key);

void hs_map(
  HashTable*,
  void (*callback)(Contact *, WINDOW *, int),
  WINDOW*
);

#endif // !HASH
