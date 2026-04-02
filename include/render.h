#ifndef RENDER_H
#define RENDER_H

#include "types.h"

extern void clear_screen(void);
extern void print_column(void);
extern void print_line(void);
extern void print_highlight(const char item);
extern const char* get_mark_color(char* item);
extern void print_board_row(Game* game, short int* row);
extern void print_tic_tac_toe_board(Game* game);
extern void print_player_wins_message(char current_player);
extern void print_draw_message(void);
extern void print_current_game_state(CurrentGameState* state);
extern void print_colored_mark(char* current_player);
extern void print_current_player_turn(char* current_player);
extern void print_game_basic_instructions(void);
extern void render_game_screen(Game* game);

#endif