#include "hash.h"


size_t hash_key_1(KeyType key){
	key = (key ^ (key >> 30)) * 0xbf58476d1ce4e5b9ULL;
	key = (key ^ (key >> 27)) * 0x94d049bb133111ebULL;
	key = key ^ (key >> 31);
	return key;
}

size_t hash_key_2(KeyType key){
	for(int i = 0; i < 8; ++i){
		key ^= (key >> (i+1)); // XOR с побитовым сдвигом
		key *= 0x27d4eb2f165667c5ULL;  // Умножение на большую константу
		key ^= (key << (i + 1));// XOR с побитовым сдвигом в другую сторону
	}
	return key;
}


size_t hash(size_t max_size, KeyType key, size_t step){
	return ((hash_key_1(key) + step*hash_key_2(key)))%(max_size);
}
