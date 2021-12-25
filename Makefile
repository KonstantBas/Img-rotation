CFLAGS=--std=c18 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
CC=gcc

all: print_header

bmp.o: bmp.c
	$(CC) -c $(CFLAGS) $< -o $@

rotation.o: rotation.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

print_header: main.o rotation.o util.o bmp.o
	$(CC) -o print_header $^

clean:
	rm -f main.o rotation.o util.o bmp.o print_header

