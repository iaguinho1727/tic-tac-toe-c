#include "core.h"
int main()
{
	setup_ctrl_c_signal();
	enable_raw_input();

	Game new_game;
	initialize_game(&new_game);
	run_game_loop(&new_game);
	restore_user_terminal();
	return 0;
}
