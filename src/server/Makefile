CC		= gcc
CFLAGS	= -pthread
DEPS 	= 

BIN_DIR = ../../bin

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

server: $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

run_server: server
	./run_server.sh $(BIN_DIR)

.PHONY: clean
clean: