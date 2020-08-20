all: third

third:
	gcc -Wall -Werror -fsanitize=address -std=c11 third.c -o third

clean:
	rm -rf third
