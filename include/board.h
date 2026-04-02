#ifndef BOARD_H
#define BOARD_H

#include "types.h"

extern void initialize_board(Game* game);
extern bool is_board_full(Game* game);
extern void mark_board_cell(Game* game);
extern bool is_target_position_occupied(Game* game);
extern void change_turn(Game* game);
extern bool has_won_horizontally(Game* game, char* current_player);
extern bool has_won_vertically(Game* game, char* current_player);
extern bool has_won_diagonally(Game* game, char* current_player);
extern bool is_there_winner(Game* game, char current_player);
extern void check_current_game_state(Game* game);

#endif
