#include "core.h"
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <string.h>
static struct termios orig_termios;
volatile sig_atomic_t is_runnig = true;

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
	printf(COLOR_RED"\nExiting game... Received signal %d\n"COLOR_RESET, sig);
	is_runnig=false;
}

void setup_ctrl_c_signal()
{
	struct sigaction sa = {0};
	sa.sa_handler = exit_game;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

void print_column()
{
	printf("|");
}
bool print_line()
{
	printf(COLOR_GOLD"\t---+---+---\n"COLOR_RESET);
	return true;
}

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

void clear_screen()
{
	printf(CLEAR_CODE);
}

void print_highlight(const char item)
{
	printf(COLOR_CYAN START_REVERSE_VIDEO" %c "END_REVERSE_VIDEO COLOR_RESET,item);
}
const char* get_mark_color(char item)
{
	return item==PLAYER_X ? COLOR_RED : COLOR_BLUE;
}

void print_board_row(Game* game,short int row)
{
	const MousePosition* cursor=&(game->cursor);
	for(short int column=0;column<BOARD_HEIGHT;column++)
	{
		const char item=game->board[row][column];
		const bool is_cursor=(cursor->column==column && cursor->row==row);
		if(is_cursor && game->event.state==NOT_ENDED)
		{
			print_highlight(item);
		}
		else{
			const char* color=get_mark_color(item);
			printf("%s %c "COLOR_RESET,color,item);

		}
		const bool is_not_last_cell=column<BOARD_WIDTH-1;
		if(is_not_last_cell)
		{
			printf(COLOR_GOLD"|"COLOR_RESET);
		}

	}
}

void print_tic_tac_toe_board(Game* game)
{
	for(short int row=0;row<BOARD_WIDTH;row++)
	{
		printf("\t");
		print_board_row(game,row);
		printf("\n");
		if(row>=2)
		{
			continue;
		}
		print_line();


	}
}

void print_player_wins_message(char current_player)
{
	PRINT_COLORED(COLOR_CYAN,"  Player ");
	print_colored_mark(current_player);
	PRINT_COLORED(COLOR_CYAN," WINS!");
}

void print_dawn_message()
{
	PRINT_COLORED(COLOR_RED,"  DAWN NOBODY WON!");
}

void print_current_game_state(CurrentGameState* state)
{
	if(*state==PLAYER_X_WIN)
	{
		print_player_wins_message(PLAYER_X);
	}else if(*state==PLAYER_O_WIN)
	{
		print_player_wins_message(PLAYER_O);
	}
	else if(*state==DAWN)
	{
		print_dawn_message();
	}
}
void print_game_basic_instructions()
{
	printf("\n  " COLOR_CYAN "Tic-Tac-Toe" COLOR_GOLD "  (WASD or ARROW KEYS to move, SPACE place, Q quit, R reset)\n"COLOR_RESET);
}


void print_colored_mark(char current_player)
{
	printf("%s%c"COLOR_RESET,get_mark_color(current_player),current_player);
}

void print_current_player_turn(char current_player)
{
	PRINT_COLORED(COLOR_CYAN,"  Player Turn: ");
	print_colored_mark(current_player);
	printf("\n");
}




void render_game_screen( Game* game)
{
	print_game_basic_instructions();
	print_current_player_turn(game->current_player);
	CurrentGameState state=game->event.state;
	print_current_game_state(&state);
	printf("\n\n");
	print_tic_tac_toe_board(game);

}

bool is_target_position_occupied(Game* game)
{
	return game->board[game->cursor.row][game->cursor.column]!=EMPTY;
}

bool on_cursor_up(MousePosition* cursor)
{
	const short int new_row = cursor->row - 1;
	if(new_row< 0)
	{
		return false;
	}
	cursor->row = new_row;
	return true;
}

bool on_cursor_down(MousePosition* cursor)
{
	const short int new_row = cursor->row + 1;
	if(new_row >= BOARD_HEIGHT)
	{
		return false;
	}
	cursor->row = new_row;
	return true;
}

bool on_cursor_left(MousePosition* cursor)
{
	const short int new_column = cursor->column - 1;
	if(new_column<0)
	{
		return false;
	}
	cursor->column = new_column;
	return true;
}

bool on_cursor_right(MousePosition* cursor)
{
	const short int new_column = cursor->column + 1;
	if(new_column>=BOARD_WIDTH )
	{
		return false;
	}
	cursor->column = new_column;
	return true;
}

void change_turn(Game* game)
{
	game->current_player=game->current_player==PLAYER_O ? PLAYER_X : PLAYER_O;
}

void mark_board_cell(Game* game)
{
	game->board[game->cursor.row][game->cursor.column]=game->current_player;
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

bool is_board_full(Game* game)
{

	unsigned short int counted_not_empty_cells=0;
	for(unsigned short int r=0;r<BOARD_WIDTH;r++)
	{
		for(unsigned short int c=0;c<BOARD_HEIGHT;c++)
		{
			if(game->board[r][c]==EMPTY)
			{
				continue;
			}
			counted_not_empty_cells++;
		}
	}
	return counted_not_empty_cells==BOARD_HEIGHT*BOARD_HEIGHT;
}



void check_current_game_state(Game* game)
{
	if(is_there_winner(game,PLAYER_X))
	{
		game->event.state=PLAYER_X_WIN;
	}else if(is_there_winner(game,PLAYER_O))
	{
		game->event.state=PLAYER_O_WIN;
	}else if(is_board_full(game))
	{
		game->event.state=DAWN;
	}else{
		game->event.state=NOT_ENDED;
	}
}

bool has_won_horizontally(Game* game,char current_player)
{

	for(unsigned short int r=0;r<BOARD_WIDTH;r++)
	{
		unsigned short int occorences=0;
		for(unsigned short int c=0;c<BOARD_HEIGHT;c++)
		{
			if(game->board[r][c]!=current_player)
			{
				continue;
			}
			occorences++;
		}
		if(occorences==WIN_OCORRENCES) return true;
	}
	return false;

}

bool has_won_vertically(Game* game, char current_player)
{

	for(unsigned short int r=0;r<BOARD_WIDTH;r++)
	{
		unsigned short int ocorrences=0;
		for(unsigned short int c=0;c<BOARD_HEIGHT;c++)
		{
			if(game->board[c][r]!=current_player)
			{
				continue;
			}
			ocorrences++;
		}
		if(ocorrences==WIN_OCORRENCES) return true;
	}
	return false;

}

bool has_won_diagonally(Game* game,char current_player)
{
	const bool fisrt_diagonal=game->board[0][0]==current_player &&
	 game->board[1][1]==current_player &&
	  game->board[2][2]==current_player;

	const bool second_diagonal=game->board[0][2]==current_player && game->board[1][1]==current_player && game->board[2][0]==current_player;
	return fisrt_diagonal || second_diagonal;

}

bool is_there_winner(Game* game,char current_player)
{
	return has_won_horizontally(game,current_player) || has_won_vertically(game,current_player)
	|| has_won_diagonally(game,current_player);
}

bool is_especial_key(char* buffer)
{
	return strncmp("\033[",buffer,2)==0;
}

bool is_esc_key(char* buffer)
{
	return strncmp("\033",buffer,1)==0;
}

void handle_special_key_event(GameEvent* event)
{
	switch (event->key_buffer[2])
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
	}
}
void reset_turn(Game* game)
{
	game->current_player=FIRST_PLAYER_TURN;
}

void on_reset_game(Game* game)
{
	initialize_game(game);
}

void handle_game_events(Game* game)
{
	check_keyboard_event(game);


	handle_keyboard_events(game);
	check_current_game_state(game);

}

bool handle_keyboard_events(Game* game)
{
	switch (game->event.key)
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
		on_reset_game(game);
		break;

	default:
		break;
	}
	return true;
}

bool check_keyboard_event( Game* game)
{
	read(0,game->event.key_buffer,sizeof(game->event.key_buffer));
	bool has_esc_sequence=is_esc_key(game->event.key_buffer);
	bool special_key=is_especial_key(game->event.key_buffer);
	if(has_esc_sequence && !special_key)
	{
		game->event.key=QUIT;
		return true;
	}else if(special_key)
	{

		handle_special_key_event(&(game->event));
		return true;

	}
	const char upper_cased_input=toupper(game->event.key_buffer[0]);
	game->event.key=upper_cased_input;
	switch (upper_cased_input)
	{
		case W_KEY:
			game->event.key=UP;
			break;
		case S_KEY:
			game->event.key=DOWN;
			break;
		case A_KEY:
			game->event.key=LEFT;
			break;
		case D_KEY:
			game->event.key=RIGHT;
			break;
		case SPACE_KEY:
			game->event.key=MARK;
			break;
		case R_KEY:
			game->event.key=RESET;
			break;
		case Q_KEY:
			game->event.key=QUIT;
			break;


	}
	return true;


}

void initialize_game(Game* game)
{
	*game=(Game){
		.cursor={
			.column=0,
			.row=0
		},
		.event={
			.key_buffer={0},
			.state=NOT_ENDED
		},
		.current_player=FIRST_PLAYER_TURN,
		.board={{0}}

	};

	initialize_board(game);
}


void run_game_loop(Game* new_game)
{
	while(is_runnig)
	{
		clear_screen();
		render_game_screen(new_game);
		handle_game_events(new_game);
	}
}
