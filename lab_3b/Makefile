all:
	clang -c main.c -o main.o -Wall -Wextra -Werror -fsanitize=address,undefined -g
	clang -c lib/table.c -o lib.o -Wall -Wextra -Werror -fsanitize=address,undefined -g 
	clang -c lib/readfile.c -o readfile.o -Wall -Wextra -Werror -fsanitize=address,undefined -g
	clang -c lib/hash.c -o hash.o -Wall -Wextra -Werror -fsanitize=address,undefined -g
	clang main.o lib.o readfile.o hash.o -o bin -Wall -Wextra -Werror -fsanitize=address,undefined -g 
