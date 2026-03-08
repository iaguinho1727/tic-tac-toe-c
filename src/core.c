#include "core.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>

//   2 | 6 | 10    1 | 2 | 3
//  ---+---+---  ---+---+---
//   3 | 4 | 5   4 | 5 | 6
//  ---+---+---  ---+---+---
//   6 | 7 | 8   7 | 8 | 9

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
	printf("---+---+---\n");
	return true;
}

bool change_mouse_cursor_based_on_mouse_position(MousePosition* position)
{
	const short int POSITIONS_FOR_COLUMNS[]={2, 6 ,10};
	const short int POSITION_FOR_ROWS[]={0,3,5};
	const short int new_column=POSITIONS_FOR_COLUMNS[position->column];
	const short int new_row=POSITION_FOR_ROWS[position->row];
	printf("\033[%d;%dH", new_row, new_column); // move cursor, don't print anything
	fflush(stdout);
	return true;
}

bool print_cell(const char* board, short int index)
{
	const char item=board[index];
	printf(" %c ",item);
	return true;
}

void print_board_row(char board[BOARD_WIDTH][BOARD_HEIGHT],short int row)
{
	for(short int column=0;column+1<BOARD_HEIGHT;column++)
	{
		const char item=board[row][column];
		if(item==0)
		{
			printf("   ");
		}else{
			printf(" %c ",item);
		}
		printf("|");
	}
}

void print_tic_tac_toe_board( char board[BOARD_WIDTH][BOARD_HEIGHT])
{
	for(short int row=0;row<BOARD_WIDTH;row++)
	{
		print_board_row(board,row);
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
	return board[row][column]!=0;
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

void wait_for_user_input( char new_board[BOARD_WIDTH][BOARD_HEIGHT],MousePosition* position)
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


		default:

	}


}


void run_game_loop()
{
	char new_board[BOARD_WIDTH][BOARD_HEIGHT]={0};

	MousePosition position;
	position.column=0;
	position.row=0;
	while(true)
	{
		CLEAR_SCREEN();
		print_tic_tac_toe_board(new_board);
		change_mouse_cursor_based_on_mouse_position(&position);
		wait_for_user_input(new_board,&position);




	}
}
