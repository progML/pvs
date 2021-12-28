
#ifndef __NOTE_H_
#define __NOTE_H_

#include <stdint.h>

#include "queue.h"

/*
	1 	16,352 	До2 	C2 	C0 	Субконтроктава
	2 	18,354 	Ре2 	D2 	D0
	3 	20,602 	Ми2 	E2 	E0
	4 	21,827 	Фа2 	F2 	F0
	5 	24,500 	Соль2 	G2 	G0
	6 	27,500 	Ля2 	A2 	A0
	7 	30,868 	Си2 	H2* 	B0
*/

#define NOTE_C0 16
#define NOTE_D0 18
#define NOTE_E0 21
#define NOTE_F0 22
#define NOTE_G0 24
#define NOTE_A0 27
#define NOTE_B0 31

#define OCT_SUBCONTR 0
#define OCT_CONTR 1
#define OCT_BIG 2
#define OCT_SMALL 3
#define OCT_FIRST 4
#define OCT_SECOND 5
#define OCT_THIRD 6
#define OCT_FOURTH 7
#define OCT_FIFTH 8

struct notes_ctx {
	uint8_t octave;
	uint8_t duration;
	char notes_msg_buf[128];
	uint8_t has_play;
	struct queue *events_queue;
};

#define BUZZER_VOLUME_MAX	10
#define BUZZER_VOLUME_MUTE	0

void buzzer_init (void);
void buzzer_set_freq(uint16_t freq);
void buzzer_set_volume(uint16_t volume);
void buzzer_play_note(uint8_t base_freq, uint8_t octave, uint32_t dur);

void handle_keyboard_events(struct notes_ctx *ctx);

#endif
