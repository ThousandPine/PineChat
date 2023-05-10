CC		= gcc
CFLAGS	= -pthread
DEPS 	= 

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

client: $(OBJ)
	$(CC) -o $@ $^

server: $(OBJ)
	$(CC) -o $@ $^

all: client server

.PHONY: clean
clean: