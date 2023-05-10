CC		= gcc
CFLAGS	= -pthread
DEPS 	= 

# OBJ_DIR = .
BIN_DIR = ../../bin

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
# OBJ = $(patsubst %, $(OBJ_DIR)/%, $(_OBJ))

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

client: $(OBJ)
	$(CC) -o $(BIN_DIR)/$@ $^

all: client

run_client: client
	./run_client.sh $(BIN_DIR)

.PHONY: clean
clean: