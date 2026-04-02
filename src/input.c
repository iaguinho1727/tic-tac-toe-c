#include "input.h"
#include "board.h"
#include "platform.h"
#include "game.h"
#include <string.h>
#include <ctype.h>
#include <errno.h>
#ifndef __EMSCRIPTEN__
#include <unistd.h>
#include <stdio.h>
#endif

bool is_special_key(char* buffer)
{
	return strncmp("\033[",buffer,2)==0;
}

bool is_esc_key(char* buffer)
{
	return strncmp("\033",buffer,1)==0;
}

void handle_special_key_event(GameEvent* event)
{
	switch(event->key_buffer[2])
	{
	case UP_ARROW:
		event->key=UP;
		break;
	case DOWN_ARROW:
		event->key=DOWN;
		break;
	case LEFT_ARROW:
		event->key=LEFT;
		break;
	case RIGHT_ARROW:
		event->key=RIGHT;
		break;
	default:
		event->key=UNKNOWN;
		break;
	}
}

bool on_cursor_up(CursorPosition* cursor)
{
	const short int new_row=cursor->row-1;
	if(new_row<0) return false;
	cursor->row=new_row;
	return true;
}

bool on_cursor_down(CursorPosition* cursor)
{
	const short int new_row=cursor->row+1;
	if(new_row>=BOARD_HEIGHT) return false;
	cursor->row=new_row;
	return true;
}

bool on_cursor_left(CursorPosition* cursor)
{
	const short int new_column=cursor->column-1;
	if(new_column<0) return false;
	cursor->column=new_column;
	return true;
}

bool on_cursor_right(CursorPosition* cursor)
{
	const short int new_column=cursor->column+1;
	if(new_column>=BOARD_WIDTH) return false;
	cursor->column=new_column;
	return true;
}

bool on_set_player_mark(Game* game)
{
	if(is_target_position_occupied(game) || game->event.state!=NOT_ENDED)
	{
		return false;
	}
	mark_board_cell(game);
	change_turn(game);
	return true;
}

void handle_keyboard_events(Game* game)
{
	switch(game->event.key)
	{
	case UP:
		on_cursor_up(&(game->cursor));
		break;
	case DOWN:
		on_cursor_down(&(game->cursor));
		break;
	case LEFT:
		on_cursor_left(&(game->cursor));
		break;
	case RIGHT:
		on_cursor_right(&(game->cursor));
		break;
	case QUIT:
		exit_game(0);
		break;
	case MARK:
		on_set_player_mark(game);
		break;
	case RESET:
		initialize_game(game);
		break;
	default:
		break;
	}
}

#ifdef __EMSCRIPTEN__
EM_BOOL on_keydown(int event_type, const EmscriptenKeyboardEvent *e, void *user_data)
{
	(void)event_type;
	Game *game=(Game *)user_data;

	if(strcmp(e->key,"ArrowUp")==0 || strcmp(e->key,"w")==0 || strcmp(e->key,"W")==0)
		game->event.key=UP;
	else if(strcmp(e->key,"ArrowDown")==0 || strcmp(e->key,"s")==0 || strcmp(e->key,"S")==0)
		game->event.key=DOWN;
	else if(strcmp(e->key,"ArrowLeft")==0 || strcmp(e->key,"a")==0 || strcmp(e->key,"A")==0)
		game->event.key=LEFT;
	else if(strcmp(e->key,"ArrowRight")==0 || strcmp(e->key,"d")==0 || strcmp(e->key,"D")==0)
		game->event.key=RIGHT;
	else if(strcmp(e->key," ")==0)
		game->event.key=MARK;
	else if(strcmp(e->key,"r")==0 || strcmp(e->key,"R")==0)
		game->event.key=RESET;
	else
		game->event.key=UNKNOWN;

	return EM_TRUE;
}
#else
void check_keyboard_event(Game* game)
{
	memset(game->event.key_buffer,0,sizeof(game->event.key_buffer));
	ssize_t bytes_read=read(0,game->event.key_buffer,sizeof(game->event.key_buffer));
	if(bytes_read<=0)
	{
		is_running=false;
		return;
	}
	if(bytes_read==-1 && errno!=EINTR)
	{
		perror(COLORED_MESSAGE(COLOR_RED,"\nFailed to read bytes from stdin  "));
		is_running=false;
		return;
	}
	bool has_esc_sequence=is_esc_key(game->event.key_buffer);
	bool special_key=is_special_key(game->event.key_buffer);
	if(has_esc_sequence && !special_key)
	{
		game->event.key=QUIT;
		return;
	}
	else if(special_key)
	{
		handle_special_key_event(&(game->event));
		return;
	}
	const char upper_cased_input=toupper(game->event.key_buffer[0]);
	switch(upper_cased_input)
	{
	case W_KEY:     game->event.key=UP;      break;
	case S_KEY:     game->event.key=DOWN;    break;
	case A_KEY:     game->event.key=LEFT;    break;
	case D_KEY:     game->event.key=RIGHT;   break;
	case SPACE_KEY: game->event.key=MARK;    break;
	case R_KEY:     game->event.key=RESET;   break;
	case Q_KEY:     game->event.key=QUIT;    break;
	default:        game->event.key=UNKNOWN; break;
	}
}
#endif
