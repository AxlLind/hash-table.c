#include <stdio.h>
#include <assert.h>
#include "hash-table.h"

int main() {
  printf("Testing hash table\n");
  ht_table table = ht_create();

  assert(ht_insert(&table, "a", 0));
  assert(ht_insert(&table, "ab", 1));
  assert(ht_insert(&table, "abc", 2));
  assert(ht_insert(&table, "abcd", 3));
  assert(ht_insert(&table, "abcde", 4));
  assert(ht_insert(&table, "abcdef", 5));
  assert(ht_insert(&table, "abcdefg", 6));
  assert(ht_insert(&table, "abcdefgh", 7));
  assert(ht_insert(&table, "abcdefghi", 8));
  assert(ht_insert(&table, "abcdefghij", 9));
  assert(!ht_insert(&table, "abcdefghij", 10));
  assert(table.len == 10);

  assert(*ht_get(&table, "a") == 0);
  assert(*ht_get(&table, "ab") == 1);
  assert(*ht_get(&table, "abc") == 2);
  assert(*ht_get(&table, "abcd") == 3);
  assert(*ht_get(&table, "abcde") == 4);
  assert(*ht_get(&table, "abcdef") == 5);
  assert(*ht_get(&table, "abcdefg") == 6);
  assert(*ht_get(&table, "abcdefgh") == 7);
  assert(*ht_get(&table, "abcdefghi") == 8);
  assert(*ht_get(&table, "abcdefghij") == 9);
  assert(ht_get(&table, "aklsjdlkas") == NULL);

  assert(ht_remove(&table, "a"));
  assert(ht_remove(&table, "ab"));
  assert(ht_remove(&table, "abc"));
  assert(ht_remove(&table, "abcd"));
  assert(ht_remove(&table, "abcde"));
  assert(ht_remove(&table, "abcdef"));
  assert(ht_remove(&table, "abcdefg"));
  assert(ht_remove(&table, "abcdefgh"));
  assert(ht_remove(&table, "abcdefghi"));
  assert(ht_remove(&table, "abcdefghij"));
  assert(!ht_remove(&table, "dsajlke"));
  assert(table.len == 0);

  ht_free(&table);
}
