#include "platform.h"
#include "types.h"
#include <stdlib.h>

#ifdef __EMSCRIPTEN__
volatile bool is_running=true;
#else
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
static struct termios orig_termios;
volatile sig_atomic_t is_running=true;

void restore_user_terminal(void)
{
	int restored_terminal_result=tcsetattr(STDIN_FILENO,TCSANOW,&orig_termios);
	if(restored_terminal_result==-1)
	{
		perror(COLORED_MESSAGE(COLOR_RED,"Failed to restore user's terminal"));
		exit(EXIT_FAILURE);
	}
}

void enable_raw_input(void)
{
	int terminal_copy_result=tcgetattr(STDIN_FILENO,&orig_termios);
	if(terminal_copy_result==-1)
	{
		perror(COLORED_MESSAGE(COLOR_RED,"Failed to make a copy of user's terminal"));
		exit(EXIT_FAILURE);
	}
	struct termios raw=orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	raw.c_cc[VMIN]=1;
	raw.c_cc[VTIME]=1;
	int new_terminal_result=tcsetattr(STDIN_FILENO,TCSANOW,&raw);
	if(new_terminal_result==-1)
	{
		perror(COLORED_MESSAGE(COLOR_RED,"Failed to apply raw mode to user's current terminal"));
		exit(EXIT_FAILURE);
	}
}

void setup_ctrl_c_signal(void)
{
	struct sigaction sa={0};
	sa.sa_handler=exit_game;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sigaction(SIGINT,&sa,NULL);
}
#endif

void exit_game(int sig)
{
	(void)sig;
	is_running=false;
}
