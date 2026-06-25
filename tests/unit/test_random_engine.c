#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../../src/engine/random_engine.c"
#include "../../src/coordinate.h"

void test_get_bot_move_is_in_range(void)
{
	int size = 3;
	char board[size][size];
	memset(board, ' ', sizeof board);
	struct Coordinate result = get_bot_move(size, board);

	// test that result is in range
	CU_ASSERT(result.x >= 0);
	CU_ASSERT(result.y <= size);
}

void test_get_bot_move_returns_free_field(void)
{
	int size = 3;
	char board[size][size];
	memset(board, 'x', sizeof board);
	board[1][2] = ' ';
	struct Coordinate result = get_bot_move(size, board);

	// test that only free field is returned
	CU_ASSERT(result.x == 2);
	CU_ASSERT(result.y == 1);
}

int main()
{
	CU_initialize_registry();
	CU_pSuite suite = CU_add_suite("Random Engine Suite", 0, 0);
	CU_add_test(suite, "Test get_bot_move is in range",
		    test_get_bot_move_is_in_range);
	CU_add_test(suite, "Test get_bot_move returns free field",
		    test_get_bot_move_returns_free_field);
	CU_basic_run_tests();
	CU_cleanup_registry();

	return 0;
}
