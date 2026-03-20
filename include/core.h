#ifndef CORE_H
#define CORE_H
#define BOARD_HEIGHT 3
#define BOARD_WIDTH 3
#define WIN_OCORRENCES BOARD_WIDTH
#define EMPTY ' '
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define COLOR_CYAN  "\x1b[36m"
#define UP_ARROW 'A'
#define DOWN_ARROW 'B'
#define RIGHT_ARROW 'C'
#define LEFT_ARROW 'D'
#define W_KEY 'W'
#define S_KEY 'S'
#define A_KEY 'A'
#define D_KEY 'D'
#define Q_KEY 'Q'
#define R_KEY 'R'
#define SPACE_KEY 32
#define ESC_KEY '\033'
#define COLOR_GOLD  "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"
#define CLEAR_CODE "\033[2J\033[H"
#define START_REVERSE_VIDEO "\033[7m"
#define END_REVERSE_VIDEO "\033[0m"
#define PRINT_COLORED(COLOR,TEXT) printf(COLOR TEXT COLOR_RESET)
#define FIRST_PLAYER_TURN  PLAYER_X
#include <stdbool.h>


typedef struct MousePosition{
	short int row;
	short int column;
}MousePosition;

typedef enum KeyboardEvent{
	MARK,
	QUIT,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	RESET,
	UNKWON,
}KeyboardEvent;

typedef enum CurrentGameState{
	PLAYER_X_WIN,
	PLAYER_O_WIN,
	DAWN,
	NOT_ENDED
}CurrentGameState;

typedef struct GameEvent{
	CurrentGameState state;
	KeyboardEvent key;
	char key_buffer[3];
}GameEvent;

typedef struct Game{
	GameEvent event;
	MousePosition cursor;
	char current_player;
	KeyboardEvent pressed_key;
	char board[BOARD_WIDTH][BOARD_HEIGHT];
}Game;



bool is_especial_key(char* buffer);

bool is_esc_key(char* buffer);

void handle_special_key_event(GameEvent*);

void setup_ctrl_c_signal();

void run_game_loop(Game*);

void clear_screen();

void print_highlight(const char item);

void render_game_screen( Game*);

void exit_game(int sig);

void initialize_game(Game*);

bool on_cursor_up(MousePosition*);

bool on_cursor_down(MousePosition*);

bool on_cursor_left(MousePosition* );

bool on_cursor_right(MousePosition*);

bool is_target_position_occupied(Game*);

bool on_set_player_mark(Game*);

bool handle_keyboard_events(Game* game);

void print_board_row(Game* game,short int row);

bool print_line();

bool check_keyboard_event( Game*);

void print_column();

void restore_user_terminal();

void enable_raw_input();

void on_reset_game(Game*);

bool is_there_winner(Game*,char);

void print_current_player_turn(char current_player);

void print_colored_mark(char current_player);

void print_game_basic_instructions();

void print_current_game_state(CurrentGameState* state);

void print_dawn_message();

void print_player_wins_message(char current_player);

bool has_won_diagonally(Game* game,char current_player);

bool has_won_vertically(Game* game, char current_player);

bool has_won_horizontally(Game* game,char current_player);

#endif
