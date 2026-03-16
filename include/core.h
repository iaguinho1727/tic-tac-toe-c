#ifndef CORE_H
#define CORE_H
#define BOARD_HEIGHT 3
#define BOARD_WIDTH 3
#define EMPTY ' '
#define COLOR_CYAN  "\x1b[36m"
#define COLOR_GOLD  "\x1b[33m"
#define COLOR_RESET "\x1b[0m"
#define CLEAR_CODE "\033[2J\033[H"
#define START_REVERSE_VIDEO "\033[7m"
#define END_REVERSE_VIDEO "\033[0m"
#include <stdbool.h>


typedef struct MousePosition{
	short int row;
	short int column;
}MousePosition;

typedef enum KeyboardControls{
	UP='W', // W
	DOWN='S',  // S
	LEFT='A',
	RIGHT='D',
	SPACE=' ',
	QUIT='Q',
	ESC=27
}KeyboardControls;

void setup_ctrl_c_signal();

void run_game_loop();

void clear_screen();

void print_highlight(const char item);

void render_game_screen( char[BOARD_WIDTH][BOARD_HEIGHT],MousePosition* cursor ,unsigned short int*);

const char get_mark_based_on_turn(unsigned short int* turn);

void exit_game(int sig);

void change_board_cursor_based_on_mouse_position(MousePosition*);

bool set_mouse_position_up(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT]);

bool set_mouse_position_down(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT]);

bool set_mouse_position_left(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT] );

bool set_mouse_position_right(MousePosition*,char[BOARD_WIDTH][BOARD_HEIGHT]);

bool is_target_position_occupied(char[BOARD_WIDTH][BOARD_HEIGHT],short int row,short column);

bool set_player_mark(MousePosition* position,char board[BOARD_WIDTH][BOARD_HEIGHT],unsigned short int* turn);


void print_board_row(char [BOARD_WIDTH][BOARD_HEIGHT],short int index,MousePosition* cursor);

bool print_line();

void wait_for_user_input( char[BOARD_WIDTH][BOARD_HEIGHT],MousePosition*,unsigned short int* turn);

void print_column();

void restore_user_terminal();

void enable_raw_input();

#endif
