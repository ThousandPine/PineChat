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

server: $(OBJ)
	$(CC) -o $(BIN_DIR)/$@ $^

all: server

run_server: server
	./run_server.sh $(BIN_DIR)

.PHONY: clean
clean: