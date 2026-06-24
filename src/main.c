#include <stdio.h>
#include <string.h>
#include "./coordinate.h"
#include "./engine/engine.h"

#define RESULT_UNDECIDED -1
#define RESULT_TIE 0
#define RESULT_X_WINS 1
#define RESULT_O_WINS 2

#define TRUE 1
#define FALSE 0

struct Coordinate get_user_move(int board_size, char board[][board_size])
{
	struct Coordinate position = {};
	while (TRUE) {
		scanf("%d %d", &position.x, &position.y);
		if (position.x < 1 || position.x > board_size ||
		    position.y < 1 || position.y > board_size) {
			printf("Invalid coordinated. Enter coordinates between 1 and %d.\n",
			       board_size);
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

void render_board(int board_size, char board[][board_size])
{
	printf("\n\nBoard:\n");
	for (int i = 0; i < board_size; i++)
		for (int j = 0; j < board_size; j++) {
			printf("[%c]", board[i][j]);
			if (j == board_size - 1)
				printf("\n");
		}
}

char select_side()
{
	printf("Choose your side: x or o?\n");

	char side;
	scanf(" %c", &side);

	while (side != 'x' && side != 'o') {
		printf("You have to choose x or o. You typed '%c'\n", side);
		printf("Choose your side:\n");
		scanf(" %c", &side);
	}

	printf("Good. You play as %c\n", side);
	return side;
}

short get_winning_side(char side)
{
	return side == 'x' ? RESULT_X_WINS : RESULT_O_WINS;
}

/*
 * Returns -1 if not decided, 0 if tie, 1 if x wins, 2 if o wins
 */
short check_game_results(int board_size, char board[][board_size],
			 int free_fields)
{
	int connected_fields_1133 = 0;
	char side_1133 = ' ';
	int connected_fields_1331 = 0;
	char side_1331 = ' ';
	for (int i = 0; i < board_size; i++) {
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

		for (int j = 0; j < board_size; j++) {
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

		if (connected_row_fields == board_size)
			return get_winning_side(side_row);

		if (connected_column_fields == board_size)
			return get_winning_side(side_column);

		if (connected_fields_1133 == board_size)
			return get_winning_side(side_1133);

		if (connected_fields_1331 == board_size)
			return get_winning_side(side_1331);
	}

	return free_fields <= 0 ? RESULT_TIE : RESULT_UNDECIDED;
}

char *get_result_message(int result)
{
	switch (result) {
	case RESULT_X_WINS:
		return "Player x won";
	case RESULT_O_WINS:
		return "Player o won";
	case RESULT_TIE:
		return "Tie";
	default:
		return "Undecided";
	}
}

short execute_user_move(int board_size, char board[][board_size],
			char user_side, int *free_fields)
{
	struct Coordinate user_move = get_user_move(board_size, board);
	board[user_move.y - 1][user_move.x - 1] = user_side;
	(*free_fields)--;
	return check_game_results(board_size, board, *free_fields);
}

short execute_bot_move(int board_size, char board[][board_size], char bot_side,
		       int *free_fields)
{
	struct Coordinate bot_move = get_bot_move(board_size, board);
	board[bot_move.y][bot_move.x] = bot_side;
	(*free_fields)--;
	return check_game_results(board_size, board, *free_fields);
}

short execute_move(char move_side, int board_size, char board[][board_size],
		   char user_side, int *free_fields)
{
	if (move_side == user_side) {
		return execute_user_move(board_size, board, move_side,
					 free_fields);
	} else {
		return execute_bot_move(board_size, board, move_side,
					free_fields);
	}
}

int main()
{
	printf("Tic Tac Toe\n\n");

	int board_size;
	printf("Enter board size: \n");
	scanf("%d", &board_size);

	char user_side = select_side();
	char board[board_size][board_size];
	memset(board, ' ', sizeof board);

	render_board(board_size, board);

	int free_fields = board_size * board_size;
	short result = RESULT_UNDECIDED;

	while (result == RESULT_UNDECIDED) {
		printf("Make your move: \n");

		result = execute_move('x', board_size, board, user_side,
				      &free_fields);
		if (result != RESULT_UNDECIDED)
			break;

		render_board(board_size, board);

		result = execute_move('o', board_size, board, user_side,
				      &free_fields);
		if (result != RESULT_UNDECIDED)
			break;

		render_board(board_size, board);
	}

	render_board(board_size, board);

	char *result_message = get_result_message(result);
	printf("%s\n\n", result_message);

	return 0;
}
