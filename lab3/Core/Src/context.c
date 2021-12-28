
#include "note.h"
#include "context.h"

struct context global_ctx = {
	.console = {
		.huart = NULL,
		.enable_interrupt = false,
		.transmitting = false,
		.debug_mode = false,
//		.received_symbol = 0,
//		.receive_buffer = { 0, },
//		.receive_buffer_pos = 0,
//		.echoed_pos = 0,
//		.command_finished = false,
//		.transmit_buffer = { 0, },
//		.transmit_buffer_len = 0,

	},
	.keyboard = {
		.counters = { 0, },
	},
	.notes = {
		.duration = 10, // 1s
		.octave = OCT_FIRST,
		.has_play = 0,
	}
};

void context_init(UART_HandleTypeDef *huart) {
	global_ctx.console.huart = huart;
	keyboard_init(&global_ctx.keyboard);

	global_ctx.notes.events_queue = &global_ctx.keyboard.event_queue;

	buzzer_init();
}

struct console_ctx *context_get_console() {
	return &global_ctx.console;
}

struct keyboard_ctx *context_get_keyboard() {
	return &global_ctx.keyboard;
}

struct notes_ctx *context_get_notes() {
	return &global_ctx.notes;
}
