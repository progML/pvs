#include "main.h"
#include <string.h>
#include <stdio.h>
#include "context.h"
#include "pca9538.h"
#include "keyboard.h"
#include "console.h"

void keyboard_init(struct keyboard_ctx *ctx) {
	queue_init(&ctx->event_queue);

	uint8_t buf = 0x70;
//	uint8_t buf = 0x07;
	HAL_StatusTypeDef pca9538WriteRegister = PCA9538_write_register(KBRD_WR_ADDR, CONFIG, &buf);
//	uint8_t buf = 0x07;

	if (pca9538WriteRegister != HAL_OK) {
		send_message_error(context_get_console(), "Error write config1\n\r");
	}
}

uint8_t check_row(uint8_t row) {
	uint8_t buf = 0;
	if (PCA9538_write_register(KBRD_WR_ADDR, OUTPUT_PORT, &buf) != HAL_OK) {
		send_message_error(context_get_console(), "Error write output2\n\r");
	}

	buf = row;
	if (PCA9538_write_register(KBRD_WR_ADDR, OUTPUT_PORT, &buf) != HAL_OK) {
		send_message_error(context_get_console(), "Error write output4\n\r");
	}

	buf = 0;
	if (PCA9538_read_inputs(KBRD_RD_ADDR, &buf) != HAL_OK) {
		send_message_error(context_get_console(), "Read error\n\r");
	}

	uint8_t kbd_in = buf & 0x70;
	if (kbd_in == 0x70) {
		return 0x00;
	}

	uint8_t key = kbd_in;
	if (row == ROW1 || row == ROW2 || row == ROW3 || row == ROW4) {
		if (!(kbd_in & 0x10)) {
			key = LEFT;
		} else if (!(kbd_in & 0x20)) {
			key = CNTR;
		} else if (!(kbd_in & 0x40)) {
			key = RGHT;
		}
	}

	return key;
}

void handle_keyboard(struct keyboard_ctx *ctx) {
	const uint8_t ROWS[] = { ROW1, ROW2, ROW3, ROW4 };
	bool presses[KEYS_NUM] = { 0 };

	for (int i = 0; i < sizeof(ROWS) / sizeof(uint8_t); i++) {
		uint8_t row = ROWS[i];
		uint8_t key = check_row(row);

		if (key != LEFT && key != CNTR && key != RGHT) {
			continue;
		}

		uint8_t num = i*3 + (key == LEFT ? 1 : (key == CNTR ? 2 : 3)) - 1;
		presses[num] = true;
	}

	for (uint8_t i = 0; i < KEYS_NUM; i++) {
		if (presses[i]) {
			if (ctx->counters[i] <= NOISE_TICKS) {
				ctx->counters[i] += 1;
			}
		} else {
			ctx->counters[i] = 0;
		}

		if (ctx->counters[i] == NOISE_TICKS) {
			uint32_t mask = __get_PRIMASK();
			__disable_irq();
			queue_enqueue(&ctx->event_queue, i + 1); // 1-12
			__enable_irq();
			__set_PRIMASK(mask);
		}
	}
}

void handle_keyboard_events_debug(struct keyboard_ctx *ctx) {
	struct console_ctx *console = context_get_console();
	uint32_t mask = __get_PRIMASK();
	__disable_irq();
	uint8_t key = queue_dequeue(&(ctx->event_queue));
	__enable_irq();
	__set_PRIMASK(mask);

	char buf[25] = { 0 };
	if(key) {
		sprintf(buf, "KEY PRESS: %d\n\r", key);
	}

	if (buf[0] != 0) {
		send_message(console, buf);
	}
}

