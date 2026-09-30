#include "lib/table.h"
#include "lib/key.h"
#include "lib/readfile.h"

#define MENU	"\n(1) Insert element.\n"						\
	"(2) Delete the latest release of the element by key.\n"					\
	"(3) Delete all release of the element by key.\n"								\
	"(4) Print all release of the element by key.\n"					\
	"(5) Import table from file.\n"						\
	"(6) Print all the elements of the table.\n"				\
	"(7) End of prigram\n"


#define TABLE_SIZE 11


void error_handler(int status){
	switch (status) {
		case SUCCESS:
			printf("Функция выполнена успешно!\n");
			break;
		case ALLOC_ERROR:
			printf("Ошибка выделения памяти при работе с функцией.\n");
			break;
		case OVERFLOW_ERROR:
			printf("Произошло переполнение при работе с функцией.\n");
			break;
		case SEARCH_ERROR:
			printf("Произошла ошибка при работе с функцией.\n");
			break;
		case KEY_NOT_FOUND:
			printf("Заданный ключ не найден.\n");
			break;
		case FILE_ERROR:
			printf("Ошибка при чтении с файла.\n");
			break;
			
		case END:
			printf("Работа программы заввершена.\n");
			break;
		default:
			break;
		
	}	
}


int main() {
	Table *table = create_table(TABLE_SIZE);
	int procedure = 0;
	KeyType key = 0;
	char *info = NULL;
	int status = 0;
	char *filename = NULL;
	printf(MENU);
	while (scanf("\n %d", &procedure) != EOF) {
		switch (procedure) {
			case 1:
				printf("Input key: ");
				if(scanf("%llu", &key) == EOF) free_table(table);
				//printf("Input info: ");
				//scanf("%llu", &info);
				getchar();
				
				info = readline("Input info: ");
				status = insert(table, key, info);
				free(info);
				error_handler(status);
				break;

			case 2:
				printf("Input key: ");
				if(scanf("%llu", &key) == EOF) {
					free_table(table);
					return 0;}
				status = delete(table, key);
				error_handler(status);
				break;
			case 3:
				printf("Input key: ");
				if(scanf("%llu", &key) == EOF) {
					free_table(table);
					return 0;}
				status = delete_all_release(table, key);
				error_handler(status);
				break;
			case 4:
				printf("Input key: ");
				if(scanf("%llu", &key) == EOF) {
					free_table(table);
					return 0;}
				Table *all_rel;
				all_rel = find_all_rel(table, key);
				print_table(all_rel);
				free_table(all_rel);
				break;

			case 5:
				if(table != NULL) free_table(table);
				table = create_table(TABLE_SIZE);
				getchar();
				filename = readline("Input filename: \n");
				if(filename == NULL) {
					free_table(table);
					return 0;}
				status = read_table_from_file(table, filename);
				error_handler(status);
				free(filename);
				break;
		
			case 6:
				print_table(table);
				break;

			case 7:
				printf("Работа программы заввершена.\n");
				free_table(table);
				

				return 0;
			
			default:
				scanf("%*[^\n]");
				printf("Некорректный ввод\n");
				break;
				}
			printf(MENU);
			}

	free_table(table);
	return 0;
}

