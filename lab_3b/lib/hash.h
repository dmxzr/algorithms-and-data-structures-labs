#ifndef HASH_H
#define HASH_H


#include <stdlib.h>
#include <stdio.h>
#include "key.h"
#include "table.h"

size_t hash_key_1(KeyType key);
size_t hash_key_2(KeyType key);
size_t hash(size_t max_size, KeyType key, size_t step);

#endif /* HASH_H */
