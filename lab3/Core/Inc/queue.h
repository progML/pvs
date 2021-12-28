
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdint.h>

#define QUEUE_LEN 100
#define QUEUE_ITEM uint8_t

struct queue {
	volatile int front;
	volatile int rear;
	volatile int size;
	volatile int capacity;
	QUEUE_ITEM data[QUEUE_LEN];
};

void queue_init(struct queue*);
void queue_enqueue(struct queue*, QUEUE_ITEM item);
QUEUE_ITEM queue_dequeue(struct queue*);

#endif
