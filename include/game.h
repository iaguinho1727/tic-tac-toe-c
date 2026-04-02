#ifndef GAME_H
#define GAME_H

#include "types.h"

extern void initialize_game(Game* game);

#ifndef __EMSCRIPTEN__
extern void run_game_loop(Game* game);
#else
#include <emscripten.h>
extern void run_emscripten_game_loop(void* arg);
#endif

#endif
