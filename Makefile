tic-tac-toe:
	gcc -o tic-tac-toe ./src/main.c ./src/engine/random.engine.c

test:
	gcc -Wall -Iinclude ./tests/unit/test_random_engine.c -o ./test_runner -lcunit
	./test_runner
	rm -rf ./test_runner

clean:
	rm -rf ./tic-tac-toe
