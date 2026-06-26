PROJECT_ROOT := $(CURDIR)
CC := gcc
CFLAGS := -Wall

SRC := $(PROJECT_ROOT)/src
SRCS_PRETTY := $(SRC)/main.c $(SRC)/engine/random_engine.c $(SRC)/board/pretty_board.c
SRCS_SIMPLE := $(SRC)/main.c $(SRC)/engine/random_engine.c $(SRC)/board/simple_board.c

all: tic-tac-toe simple test

tic-tac-toe: $(SRCS_PRETTY)
	$(CC) -o $(PROJECT_ROOT)/tic-tac-toe $(SRCS_PRETTY)

simple: $(SRCS_SIMPLE)
	$(CC) -o $(PROJECT_ROOT)/tic-tac-toe-simple $(SRCS_SIMPLE)

test:
	$(CC) $(CFLAGS) -Iinclude $(PROJECT_ROOT)/tests/unit/test_random_engine.c -o $(PROJECT_ROOT)/test_runner -lcunit
	./test_runner
	rm -rf $(PROJECT_ROOT)/test_runner

clean:
	rm -rf $(PROJECT_ROOT)/tic-tac-toe
	rm -rf $(PROJECT_ROOT)/tic-tac-toe-simple
