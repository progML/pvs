
#include <string.h>
#include <stdio.h>

#include "stm32f4xx_hal.h"

#include "console.h"
#include "note.h"
#include "context.h"

const uint8_t NOTES_TABLE[] = { NOTE_C0, NOTE_D0, NOTE_E0, NOTE_F0, NOTE_G0, NOTE_A0, NOTE_B0 };
const char NOTES_LETTERS[] = { 'C', 'D', 'E', 'F', 'G', 'A', 'B' };

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim7;

void buzzer_init(void) {
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	TIM1->PSC = (2560) - 1;
}

void buzzer_set_freq(uint16_t freq) {
	uint16_t counter = (65625 / freq) - 1;
	TIM1->ARR = counter;
	TIM1->CCR1 = counter / 2; // PWM 50%
}

void buzzer_set_volume(uint16_t volume) {
	if (volume > BUZZER_VOLUME_MAX)
		volume = BUZZER_VOLUME_MAX;
	TIM1->CCR1 = volume;
	TIM1->CNT = 0;
	TIM1->ARR = 0;
}

void buzzer_play_note(uint8_t base_freq, uint8_t octave, uint32_t dur) {
	buzzer_set_freq(base_freq * (1 << octave));
	struct notes_ctx *notes = context_get_notes();
	notes->has_play = 1;
	htim7.Instance->ARR = dur;
	HAL_TIM_Base_Start_IT(&htim7);
}

void handle_keyboard_events(struct notes_ctx *ctx) {
	struct console_ctx *console = context_get_console();
	uint32_t mask = __get_PRIMASK();
	__disable_irq();
	uint8_t key = queue_dequeue(ctx->events_queue);
	__enable_irq();
	__set_PRIMASK(mask);
	switch (key) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			sprintf(ctx->notes_msg_buf, "Freq: %d; PLAYING: %c%d\n\r", (NOTES_TABLE[key - 1] * (1 << ctx->octave)), NOTES_LETTERS[key - 1], ctx->octave);
			buzzer_play_note(NOTES_TABLE[key - 1], ctx->octave, ctx->duration * 200);
			break;
		case 8:
			if (ctx->octave < OCT_FIFTH) {
				ctx->octave++;
			}
			sprintf(ctx->notes_msg_buf, "OCTAVE++: %d\n\r", ctx->octave);
			break;
		case 9:
			if (ctx->octave != OCT_SUBCONTR) {
				ctx->octave--;
			}
			sprintf(ctx->notes_msg_buf, "OCTAVE--: %d\n\r", ctx->octave);
			break;
		case 10:
			if (ctx->duration < 0xFF) {
				ctx->duration++;
			}
			sprintf(ctx->notes_msg_buf, "DURATION++: %dms\n\r", ctx->duration * 100);
			break;
		case 11:
			if (ctx->duration != 1) {
				ctx->duration--;
			}
			sprintf(ctx->notes_msg_buf, "DURATION--: %dms\n\r", ctx->duration * 100);
			break;
		case 12:
			mask = __get_PRIMASK();
			__disable_irq();
			for(uint8_t i = 1; i < 8; i++ ) {
				queue_enqueue(ctx->events_queue, i); // 1-12
			}
			__enable_irq();
			__set_PRIMASK(mask);
			break;
		default:
			ctx->notes_msg_buf[0] = 0;
	}
	if (ctx->notes_msg_buf[0] != 0) {
		send_message(console, ctx->notes_msg_buf);
	}
}
