#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "hash-table.h"

#define ALPHABET "abcdefghijklmnopqrstuvwxyz"

void rand_str(char *s, int n) {
  int i;
  for (i = 0; n > 0; i++) {
    s[i] = ALPHABET[n % 26];
    n /= 26;
  }
  s[i] = 0;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));
  int ops = 100000, insertions = 0, deletions = 0;
  if (argc == 2)
    sscanf(argv[1], "%d", &ops);
  printf("Running fuzz test with %d operations.\n", ops);
  ht_table table = ht_create();
  char s[5];
  for (int i = 0; i < ops; i++) {
    int n = rand() >> 17;
    rand_str(s, n>>1);
    if (n & 1) {
      ht_insert(&table, s, n);
      insertions++;
      assert(ht_get(&table, s));
    } else {
      ht_remove(&table, s);
      deletions++;
      assert(!ht_get(&table, s));
    }
  }
  printf("[passed] Successfully performed %d operations on hashtable!\n", ops);
  printf("         size=%ld, insertions=%d, deletions=%d\n", table.len, insertions, deletions);
  ht_free(&table);
}
