#include <stdlib.h>
#include "../coordinate.h"
#include "./engine.h"

struct Coordinate get_bot_move(int board_size, char board[][board_size])
{
	struct Coordinate bot_move = {};

	while (1) {
		bot_move.x = rand() % board_size;
		bot_move.y = rand() % board_size;

		if (board[bot_move.y][bot_move.x] == ' ')
			return bot_move;
	}
}
