#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "./UI.h"
#include "./types.h"
#include "./hash_table.h"

HashTable *hs_create(size_t value_size, size_t max_size)
{
  HashTable *hs  = (HashTable *)malloc(sizeof(HashTable));
  hs->size       = max_size;
  hs->length     = 0;
  hs->buckets    = (Entry **)calloc(max_size, sizeof(Entry *));
  hs->items_size.value_s = value_size;
  return hs;
}

static void hs_free_item(Entry *en){
  free(en->key);
  free(en->value);
  free(en);
}

void hs_free(HashTable *hs){
  for (size_t i = 0; i < hs->size; ++i) {
    Entry *current = hs->buckets[i];
    while (current != NULL)
    {
      Entry *aux = current;
      current = current->next;
      hs_free_item(aux);
    }
  }
  free(hs->buckets);
  free(hs);
}

static Entry *hs_create_item(const char *key, size_t value_size, void *value)
{
  Entry *ret = (Entry *)malloc(sizeof(Entry));

  ret->key = strdup(key);

  ret->value = malloc(value_size);
  memcpy(ret->value, value, value_size);

  ret->next = NULL;

  return ret;
}

unsigned char *hs_hash(const char *key)
{
  unsigned char *hash = (unsigned char*)malloc(SHA256_DIGEST_LENGTH);
  SHA256((unsigned const char*)key, strlen(key), hash);
  return hash;
}

void hs_free_hash(unsigned char* hash)
{
  free(hash);
}

size_t hs_get_index(const char *key, size_t hs_size)
{
  unsigned char *hash = hs_hash(key);
  size_t ret = hash[0] % hs_size;
  hs_free_hash(hash);
  return ret;
}

void hs_insert(HashTable *hs, const char *key, void *value)
{
  size_t index = hs_get_index(key, hs->size);

  Entry *new = hs_create_item(key, hs->items_size.value_s, value);

  mvprintw(20, 2, "[%zu]", index);

  if (hs->buckets[index] == NULL) {
    hs->buckets[index] = new;
  } else {
    Entry *current = hs->buckets[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new;
  }

  hs->length++;
}

Entry *hs_search(const HashTable *hs, const char *key)
{
  size_t index = hs_get_index(key, hs->size);
  Entry *current = hs->buckets[index];

  while (current != NULL)
  {
    if (strcmp(current->key, key) == 0)
      return current;
    current = current->next;
  }

  return NULL;
}

bool hs_delete(HashTable *hs, const char *key)
{
  if (hs->length == 0) return false;
  size_t index = hs_get_index(key, hs->size);

  Entry *current = hs->buckets[index];
  Entry *prev = NULL;

  while (current != NULL)
  {
    if (strcmp(current->key, key) == 0)
    {
      if (prev == NULL) hs->buckets[index] = current->next;
      else prev->next = current->next;

      hs_free_item(current);

      hs->length--;
      return true;
    }

    prev = current;
    current = current->next;
  }

  return false;
}

void hs_map(
  HashTable *hs,
  void (*callback)(Contact *, WINDOW *, int),
  WINDOW *window
){
  int idx = 0;
  
  for (size_t i = 0; i < hs->size; i++)
  {
    Entry *entry = hs->buckets[i];
    
    while (entry != NULL)
    {
      Contact *contact = (Contact *)entry->value;
      
      callback(contact, window, idx);
      idx++;
      entry = entry->next;
    }
  }
}
