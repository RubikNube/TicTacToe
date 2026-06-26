#include <stdio.h>
#include <ctype.h>
#include "./board.h"

#define BOX_DOWN_RIGHT "┌"
#define BOX_DOWN_LEFT "┐"
#define BOX_HORIZONTAL "─"
#define BOX_VERTICAL "│"
#define BOX_UP_RIGHT "└"
#define BOX_UP_LEFT "┘"
#define BOX_VERTICAL_RIGHT "├"
#define BOX_VERTICAL_LEFT "┤"
#define BOX_DOWN_HORIZONTAL "┬"
#define BOX_UP_HORIZONTAL "┴"
#define BOX_VERTICAL_HORIZONTAL "┼"

void render_board(int board_size, char board[][board_size])
{
	printf("\n\nBoard:\n\n");
	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			if (i == 0) {
				if (j == 0)
					printf("%s%s%s%s%s", BOX_DOWN_RIGHT,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_HORIZONTAL,
					       BOX_DOWN_HORIZONTAL);
				else if (j == board_size - 1)
					printf("%s%s%s%s\n", BOX_HORIZONTAL,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_DOWN_LEFT);
				else
					printf("%s%s%s%s", BOX_HORIZONTAL,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_DOWN_HORIZONTAL);
			} else {
				if (j == 0)
					printf("%s%s%s%s%s", BOX_VERTICAL_RIGHT,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_HORIZONTAL,
					       BOX_VERTICAL_HORIZONTAL);
				else if (j == board_size - 1)
					printf("%s%s%s%s\n", BOX_HORIZONTAL,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_VERTICAL_LEFT);
				else
					printf("%s%s%s%s", BOX_HORIZONTAL,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_VERTICAL_HORIZONTAL);
			}
		}

		for (int j = 0; j < board_size; j++) {
			if (j == 0)
				printf("%s %c %s", BOX_VERTICAL,
				       toupper(board[i][j]), BOX_VERTICAL);
			else if (j == board_size - 1)
				printf(" %c %s\n", toupper(board[i][j]),
				       BOX_VERTICAL);
			else
				printf(" %c %s", toupper(board[i][j]),
				       BOX_VERTICAL);
		}

		if (i == board_size - 1) {
			for (int j = 0; j < board_size; j++) {
				if (j == 0)
					printf("%s%s%s%s%s", BOX_UP_RIGHT,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_HORIZONTAL,
					       BOX_UP_HORIZONTAL);
				else if (j == board_size - 1)
					printf("%s%s%s%s\n", BOX_HORIZONTAL,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_UP_LEFT);
				else
					printf("%s%s%s%s", BOX_HORIZONTAL,
					       BOX_HORIZONTAL, BOX_HORIZONTAL,
					       BOX_UP_HORIZONTAL);
			}
		}
	}
}
