#ifndef __KEYBOARD_H_
#define __KEYBOARD_H_

#include <stdint.h>

#include "queue.h"

#define KBRD_RD_ADDR 0xE3
#define KBRD_WR_ADDR 0xE2

#define ROW1 0x1E
#define ROW2 0x3D
#define ROW3 0x7B
#define ROW4 0xF7

#define LEFT 0x04
#define CNTR 0x02
#define RGHT 0x01

#define NOISE_TICKS 5
#define KEYS_NUM 12

struct keyboard_ctx {
	struct queue event_queue;
	uint8_t counters[KEYS_NUM];
};

void keyboard_init(struct keyboard_ctx *ctx);

uint8_t check_row(uint8_t  row);

void handle_keyboard(struct keyboard_ctx *ctx);
void handle_keyboard_events_debug();

#endif
