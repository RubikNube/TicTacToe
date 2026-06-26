#include <stdio.h>
#include "./board.h"

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
