#ifndef PLATFORM_H
#define PLATFORM_H

#ifdef __EMSCRIPTEN__
#include <stdbool.h>
extern volatile bool is_running;
#else
#include <signal.h>
extern volatile sig_atomic_t is_running;
extern void enable_raw_input(void);
extern void restore_user_terminal(void);
extern void setup_ctrl_c_signal(void);
#endif

extern void exit_game(int sig);

#endif