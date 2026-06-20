#include <stdio.h>
#include <stdlib.h>

struct Coordinate {
	int x;
	int y;
};

struct Coordinate getCoordinateFromUser(char (*boardState)[3])
{
	struct Coordinate position = {};
	while (1) {
		scanf("%d %d", &position.x, &position.y);
		if (position.x < 1 || position.x > 3 || position.y < 1 ||
		    position.y > 3) {
			printf("Invalid coordinated. Enter coordinates between 1 and 3.\n");
			continue;
		}

		printf("You entered %d %d\n", position.x, position.y);

		if (boardState[position.y - 1][position.x - 1] != ' ') {
			printf("Field already taken. Choose a different one.\n");
			continue;
		}

		return position;
	}
}

void renderBoard(char (*boardState)[3])
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			printf("[%c]", boardState[i][j]);
			if (j == 2) {
				printf("\n");
			}
		}
	}
}

char selectSide()
{
	printf("Choose your side: x or o?\n");

	char side;
	scanf("%c", &side);

	while (side != 'x' && side != 'o') {
		printf("You have to choose x or o. You typed %c\n", side);
		printf("Choose your side:\n");
		scanf("%c", &side);
	}

	printf("Good. You play as %c\n", side);
	return side;
}

/*
 * Returns -1 if not decided, 0 if tie, 1 if x wins, 2 if o wins
 */
short checkGameResult(char boardState[3][3], int numberOfFreeFields)
{
	// check rows
	for (int i = 0; i < 3; i++) {
		int numberOfConnectedFields = 0;
		char side = ' ';

		for (int j = 0; j < 3; j++) {
			char currentSide = boardState[i][j];

			if (currentSide != ' ') {
				if (side == ' ') {
					side = currentSide;
					numberOfConnectedFields++;
					continue;
				} else if (side == currentSide) {
					numberOfConnectedFields++;
					continue;
				} else {
					break;
				}
			}
		}
		if (numberOfConnectedFields == 3) {
			return side == 'x' ? 1 : 2;
		}
	}
	// check columns
	for (int i = 0; i < 3; i++) {
		int numberOfConnectedFields = 0;
		char side = ' ';

		for (int j = 0; j < 3; j++) {
			char currentSide = boardState[j][i];

			if (currentSide != ' ') {
				if (side == ' ') {
					side = currentSide;
					numberOfConnectedFields++;
					continue;
				} else if (side == currentSide) {
					numberOfConnectedFields++;
					continue;
				} else {
					break;
				}
			}
		}
		if (numberOfConnectedFields == 3) {
			return side == 'x' ? 1 : 2;
		}
	}
	// check diagonals

	// 0,0 to 2,2
	int numberOfConnectedFieldsDiagonal1133 = 0;
	char sideDiagonal1133 = ' ';
	for (int i = 0; i < 3; i++) {
		char currentSide = boardState[i][i];

		if (currentSide != ' ') {
			if (sideDiagonal1133 == ' ') {
				sideDiagonal1133 = currentSide;
				numberOfConnectedFieldsDiagonal1133++;
				continue;
			} else if (sideDiagonal1133 == currentSide) {
				numberOfConnectedFieldsDiagonal1133++;
				continue;
			} else {
				break;
			}
		}
	}
	if (numberOfConnectedFieldsDiagonal1133 == 3) {
		return sideDiagonal1133 == 'x' ? 1 : 2;
	}

	int numberOfConnectedFieldsDiagonal1331 = 0;
	char side1331 = ' ';
	// 1,3 to 3,1
	for (int i = 2; i >= 0; i--) {
		char currentSide = boardState[2 - i][i];
		if (currentSide != ' ') {
			if (side1331 == ' ') {
				side1331 = currentSide;
				numberOfConnectedFieldsDiagonal1331++;
				continue;
			} else if (side1331 == currentSide) {
				numberOfConnectedFieldsDiagonal1331++;
				continue;
			} else {
				break;
			}
		}
	}

	if (numberOfConnectedFieldsDiagonal1331 == 3) {
		return side1331 == 'x' ? 1 : 2;
	}

	return numberOfFreeFields <= 0 ? 0 : -1;
}

char *getGameResultMessage(int gameResult)
{
	switch (gameResult) {
	case 1:
		return "Player x won";
	case 2:
		return "Player o won";
	case 0:
		return "Tie";
	default:
		return "Undecided";
	}
}

int main()
{
	printf("Tic Tac Toe\n\n");

	char userSide = selectSide();
	char botSide = userSide == 'x' ? 'o' : 'x';

	char boardState[3][3];

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			boardState[i][j] = ' ';
		}
	}

	renderBoard(boardState);

	int freeFields = 9;
	short gameResult = -1;

	while (gameResult == -1) {
		printf("Make your move: \n");

		struct Coordinate nextMove = getCoordinateFromUser(boardState);

		boardState[nextMove.y - 1][nextMove.x - 1] = userSide;
		freeFields--;
		gameResult = checkGameResult(boardState, freeFields);
		if (gameResult != -1) {
			break;
		}

		struct Coordinate botMove = {};

		while (1) {
			botMove.x = rand() % 3;
			botMove.y = rand() % 3;

			if (boardState[botMove.y][botMove.x] != ' ') {
				continue;
			}

			break;
		}

		// execute bot move
		boardState[botMove.y][botMove.x] = botSide;
		freeFields--;

		renderBoard(boardState);

		gameResult = checkGameResult(boardState, freeFields);
		if (gameResult != -1) {
			break;
		}
	}

	char *gameResultMessage = getGameResultMessage(gameResult);
	printf("%s\n\n", gameResultMessage);
	renderBoard(boardState);

	return 0;
}
