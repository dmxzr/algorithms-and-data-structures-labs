#include "table.h"
#include "key.h"
#include "readfile.h"
#include <string.h>

Table *create_table(size_t max_size_key_space){
	if(max_size_key_space == 0) return NULL;

	Table *table = (Table *)malloc(sizeof(Table));
	if(table == NULL) return NULL;

	table->len_key_space = 0;
	table->max_size_key_space = max_size_key_space;
	table->key_space = (KeySpace *)malloc((max_size_key_space+1)* sizeof(KeySpace));

	if(table->key_space == NULL){
		free(table);
		return NULL;
	}
	return table;
}

//коряво добавляется релиз
int insert(Table *table, KeyType key, InfoType info){
	if(table == NULL) return ALLOC_ERROR;

	if(table->len_key_space == table->max_size_key_space) return OVERFLOW_ERROR;

	int index = binary_search(table, key);
	printf("индекс %d, ключ %llu, инфо %llu\n", index, key, info);
	ULLI release = 0;
	if(index == -1) index = (table->len_key_space);

	// иду вправо +1 пока не надйу макс релиз


	while(table->key_space[index].key == key){
		release=table->key_space[index].release;
		index++
	}
	release++;

	printf("индекс итог %d \n", index);
	
	(table->len_key_space)++;
	for(int i =  table->len_key_space - 1; i >= index; i-- ){
		table->key_space[i+1] = table->key_space[i];	
	}

	
	table->key_space[index].key = key;
	table->key_space[index].release = release;
	table->key_space[index].info = info;
	//memcpy(table->key_space[index].info ,info, 1);	
	//printf("инфо добавление: %llu\n", *(table->key_space[index].info));
	
	return SUCCESS;
}

//ready
int delete(Table *table, KeyType key, RelType release){
	if(table == NULL) return ALLOC_ERROR;

	if(table->len_key_space == 0) return ALLOC_ERROR;

	//делаем бин поиск, находим какой-то элемент с релизом,смотрим на его релиз, если он больше чем заданный, то двигаемся влево, иначе вправго, и так, пока не надйем нужный релиз, либо не перескочим его -> этот релиз отсутствует
	

	int index = binary_search(table, key);
	if(index == -1) return KEY_NOT_FOUND;


		
	if(table->key_space[index].release < release) {
		while(table->key_space[index].release != release && table->key_space[index].key == key) {
			index++;
			
			}
		if(table->key_space[index].release != release){
			return REL_NOT_FOUND;
		}
	}
	else
		if(table->key_space[index].release > release) {
			while(table->key_space[index].release != release && table->key_space[index].key == key) {
				index--;
				}
			if(table->key_space[index].release != release){
				return REL_NOT_FOUND;
			}
		}
		
	
		

	
	
	for(size_t i = index; i < table->len_key_space; i++ ){
			table->key_space[i] = table->key_space[i+1];
		}
	
	/*free(table->key_space[table->len_key_space].info);
	table->key_space[table->len_key_space].key = 0;
	table->key_space[table->len_key_space].release = 0;*/
	(table->len_key_space)--;
	//free(table->key_space[table->len_key_space -1].info);
	return SUCCESS;
	
	
}

//
int delete_all_release(Table *table, KeyType key){
	if(table == NULL) return ALLOC_ERROR;

	if(table->len_key_space == 0) return ALLOC_ERROR;
	
	int index = binary_search(table, key);
	if(index == -1) return KEY_NOT_FOUND;
	//printf("index: %d\n", index);

	// используем бин поиск. нашли релиз, уходим налево, получая индекс наименьшего релиза, потом идем вправо до макс релиза, удаляя все элементы
	
	while(table->key_space[index].key == key){
		if(index - 1 >= 0 ) index--;
		else break;
		printf("%d\n", index);
	}
	
	while(table->key_space[index].key == key ){
		//printf("j = %d\n", j);
		for(size_t i = index; i < table->len_key_space; i++ ){
			table->key_space[i] = table->key_space[i+1];
		}
	
	/*free(table->key_space[table->len_key_space].info);
	table->key_space[table->len_key_space].key = 0;
	table->key_space[table->len_key_space].release = 0;*/
	(table->len_key_space)--;
	//free(table->key_space[table->len_key_space -1].info);
	

	}
	return SUCCESS;
	
		
}
 

void free_table(Table *table){
	if(table == NULL) return;

	//for(size_t i = 0; i < table->len_key_space; i++){
	//	free(table->key_space[i].info);
	//}
	free(table->key_space);
	free(table);
	return;
}


int binary_search(Table *table, KeyType key){
	if(table->len_key_space == 0) return 0;
	size_t left = 0;
	size_t right = (table->len_key_space) -1;
	while(left <= right){
		size_t mid = (left+right)/2;
		if(table->key_space[mid].key  == key) {
			return mid;
		}
		else {if(table->key_space[mid].key > key){
			right = mid - 1;	
		}
		else{
			left = mid + 1;
		}
	} 
	}
	return -1;
	
}


void print_table(Table *table){
	if(table == NULL) return;

	if(table->max_size_key_space == 0){
		printf("table is empty\n");
		return;
	}
	
	printf("\t TABLE: \n");
	printf("key     	release	 	info\n");
	for(size_t i = 0; i < table->len_key_space; i++){
		printf("%llu		", table->key_space[i].key);
		printf("%llu 		", table->key_space[i].release);
		printf("%llu\n", table->key_space[i].info);
	}
	for(size_t i = table->len_key_space; i < table->max_size_key_space; i++){
		printf("0		-		-\n");
	}
	printf("\n");
	return;
	
}
//
Table *find_all_rel(Table *table, KeyType key){
	if(table == NULL || table->len_key_space == 0) return NULL;

	size_t size = table->max_size_key_space;

	Table *elements = create_table(size);

	if(elements == NULL) return NULL;
	//	бин поиском находим какой-то элемент, идем влево до минимального релиза, заносим в таблицу все последующие до максимального
	int index = binary_search(table, key);

	while(table->key_space[index].key == key ){
		if(index - 1 >= 0 ) index--;
		else break;
	}


	
	for(size_t i = index; table->key_space[i].key == key; i++){
			printf("%llu\n", table->key_space[i].key);
			insert(elements, key, table->key_space[i].info);
		
	}
	if(index == -1){
		free_table(elements);
		return NULL;
	}
	
	
	return elements;

	
}





int read_table_from_file(Table *table, char *filename){
	if(table == NULL) return ALLOC_ERROR;

	char *str = NULL;
	FILE *file = fopen(filename, "r");

	if(file == NULL) return FILE_ERROR;
	char *key = NULL;
	char *info = NULL;

	str = file_readline(file);
	
	while(str!= NULL){
		//printf("%s\n", str);
		key = strtok(str, DELIM);
		info = strtok(NULL, DELIM);

		insert(table, (ULLI)(atoi(key)) ,(ULLI)(atoi(info)));
		//table->key_space[table->len_key_space].key = (ULLI)(atoi(key));
	//	table->key_space[table->len_key_space].info = (ULLI)(atoi(info));
		//(table->len_key_space)++;
		free(str);
		str = file_readline(file);
	}

	fclose(file);
	return SUCCESS;
}
