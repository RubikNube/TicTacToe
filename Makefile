PROJECT_ROOT := $(CURDIR)
CC := gcc
CFLAGS := -Wall

tic-tac-toe:
	$(CC) -o tic-tac-toe $(PROJECT_ROOT)/src/main.c $(PROJECT_ROOT)/src/engine/random_engine.c $(PROJECT_ROOT)/src/board/simple_board.c

test:
	$(CC) $(CFLAGS) -Iinclude $(PROJECT_ROOT)/tests/unit/test_random_engine.c -o $(PROJECT_ROOT)/test_runner -lcunit
	./test_runner
	rm -rf $(PROJECT_ROOT)/test_runner

clean:
	rm -rf $(PROJECT_ROOT)/tic-tac-toe
