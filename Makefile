all: predict

predict:
	gcc -Wall -Werror -fsanitize=address -std=c11 predict.c -o predict

clean:
	rm -rf predict
