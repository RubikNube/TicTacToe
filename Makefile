tic-tac-toe:
	gcc -o tic-tac-toe ./src/main.c ./src/engine/random.engine.c

clean:
	rm -rf ./tic-tac-toe
