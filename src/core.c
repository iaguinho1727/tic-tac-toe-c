#include "core.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>

static struct termios orig_termios;

void restore_user_terminal(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void enable_raw_input(void) {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(restore_user_terminal);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);   /* no echo, read char-by-char */
    raw.c_cc[VMIN]  = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void exit_game(int sig)
{
	printf("Exiting game... Received signal %d\n", sig);
	_exit(0);
}

void setup_ctrl_c_signal()
{
	signal(SIGINT,exit_game);
}

void print_column()
{
	printf("|");
}
bool print_line()
{
	printf("\t---+---+---\n");
	return true;
}

void fill_board(char board[BOARD_WIDTH][BOARD_HEIGHT])
{
	for(short int r=0;r<BOARD_WIDTH;r++)
	{
		for(short c=0;c<BOARD_HEIGHT;c++)
		{
			board[r][c]=EMPTY;
		}
	}
}

void clear_screen()
{
	printf(CLEAR_CODE);
}

void print_highlight(const char item)
{
	printf(START_REVERSE_VIDEO" %c "END_REVERSE_VIDEO,item);
}

void print_board_row(char board[BOARD_WIDTH][BOARD_HEIGHT],short int row,MousePosition* cursor)
{
	for(short int column=0;column<BOARD_HEIGHT;column++)
	{
		const char item=board[row][column];
		const bool is_cursor=(cursor->column==column && cursor->row==row);
		if(is_cursor)
		{
			print_highlight(item);
		}
		else{
			printf(" %c ",item);

		}
		const bool is_not_last_cell=column<BOARD_WIDTH-1;
		if(is_not_last_cell)
		{
			printf("|");
		}

	}
}

const char get_mark_based_on_turn(unsigned short int* turn)
{
	return (*turn)%2==0 ? 'X' : 'O';
}


void render_game_screen( char board[BOARD_WIDTH][BOARD_HEIGHT],MousePosition* cursor,unsigned short int* turn)
{
	printf("\n  " COLOR_CYAN "Tic-Tac-Toe" COLOR_RESET "  (WASD move, SPACE place, Q quit)\n");
	const char current_player = get_mark_based_on_turn(turn);
	printf("  Player turn: " COLOR_GOLD "%c" COLOR_RESET " \n\n", current_player);
	for(short int row=0;row<BOARD_WIDTH;row++)
	{
		printf("\t");
		print_board_row(board,row,cursor);
		printf("\n");
		if(row>=2)
		{
			continue;
		}
		print_line();


	}
}

bool is_target_position_occupied(char board[BOARD_WIDTH][BOARD_HEIGHT],short int row,short column)
{
	return board[row][column]!=EMPTY;
}

bool set_mouse_position_up(MousePosition* position, char board[BOARD_WIDTH][BOARD_HEIGHT])
{
	const short int new_row = position->row - 1;
	if(new_row< 0)
	{
		return false;
	}

	if(is_target_position_occupied(board, new_row, position->column))
	{
		return false;
	}
	position->row = new_row;
	return true;
}

bool set_mouse_position_down(MousePosition* position, char board[BOARD_WIDTH][BOARD_HEIGHT])
{
	const short int new_row = position->row + 1;
	if(new_row >= BOARD_HEIGHT)
	{
		return false;
	}

	if(is_target_position_occupied(board, new_row, position->column))
	{
		return false;
	}
	position->row = new_row;
	return true;
}

bool set_mouse_position_left(MousePosition* position, char board[BOARD_WIDTH][BOARD_HEIGHT])
{
	const short int new_column = position->column - 1;
	if(new_column<0)
	{
		return false;
	}

	if(is_target_position_occupied(board, position->row, new_column))
	{
		return false;
	}
	position->column = new_column;
	return true;
}

bool set_mouse_position_right(MousePosition* position, char board[BOARD_WIDTH][BOARD_HEIGHT])
{
	const short int new_column = position->column + 1;
	if(new_column>=BOARD_WIDTH )
	{
		return false;
	}

	if(is_target_position_occupied(board, position->row, new_column))
	{
		return false;
	}
	position->column = new_column;
	return true;
}

bool set_player_mark(MousePosition* position,char board[BOARD_WIDTH][BOARD_HEIGHT],unsigned short int* turn)
{
	const char mark=get_mark_based_on_turn(turn);
	if(is_target_position_occupied(board,position->row,position->column))
	{
		return false;
	}
	board[position->row][position->column]=mark;
	return true;
}

char get_winner(char new_board[BOARD_WIDTH][BOARD_HEIGHT])
{
	unsigned short int occorences=0;
	for(unsigned short int r=0;r<BOARD_WIDTH;r++)
	{
		occorences=0;
		for(unsigned short int c=0;c<BOARD_HEIGHT;c++)
		{

		}
	}
}

void wait_for_user_input( char new_board[BOARD_WIDTH][BOARD_HEIGHT],MousePosition* position,unsigned short int* turn)
{
	char command=toupper(getchar());
	switch (command)
	{
		case UP:
			set_mouse_position_up(position,new_board);

			break;
		case DOWN:
			set_mouse_position_down(position,new_board);
			break;
		case LEFT:
			set_mouse_position_left(position,new_board);
			break;
		case RIGHT:
			set_mouse_position_right(position,new_board);
			break;
		case SPACE:
			set_player_mark(position,new_board,turn);
			(*turn)++;
			break;
		case QUIT:
		case ESC:
			exit_game(0);


		default:

	}


}


void run_game_loop()
{
	char new_board[BOARD_WIDTH][BOARD_HEIGHT]={0};
	fill_board(new_board);

	MousePosition position;
	position.column=0;
	position.row=0;
	unsigned short turn=0;
	while(true)
	{
		clear_screen();
		render_game_screen(new_board,&position,&turn);
		wait_for_user_input(new_board,&position,&turn);
	}
}
