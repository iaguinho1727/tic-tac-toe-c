#ifndef TYPES_H
#define TYPES_H

#define BOARD_HEIGHT 3
#define BOARD_WIDTH 3
#define WIN_OCCURRENCES BOARD_WIDTH
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
#define COLOR_GOLD  "\x1b[33m"
#define COLOR_RED "\x1b[31m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_RESET "\x1b[0m"
#define CLEAR_CODE "\033[2J\033[H"
#define START_REVERSE_VIDEO "\033[7m"
#define END_REVERSE_VIDEO "\033[0m"
#define COLORED_MESSAGE(COLOR,TEXT) COLOR TEXT COLOR_RESET
#define PRINT_COLORED(COLOR,TEXT) printf(COLORED_MESSAGE(COLOR,TEXT))
#define FIRST_PLAYER_TURN PLAYER_X

#include <stdbool.h>
#include <stdio.h>

typedef struct CursorPosition {
	short int row;
	short int column;
} CursorPosition;

typedef enum KeyboardEvent {
	MARK,
	QUIT,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	RESET,
	UNKNOWN
} KeyboardEvent;

typedef enum CurrentGameState {
	PLAYER_X_WIN,
	PLAYER_O_WIN,
	DRAW,
	NOT_ENDED
} CurrentGameState;

typedef struct GameEvent {
	CurrentGameState state;
	KeyboardEvent key;
	char key_buffer[3];
} GameEvent;

typedef struct Game {
	GameEvent event;
	CursorPosition cursor;
	char current_player;
	char board[BOARD_WIDTH][BOARD_HEIGHT];
} Game;

#endif