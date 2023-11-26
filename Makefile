CC=gcc
CFLAGS=-Wall -Werror -Wextra -lm
XFLAGS=-lssl -lcrypto -lncurses -ltinfo -lform
SRC=main.c ./src/hash_table.c ./src/UI.c ./src/types.c ./src/file_io.c ./src/pages/*.c

ifdef MAX_HS_SIZE
    CFLAGS += -DMAX_HS_SIZE=$(MAX_HS_SIZE)
endif

all: main

main: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(XFLAGS) -g -o main

clean:
	rm -f main
