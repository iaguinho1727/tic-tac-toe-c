#include "core.h"
int main()
{
	setup_ctrl_c_signal();
	enable_raw_input();
	run_game_loop();
	restore_user_terminal();
	return 0;
}
