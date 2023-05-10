CC		= gcc
CFLAGS	= -pthread
DEPS 	= 

BIN_DIR = ../../bin

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))

%.o: %.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

client: $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$@ $^ $(CFLAGS)

run_client: client
	./run_client.sh $(BIN_DIR)

.PHONY: clean
clean: