
#ifndef __CONTEXT_H
#define __CONTEXT_H

#include "console.h"
#include "keyboard.h"
#include "note.h"

struct context {
	struct console_ctx console;
	struct keyboard_ctx keyboard;
	struct notes_ctx notes;
};

void context_init();
struct console_ctx *context_get_console();
struct keyboard_ctx *context_get_keyboard();
struct notes_ctx *context_get_notes();

#endif
