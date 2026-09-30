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
	table->key_space = (KeySpace *)malloc(max_size_key_space * sizeof(KeySpace));
	for(size_t i = 0; i < table->max_size_key_space; i++){
		table->key_space[i].busy = -1;
	}
	if(table->key_space == NULL){	
		free(table);
		return NULL;
	}
	return table;
}




//исправил
int insert(Table *table, KeyType key, InfoType *info){
	if(table == NULL) return ALLOC_ERROR;

	if(table->len_key_space == table->max_size_key_space) return OVERFLOW_ERROR;
	ULLI release = 1;
	(table->len_key_space)++;
	long long int index_first = hash(table->max_size_key_space, key, 0), index = -1;

		if( (index = search(table, key)) != -1){
			release = (table->key_space[find_last_rel(table, key)].release) + 1;
			table->key_space[index].busy = 1;
			table->key_space[index].key = key;
			table->key_space[index].release = release;
			table->key_space[index].info = strdup(info);	
			return SUCCESS;
		}

/*
		for(size_t i = 0; index != index_first || i == 1; i++){
			index = hash(table->max_size_key_space, key, i);
			if(table->key_space[index].key == key) {
			//printf("%d\n", find_last_rel(table, key));
			release = (table->key_space[find_last_rel(table, key)].release) + 1;
			}
			if(table->key_space[index].busy != 1) {
				table->key_space[index].busy = 1;
				table->key_space[index].key = key;
				table->key_space[index].release = release;
				table->key_space[index].info = strdup(info);	
				return SUCCESS;
			}
			
	}
	

	//printf("сюда\n");
/*	table->key_space[index].busy = 1;
	table->key_space[index].key = key;
	table->key_space[index].release = release;
	table->key_space[index].info = strdup(info);
	return SUCCESS; */
	/*
	index = binary_search(table, key);
	ULLI release = 1;
	if(index == -1) return SEARCH_ERROR;
	(table->len_key_space)++;
	for(int i =  table->len_key_space - 1; i >= index; i-- ){
		table->key_space[i+1] = table->key_space[i];	
	}

	if(index-1 >= 0 && table->key_space[index - 1].key == key){
		release+=table->key_space[index - 1].release;
		//printf("инфо если ключи повторяются: %llu\t", *info);
	}
	table->key_space[index].busy = 1;
	table->key_space[index].key = key;
	table->key_space[index].release = release;
	table->key_space[index].info = strdup(info);
	//memcpy(table->key_space[index].info ,info, 1);	
	//printf("инфо добавление: %llu\n", *(table->key_space[index].info));
	
	return SUCCESS;*/
}

//готово надеюсь
int delete(Table *table, KeyType key){
	if(table == NULL) return ALLOC_ERROR;

	if(table->len_key_space == 0) return KEY_NOT_FOUND;
	
	int count = 0;
	long long int index_first = hash(table->max_size_key_space, key, 0), index = -1;
	size_t true_index, real_true_index;
	for(size_t i = 0; index != index_first || i == 1; i++){
		index = hash(table->max_size_key_space, key, i);
		if(table->key_space[index].key == key){
			count++;
			real_true_index = true_index;
			true_index = index;
		}
		
	}
	if(count == 0 ) return KEY_NOT_FOUND;
	
	free(table->key_space[real_true_index].info);
	table->key_space[real_true_index].key = 0;
	table->key_space[real_true_index].busy = 0;
	table->key_space[real_true_index].release = 0;
	(table->len_key_space)--;
	//free(table->key_space[table->len_key_space -1].info);
	return SUCCESS;
	
	
}

//ГОТОВО хахаха 
int delete_all_release(Table *table, KeyType key){
	if(table == NULL) return ALLOC_ERROR;
	
	if(table->len_key_space == 0) return KEY_NOT_FOUND;
	int count = 0;
	long long int index_first = hash(table->max_size_key_space, key, 0), index = -1;
	
	for(size_t i = 0; index != index_first || i == 1; i++){
		index = hash(table->max_size_key_space, key, i);
		if(table->key_space[index].key == key){
			free(table->key_space[index].info);
			table->key_space[index].key = 0;
			table->key_space[index].busy = 0;
			table->key_space[index].release = 0;
			(table->len_key_space)--;
			count++;
		}
		
	}
	if(count == 0 ) return KEY_NOT_FOUND;
	return SUCCESS;
	
		
}
 
//ГОТОВО
void free_table(Table *table){
	if(table == NULL) return;

	for(size_t i = 0; i < table->max_size_key_space; i++){
		if(table->key_space[i].busy == 1){
			free(table->key_space[i].info);
			printf("%zu\n", i);}
	}
	free(table->key_space);
	free(table);
	return;
}

//ready
int search(Table *table, KeyType key){
	if(table->len_key_space == 0) return -1;

	int index = hash(table, key, 0);
	for(size_t i = 0; table->key_space[index].busy != -1; i++){
		index = hash(table, key, i);
		if(table->key_space[index].key == key && table->key_space[index].busy != 1)
			return index;
	
		
	}
	return -1;
	
}

//ГОТОВО
void print_table(Table *table){
	if(table == NULL) return;

	if(table->len_key_space == 0){
		printf("table is empty\n");
		return;
	}
	
	printf("\t TABLE: \n");
	printf("busy		key     	realese	 	info\n");
	for(size_t i = 0; i < table->max_size_key_space; i++){
		
		printf("%d		", table->key_space[i].busy);
		if(table->key_space[i].busy == 1){
		printf("%llu		", table->key_space[i].key);
		printf("%llu 		", table->key_space[i].release);
		printf("%s\n", table->key_space[i].info);
	}
		else
		printf("-		-		-\n");
	}
	printf("\n");
	return;
	
}

Table *find_all_rel(Table *table, KeyType key){
	if(table == NULL || table->len_key_space == 0) return NULL;

	size_t size = table->max_size_key_space;

	Table *elements = create_table(size);

	if(elements == NULL) return NULL;
	long long int index_first = hash(table->max_size_key_space, key, 0), index = -1;
	int j = 0;
	for(size_t i = 0; index != index_first || i == 1; i++){
		index = hash(table->max_size_key_space, key, i);
		if(table->key_space[index].key == key && (i ==0 || index_first != index)){
			//if(index == index_first && i != 1) break;
			//else{
			//printf("%llu\n", table->key_space[i].key);
			insert(elements, key, table->key_space[index].info);
			j++;
		}
	}
	if(j == 0){
		free_table(elements);
		return NULL;
	}
	
	
	return elements;

	
}

//готово
int find_last_rel(Table *table, KeyType key){
	if(table == NULL) return ALLOC_ERROR;
	int index = -1;
	ULLI release = 0;

	if(table->max_size_key_space == 0) return -1;

	for(size_t i = 0; i < table->max_size_key_space; i++){
		//printf("%llu %llu  rel %llu\n", table->key_space[i].key, key, table->key_space[i].release);
		if(table->key_space[i].key == key){
			//printf("success %llu %llu rel %llu\n", table->key_space[i].key, key, table->key_space[i].release);
			if(release < table->key_space[i].release){
				release = table->key_space[i].release;
				index = i;
			}
		}
	}
	return index;
}

//ГООТОВО
int read_table_from_file(Table *table, char *filename){
	if(table == NULL) return ALLOC_ERROR;

	char *str = NULL;
	FILE *file = fopen(filename, "r");

	if(file == NULL) return FILE_ERROR;
	char *key = NULL;
	char *info = NULL;

	str = file_readline(file);
	
	while(str!= NULL){
		printf("%s\n", str);
		key = strtok(str, DELIM);
		info = strtok(NULL, DELIM);

		insert(table, (ULLI)(atoi(key)) ,(info));
		//table->key_space[table->len_key_space].key = (ULLI)(atoi(key));
	//	table->key_space[table->len_key_space].info = (ULLI)(atoi(info));
		//(table->len_key_space)++;
		free(str);
		str = file_readline(file);
	}

	fclose(file);
	return SUCCESS;
}
