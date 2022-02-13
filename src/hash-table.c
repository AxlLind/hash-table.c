#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "hash-table.h"

static size_t str_hash(char const *s) {
  size_t hash = 7;
  for (; *s; s++)
    hash = hash*31 + *s;
  return hash;
}

static int ht_insert_impl(ht_table *table, char *key, int val, int copy_key) {
  for (size_t h = str_hash(key); ; h++) {
    ht_node *node = table->table + (h % table->capacity);
    if (!node->key) {
      char *new_key = key;
      if (copy_key) {
        new_key = malloc(strlen(key)+1);
        strcpy(new_key, key);
      }
      *node = (ht_node) { .key=new_key, .val=val, .deleted=0 };
      table->len++;
      return 1;
    }
    if (strcmp(node->key, key) == 0)
      return 0;
  }
}

static void ht_expand(ht_table *table) {
  ht_node *old_table = table->table;
  size_t old_capacity = table->capacity;
  table->len = 0;
  table->capacity *= 2;
  table->table = calloc(table->capacity, sizeof(ht_node));
  for (size_t i = 0; i < old_capacity; i++) {
    ht_node *node = old_table + i;
    if (node->key)
      ht_insert_impl(table, node->key, node->val, 0);
  }
  free(old_table);
}

int ht_insert(ht_table *table, char *key, int val) {
  if (!ht_insert_impl(table, key, val, 1))
    return 0;
  if (table->len * 4 > table->capacity * 3)
    ht_expand(table);
  return 1;
}

int ht_remove(ht_table *table, char const *key) {
  for (size_t h = str_hash(key); ; h++) {
    ht_node *node = table->table + (h % table->capacity);
    if (node->deleted)
      continue;
    if (!node->key)
      return 0;
    if (strcmp(node->key, key) == 0) {
      free(node->key);
      *node = (ht_node) { .key=NULL, .val=0, .deleted=1 };
      table->len--;
      return 1;
    }
  }
}

int const* ht_get(ht_table *table, char const* key) {
  for (size_t h = str_hash(key); ; h++) {
    ht_node *node = table->table + (h % table->capacity);
    if (!node->key)
      return NULL;
    if (strcmp(node->key, key) == 0)
      return &node->val;
  }
}

ht_table ht_create(void) {
  return (ht_table) {
    .len = 0,
    .capacity = 8,
    .table = calloc(8, sizeof(ht_node)),
  };
}

void ht_free(ht_table *table) {
  for (size_t i = 0; i < table->capacity; i++)
    free(table->table[i].key);
  free(table->table);
}
