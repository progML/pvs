
#ifndef __CONSOLE_H
#define __CONSOLE_H

#include <stdbool.h>

#include "stm32f4xx_hal.h"

#define BUF_SIZE 100

struct context;

struct console_ctx {
	UART_HandleTypeDef *huart;
	bool debug_mode;
	char received_symbol;
	bool enable_interrupt;
	bool transmitting;

//	char receive_buffer[BUF_SIZE + 1];
//	uint16_t receive_buffer_pos;
//	uint16_t echoed_pos;
//	bool command_finished;

//	uint8_t transmit_buffer[BUF_SIZE + 1];
//	uint16_t transmit_buffer_len;
};

void console_uart_rx_callback(struct console_ctx *ctx, UART_HandleTypeDef *huart);
void console_uart_tx_callback(struct console_ctx *ctx, UART_HandleTypeDef *huart);

//void receive_symbol(struct console_ctx *data);
void send_message(struct console_ctx *ctx, const char *msg);
void send_message_error(struct console_ctx *ctx, const char *msg);
void send_messagen(struct console_ctx *ctx, const char *msg, size_t len);

//void handle_console(struct console_ctx *ctx, void (*handle_command)(struct console_ctx*));

#endif
