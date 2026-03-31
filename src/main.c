#include "core.h"
#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
	#include <emscripten/html5.h>
#endif
int main(void)
{
#ifndef __EMSCRIPTEN__
	setup_ctrl_c_signal();
	enable_raw_input();
#endif

	Game new_game;
	initialize_game(&new_game);
#ifndef __EMSCRIPTEN__
	run_game_loop(&new_game);
	restore_user_terminal();

#else
	emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, &new_game, 1, on_keydown);
	emscripten_set_main_loop_arg(run_emscripten_game_loop, &new_game, 0, 1);
#endif
	return 0;
}
