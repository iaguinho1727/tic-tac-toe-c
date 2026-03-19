#ifndef CORE_H
#define CORE_H
#define BOARD_HEIGHT 3
#define BOARD_WIDTH 3
#define EMPTY ' '
#define COLOR_CYAN  "\x1b[36m"
#define COLOR_GOLD  "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
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
	W='W', // W
	S='S',  // S
	A='A',
	D='D',
	SPACE=' ',
	QUIT='Q',
	ESC=27,
	UP='A',
	DOWN='B',
	RIGHT='C',
	LEFT='D'
}KeyboardControls;

bool is_especial_key(char* buffer);

bool is_esc_key(char* buffer);

void handle_special_key_event(MousePosition* cursor,char key);

void setup_ctrl_c_signal();

void run_game_loop();

void clear_screen();

void print_highlight(const char item);

void render_game_screen( char[BOARD_WIDTH][BOARD_HEIGHT],MousePosition* cursor ,unsigned short int*);

char get_mark_based_on_turn(unsigned short int* turn);

void exit_game(int sig);

void change_board_cursor_based_on_mouse_position(MousePosition*);

bool on_mouse_position_up(MousePosition*);

bool on_mouse_position_down(MousePosition*);

bool on_mouse_position_left(MousePosition* );

bool on_mouse_position_right(MousePosition*);

bool is_target_position_occupied(char[BOARD_WIDTH][BOARD_HEIGHT],short int row,short column);

bool on_set_player_mark(MousePosition* position,char board[BOARD_WIDTH][BOARD_HEIGHT],unsigned short int* turn);


void print_board_row(char [BOARD_WIDTH][BOARD_HEIGHT],short int index,MousePosition* cursor);

bool print_line();

bool handle_player_input( char[BOARD_WIDTH][BOARD_HEIGHT],MousePosition*,unsigned short int* turn);

void print_column();

void restore_user_terminal();

void enable_raw_input();

#endif
