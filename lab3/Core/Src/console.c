#include <string.h>

#include "console.h"

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
void console_uart_rx_callback(struct console_ctx *ctx, UART_HandleTypeDef *huart) {
//	if (ctx->huart == huart) {
//		receive_symbol(ctx);
//	}
}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
void console_uart_tx_callback(struct console_ctx *ctx, UART_HandleTypeDef *huart) {
	if (ctx->huart == huart) {
		ctx->transmitting = false;
	}
}

void send_message_error(struct console_ctx *ctx, const char *msg) {
	HAL_UART_Transmit(ctx->huart, (uint8_t *)msg, strlen(msg), 1000);
}


void send_message(struct console_ctx *ctx, const char *msg) {
	send_messagen(ctx, msg, strlen(msg));
}

void send_messagen(struct console_ctx *ctx, const char *msg, size_t len) {
	if (ctx->enable_interrupt) {
		while (ctx->transmitting) { }
	}

	if (ctx->enable_interrupt) {
		HAL_UART_Transmit_IT(ctx->huart, (uint8_t *)msg, len);
		ctx->transmitting = true;
	} else {
		HAL_UART_Transmit(ctx->huart, (uint8_t *)msg, len, 1000);
	}

}

//void receive_symbol(struct console_ctx *ctx) {
//	switch (ctx->received_symbol) {
//		case '\r':
//		case '\n':
//		case '\0':
//			ctx->receive_buffer[ctx->receive_buffer_pos] = '\0';
//			ctx->command_finished = true;
//			return;
//		default:
//			ctx->receive_buffer[ctx->receive_buffer_pos] = ctx->received_symbol;
//			ctx->receive_buffer_pos++;
//			if(ctx->receive_buffer_pos >= BUF_SIZE) {
//				ctx->receive_buffer[BUF_SIZE] = '\0';
//				ctx->receive_buffer_pos = BUF_SIZE;
//				ctx->command_finished = true;
//				return;
//			}
//			break;
//	}
//	ctx->command_finished = false;
//}

//void handle_console(struct console_ctx *ctx, void (*handle_command)(struct console_ctx*)) {
//	HAL_StatusTypeDef status;
//	if (ctx->enable_interrupt) {
//		status = HAL_UART_Receive_IT(ctx->huart, (uint8_t*) &ctx->received_symbol, sizeof(ctx->received_symbol));
//	} else {
//		status = HAL_UART_Receive(ctx->huart, (uint8_t*) &ctx->received_symbol, sizeof(ctx->received_symbol), 100);
//	}
//
//	if (status != HAL_OK) {
//		return;
//	}
//
//	if (!ctx->enable_interrupt) {
//		receive_symbol(ctx);
//	}
//
//	if (ctx->echoed_pos < ctx->receive_buffer_pos) {
//		send_messagen(ctx, &ctx->receive_buffer[ctx->echoed_pos], ctx->receive_buffer_pos - ctx->echoed_pos);
//		ctx->echoed_pos = ctx->receive_buffer_pos;
//	}
//
//	if (ctx->command_finished) {
//		handle_command(ctx);
//	}
//}

