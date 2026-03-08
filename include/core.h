#ifndef CORE_H
#define CORE_H
#define BOARD_HEIGHT 3
#define BOARD_WIDTH 3
#define EMPTY ' '
#define CLEAR_SCREEN() printf("\033[2J\033[H")
#include <stdbool.h>


typedef struct MousePosition{
	short int row;
	short int column;
}MousePosition;

typedef enum KeyboardControls{
	UP=87, // W
	DOWN=83,  // S
	LEFT=65,
	RIGHT=68,
}KeyboardControls;

void setup_ctrl_c_signal();

void run_game_loop();

void print_tic_tac_toe_board( char[BOARD_WIDTH][BOARD_HEIGHT] );

void exit_game(int sig);

void change_board_cursor_based_on_mouse_position(MousePosition*);

bool set_mouse_position_up(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT]);

bool set_mouse_position_down(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT]);

bool set_mouse_position_left(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT] );

bool set_mouse_position_right(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT]);

bool is_target_position_occupied(char[BOARD_WIDTH][BOARD_HEIGHT],short int row,short column);


void print_board_row(char [BOARD_WIDTH][BOARD_HEIGHT],short int index);

bool print_cell(const char*,short int);

bool print_line();

void wait_for_user_input( char[BOARD_WIDTH][BOARD_HEIGHT],MousePosition*);

void print_column();

void restore_user_terminal();

void enable_raw_input();

#endif
