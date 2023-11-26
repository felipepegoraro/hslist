CC=gcc
CFLAGS=-Wall -Werror -Wextra -lm
XFLAGS=-lssl -lcrypto -lncurses -ltinfo -lform
SRC=main.c ./src/hash_table.c ./src/UI.c ./src/types.c ./src/file_io.c ./src/pages/*.c

ifdef MAX_HS_SIZE
	CFLAGS += -DMAX_HS_SIZE=$(MAX_HS_SIZE)
endif

ifdef CONTACT_LIST_FILENAME
	CFLAGS += -DCONTACT_LIST_FILENAME=\"$(CONTACT_LIST_FILENAME)\"
endif

all: main

main: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(XFLAGS) -g -o main

clean:
	rm -f main
