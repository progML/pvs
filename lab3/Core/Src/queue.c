
#include "queue.h"

void queue_init(struct queue* queue) {
	queue->capacity = QUEUE_LEN;
	//queue->data = { 0, };

	queue->size = 0;
	queue->front = 0;
	queue->rear = queue->capacity - 1;
}

void queue_enqueue(struct queue* queue, QUEUE_ITEM item) {
	if (queue->size == queue->capacity) {
		queue_dequeue(queue);
	}
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->data[queue->rear] = item;
	queue->size++;
}

QUEUE_ITEM queue_dequeue(struct queue* queue) {
	if (queue->size == 0) {
		return 0;
	}
	QUEUE_ITEM item = queue->data[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size--;
	return item;
}
