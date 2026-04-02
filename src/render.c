#include "render.h"
#include <stdio.h>

void clear_screen(void)
{
	printf(CLEAR_CODE);
}

void print_column(void)
{
	PRINT_COLORED(COLOR_GOLD,"|");
}

void print_line(void)
{
	printf(COLOR_GOLD"\t---+---+---\n"COLOR_RESET);
}

void print_highlight(const char item)
{
	printf(COLOR_CYAN START_REVERSE_VIDEO" %c "END_REVERSE_VIDEO COLOR_RESET,item);
}

const char* get_mark_color(char* item)
{
	return *item==PLAYER_X ? COLOR_RED : COLOR_BLUE;
}

void print_board_row(Game* game,short int* row)
{
	const CursorPosition* cursor=&(game->cursor);
	for(short int column=0;column<BOARD_HEIGHT;column++)
	{
		char item=game->board[*row][column];
		const bool is_cursor=(cursor->column==column && cursor->row==*row);
		if(is_cursor && game->event.state==NOT_ENDED)
		{
			print_highlight(item);
		}
		else
		{
			const char* color=get_mark_color(&item);
			printf("%s %c "COLOR_RESET,color,item);
		}
		if(column<BOARD_WIDTH-1)
		{
			print_column();
		}
	}
}

void print_tic_tac_toe_board(Game* game)
{
	for(short int row=0;row<BOARD_WIDTH;row++)
	{
		printf("\t");
		print_board_row(game,&row);
		printf("\n");
		if(row<BOARD_WIDTH-1)
		{
			print_line();
		}
	}
}

void print_player_wins_message(char current_player)
{
	PRINT_COLORED(COLOR_CYAN,"  Player ");
	print_colored_mark(&current_player);
	PRINT_COLORED(COLOR_CYAN," WINS!");
}

void print_draw_message(void)
{
	PRINT_COLORED(COLOR_RED,"  DRAW NOBODY WON!");
}

void print_current_game_state(CurrentGameState* state)
{
	switch(*state)
	{
	case PLAYER_X_WIN:
		print_player_wins_message(PLAYER_X);
		break;
	case PLAYER_O_WIN:
		print_player_wins_message(PLAYER_O);
		break;
	case DRAW:
		print_draw_message();
		break;
	default:
		break;
	}
}

void print_colored_mark(char* current_player)
{
	printf("%s%c"COLOR_RESET,get_mark_color(current_player),*current_player);
}

void print_current_player_turn(char* current_player)
{
	PRINT_COLORED(COLOR_CYAN,"  Player Turn: ");
	print_colored_mark(current_player);
	printf("\n");
}

void print_game_basic_instructions(void)
{
	PRINT_COLORED(COLOR_CYAN,"\n  ""Tic-Tac-Toe");
#ifndef __EMSCRIPTEN__
	PRINT_COLORED(COLOR_GOLD,"  (WASD or ARROW KEYS to move, SPACE place, Q quit, R reset)\n");
#else
	PRINT_COLORED(COLOR_GOLD,"  (WASD or ARROW KEYS to move, SPACE place, R reset)\n");
#endif
}

void render_game_screen(Game* game)
{
	print_game_basic_instructions();
	print_current_player_turn(&(game->current_player));
	CurrentGameState state=game->event.state;
	print_current_game_state(&state);
	printf("\n\n");
	print_tic_tac_toe_board(game);
}
