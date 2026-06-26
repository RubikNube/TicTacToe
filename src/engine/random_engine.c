#include <stdlib.h>
#include "../coordinate.h"
#include "./engine.h"

struct Coordinate get_bot_move(int board_size, char board[][board_size])
{
	struct Coordinate free_fields[board_size * board_size];
	int number_free_fields = 0;

	for (int i = 0; i < board_size; i++) {
		for (int j = 0; j < board_size; j++) {
			char content = board[i][j];
			if (content == ' ') {
				struct Coordinate free_field = { j, i };
				free_fields[number_free_fields] = free_field;
				number_free_fields++;
			}
		}
	}

	int selected_field_number = rand() % number_free_fields;
	return free_fields[selected_field_number];
}
