#ifndef TABLE_H
#define TABLE_H


#include <stdio.h>
#include <stdlib.h>
#include "key.h"
#include "hash.h"


enum table_errors {
	SUCCESS,
	ALLOC_ERROR,
	OVERFLOW_ERROR,
	KEY_NOT_FOUND,
	FILE_ERROR,
	SEARCH_ERROR,
	END
};

typedef struct Table {
	KeySpace *key_space; // указатель на 
	size_t max_size_key_space; // макс размер таблиы
	size_t len_key_space; // длина (кол-во элементов) таблцы
	size_t step; //шаг
} Table;


Table *create_table(size_t max_size_key_space);
void free_table(Table *table);
void print_table(Table *table);
Table *find_all_rel(Table *table, KeyType key);
int find_last_rel(Table *table, KeyType key);
int insert(Table *table, KeyType key, InfoType *info);
int delete(Table *table, KeyType key);
int read_table_from_file(Table *table, char *filename);
//int binary_search(Table *table, KeyType key);
int delete_all_release(Table *table, KeyType key);

#endif /* TABLE_H */
