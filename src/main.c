#include "core.h"
int main(void)
{
#ifndef __EMSCRIPTEN__
	setup_ctrl_c_signal();
	enable_raw_input();
#endif

	Game new_game;
	initialize_game(&new_game);
	run_game_loop(&new_game);

#ifndef __EMSCRIPTEN__
	restore_user_terminal();
#endif
	return 0;
}
