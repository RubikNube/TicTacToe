#include <stdio.h>
#include <stdlib.h>

struct Coordinate {
	int x;
	int y;
};

struct Coordinate get_user_move(char (*board)[3])
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

		if (board[position.y - 1][position.x - 1] != ' ') {
			printf("Field already taken. Choose a different one.\n");
			continue;
		}

		return position;
	}
}

void render_board(char (*board)[3])
{
	printf("\n\nBoard:\n");
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			printf("[%c]", board[i][j]);
			if (j == 2)
				printf("\n");
		}
}

char select_side()
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
short check_game_results(char (*board)[3], int free_fields)
{
	int connected_fields_1133 = 0;
	char side_1133 = ' ';
	int connected_fields_1331 = 0;
	char side_1331 = ' ';
	for (int i = 0; i < 3; i++) {
		int connected_row_fields = 0;
		char side_row = ' ';
		int connected_column_fields = 0;
		char side_column = ' ';

		char tmp_side_1133 = board[i][i];

		if (tmp_side_1133 != ' ') {
			if (side_1133 == ' ') {
				side_1133 = tmp_side_1133;
				connected_fields_1133++;
			} else if (side_1133 == tmp_side_1133) {
				connected_fields_1133++;
			}
		}

		char tmp_side_1331 = board[2 - i][i];
		if (tmp_side_1331 != ' ') {
			if (side_1331 == ' ') {
				side_1331 = tmp_side_1331;
				connected_fields_1331++;
			} else if (side_1331 == tmp_side_1331) {
				connected_fields_1331++;
			}
		}

		for (int j = 0; j < 3; j++) {
			char tmp_side_row = board[i][j];

			if (tmp_side_row != ' ') {
				if (side_row == ' ') {
					side_row = tmp_side_row;
					connected_row_fields++;
				} else if (side_row == tmp_side_row) {
					connected_row_fields++;
				}
			}

			char tmp_side_column = board[j][i];

			if (tmp_side_column != ' ') {
				if (side_column == ' ') {
					side_column = tmp_side_column;
					connected_column_fields++;
				} else if (side_column == tmp_side_column) {
					connected_column_fields++;
				}
			}
		}

		if (connected_row_fields == 3)
			return side_row == 'x' ? 1 : 2;

		if (connected_column_fields == 3)
			return side_column == 'x' ? 1 : 2;

		if (connected_fields_1133 == 3)
			return side_1133 == 'x' ? 1 : 2;

		if (connected_fields_1331 == 3)
			return side_1331 == 'x' ? 1 : 2;
	}

	return free_fields <= 0 ? 0 : -1;
}

char *get_result_message(int result)
{
	switch (result) {
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

struct Coordinate get_bot_move(char (*board)[3])
{
	struct Coordinate bot_move = {};

	while (1) {
		bot_move.x = rand() % 3;
		bot_move.y = rand() % 3;

		if (board[bot_move.y][bot_move.x] == ' ')
			return bot_move;
	}
}

short execute_user_move(char (*board)[3], char user_side, int *free_fields)
{
	struct Coordinate user_move = get_user_move(board);
	board[user_move.y - 1][user_move.x - 1] = user_side;
	(*free_fields)--;
	return check_game_results(board, *free_fields);
}

short execute_bot_move(char (*board)[3], char bot_side, int *free_fields)
{
	struct Coordinate bot_move = get_bot_move(board);
	board[bot_move.y][bot_move.x] = bot_side;
	(*free_fields)--;
	return check_game_results(board, *free_fields);
}

short execute_move(char move_side, char (*board)[3], char user_side,
		   int *free_fields)
{
	if (move_side == user_side) {
		return execute_user_move(board, move_side, free_fields);
	} else {
		return execute_bot_move(board, move_side, free_fields);
	}
}

int main()
{
	printf("Tic Tac Toe\n\n");

	char user_side = select_side();
	char bot_side = user_side == 'x' ? 'o' : 'x';

	char board[3][3];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			board[i][j] = ' ';

	render_board(board);

	int free_fields = 9;
	short result = -1;

	while (result == -1) {
		printf("Make your move: \n");

		result = execute_move('x', board, user_side, &free_fields);
		if (result != -1)
			break;

		render_board(board);

		result = execute_move('o', board, user_side, &free_fields);
		if (result != -1)
			break;

		render_board(board);
	}

	render_board(board);

	char *result_message = get_result_message(result);
	printf("%s\n\n", result_message);

	return 0;
}
