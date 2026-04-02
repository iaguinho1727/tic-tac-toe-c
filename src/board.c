#include "board.h"

void initialize_board(Game* game)
{
	for(short int r=0;r<BOARD_WIDTH;r++)
	{
		for(short c=0;c<BOARD_HEIGHT;c++)
		{
			game->board[r][c]=EMPTY;
		}
	}
}

bool is_board_full(Game* game)
{
	for(int r=0;r<BOARD_WIDTH;r++)
		for(int c=0;c<BOARD_HEIGHT;c++)
			if(game->board[r][c]==EMPTY) return false;
	return true;
}

void mark_board_cell(Game* game)
{
	game->board[game->cursor.row][game->cursor.column]=game->current_player;
}

bool is_target_position_occupied(Game* game)
{
	return game->board[game->cursor.row][game->cursor.column]!=EMPTY;
}

void change_turn(Game* game)
{
	game->current_player=game->current_player==PLAYER_O ? PLAYER_X : PLAYER_O;
}

bool has_won_horizontally(Game* game,char* current_player)
{
	for(unsigned short int r=0;r<BOARD_WIDTH;r++)
	{
		unsigned short int occurrences=0;
		for(unsigned short int c=0;c<BOARD_HEIGHT;c++)
		{
			if(game->board[r][c]!=*current_player) continue;
			occurrences++;
		}
		if(occurrences==WIN_OCCURRENCES) return true;
	}
	return false;
}

bool has_won_vertically(Game* game, char* current_player)
{
	for(unsigned short int r=0;r<BOARD_WIDTH;r++)
	{
		unsigned short int occurrences=0;
		for(unsigned short int c=0;c<BOARD_HEIGHT;c++)
		{
			if(game->board[c][r]!=*current_player) continue;
			occurrences++;
		}
		if(occurrences==WIN_OCCURRENCES) return true;
	}
	return false;
}

bool has_won_diagonally(Game* game,char* current_player)
{
	bool main_diagonal=true;
	for(unsigned short int i=0;i<BOARD_WIDTH && main_diagonal;i++)
	{
		main_diagonal=game->board[i][i]==*current_player;
	}
	bool anti_diagonal=true;
	for(unsigned short int i=0;i<BOARD_WIDTH && anti_diagonal;i++)
	{
		anti_diagonal=game->board[i][BOARD_WIDTH-1-i]==*current_player;
	}
	return main_diagonal || anti_diagonal;
}

bool is_there_winner(Game* game,char current_player)
{
	return has_won_horizontally(game,&current_player)
		|| has_won_vertically(game,&current_player)
		|| has_won_diagonally(game,&current_player);
}

void check_current_game_state(Game* game)
{
	if(is_there_winner(game,PLAYER_X))
		game->event.state=PLAYER_X_WIN;
	else if(is_there_winner(game,PLAYER_O))
		game->event.state=PLAYER_O_WIN;
	else if(is_board_full(game))
		game->event.state=DRAW;
	else
		game->event.state=NOT_ENDED;
}
