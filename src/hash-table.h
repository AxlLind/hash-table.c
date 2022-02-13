#include <stdlib.h>

typedef struct {
  char *key;
  int val;
  char deleted;
} ht_node;

typedef struct {
  ht_node *table;
  size_t len;
  size_t capacity;
} ht_table;

int ht_insert(ht_table *table, char *key, int val);

int ht_remove(ht_table *table, char const *key);

int const* ht_get(ht_table *table, char const* key);

ht_table ht_create(void);

void ht_free(ht_table *table);
