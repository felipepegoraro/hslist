CC=gcc
CFLAGS=-Wall -Werror -Wextra -lm
XFLAGS=-lssl -lcrypto -lncurses -ltinfo -lform
SRC=main.c ./src/hash_table.c ./src/UI.c ./src/types.c ./src/pages/*.c

all:
	$(CC) $(CFLAGS) $(SRC) $(XFLAGS) -o main

clean:
	rm main
