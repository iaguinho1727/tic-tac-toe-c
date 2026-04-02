#ifndef INPUT_H
#define INPUT_H

#include "types.h"

extern bool is_special_key(char* buffer);
extern bool is_esc_key(char* buffer);
extern void handle_special_key_event(GameEvent* event);
extern void handle_keyboard_events(Game* game);
extern bool on_cursor_up(CursorPosition* cursor);
extern bool on_cursor_down(CursorPosition* cursor);
extern bool on_cursor_left(CursorPosition* cursor);
extern bool on_cursor_right(CursorPosition* cursor);
extern bool on_set_player_mark(Game* game);

#ifndef __EMSCRIPTEN__
extern void check_keyboard_event(Game* game);
#else
#include <emscripten/html5.h>
EM_BOOL on_keydown(int event_type, const EmscriptenKeyboardEvent* e, void* user_data);
#endif

#endif
