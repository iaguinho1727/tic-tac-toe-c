#include "game.h"
#include "board.h"
#include "render.h"
#include "input.h"
#include "platform.h"

void initialize_game(Game* game)
{
	*game=(Game){
		.cursor={
			.column=0,
			.row=0
		},
		.event={
			.key_buffer={0},
			.state=NOT_ENDED,
			.key=UNKNOWN
		},
		.current_player=FIRST_PLAYER_TURN,
	};
	initialize_board(game);
}

#ifndef __EMSCRIPTEN__
static void handle_game_events(Game* game)
{
	check_keyboard_event(game);
	handle_keyboard_events(game);
	check_current_game_state(game);
}

void run_game_loop(Game* game)
{
	while(is_running)
	{
		clear_screen();
		render_game_screen(game);
		handle_game_events(game);
	}
}
#else
void run_emscripten_game_loop(void *arg)
{
	Game *game=(Game *)arg;
	clear_screen();
	render_game_screen(game);
	handle_keyboard_events(game);
	check_current_game_state(game);
	game->event.key=UNKNOWN;
}
#endif
