#include <stdio.h>

#define RET_OK 1
#define RET_NG 0

#define MAX_QUEUE_SIZE 5 //  配列の最大の大きさ 
typedef struct {
	int array[MAX_QUEUE_SIZE]; // データを格納する配列
	unsigned int head;
        unsigned int tail;
} QUEUE_BUF;

void init_queue(QUEUE_BUF* queue)
{
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		queue->array[i] = 0;
	}
	queue->head = 0;
	queue->tail = 0;
}

int enqueue(QUEUE_BUF* queue, int val)
{
	int ret = RET_NG;

	// 配列に空き容量がある場合は格納
	if(queue->tail < MAX_QUEUE_SIZE)
	{
		queue->array[queue->tail] = val;
		queue->tail++;
		ret = RET_OK;
		printf("enqueue : %d\n", val);
	}

	return ret;
}

int dequeue(QUEUE_BUF* queue, int* val)
{
	int ret = RET_NG;

	// 格納されたデータがある場合
	if(queue->head != queue->tail)
	{
		*val = queue->array[queue->head];
		queue->head++;
		ret = RET_OK;
	}

	return ret;
}

int main(int argc, char *argv[])
{
	QUEUE_BUF queue;

	init_queue(&queue);

	for(int i = 0; i < 5; i++)
	{
		enqueue(&queue, i);
	}

	int val;
	for(int i = 0; i < 5; i++)
	{
		dequeue(&queue, &val);
		printf("dequeue : %d\n", val);
	}
	
	return 0;
}

