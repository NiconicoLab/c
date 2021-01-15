#include <stdio.h>

#define RET_OK 1
#define RET_NG 0

#define MAX_QUEUE_SIZE 5 //  配列の最大の大きさ 
typedef struct {
	int array[MAX_QUEUE_SIZE]; // データを格納する配列
	unsigned int head;
        unsigned int tail;
	unsigned int num;
} QUEUE_BUF;

void init_queue(QUEUE_BUF* queue)
{
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		queue->array[i] = 0;
	}
	queue->head = 0;
	queue->tail = 0;
	queue->num  = 0;
}

int enqueue(QUEUE_BUF* queue, int val)
{
	int ret = RET_NG;

	// 配列に空き容量がある場合は格納
	if(queue->num < MAX_QUEUE_SIZE)
	{
		if(queue->tail == MAX_QUEUE_SIZE)
		{
			queue->tail = 0;
		}
		queue->array[queue->tail] = val;
		queue->tail++;
		queue->num++;
		ret = RET_OK;
		printf("enqueue : %d\n", val);
	}

	return ret;
}

int dequeue(QUEUE_BUF* queue, int* val)
{
	int ret = RET_NG;

	// 格納されたデータがある場合
	if(queue->num > 0)
	{
		if(queue->head == MAX_QUEUE_SIZE)
		{
			queue->head = 0;
		}
		*val = queue->array[queue->head];
		queue->head++;
		queue->num--;
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
		if(dequeue(&queue, &val) == RET_OK)
		{
			printf("dequeue : %d\n", val);
		}
	}

	for(int i = 0; i < 1; i++)
	{
		enqueue(&queue, i+10);
	}

	for(int i = 0; i < 1; i++)
	{
		if(dequeue(&queue, &val) == RET_OK)
		{
			printf("dequeue : %d\n", val);
		}
	}

	for(int i = 0; i < 5; i++)
	{
		enqueue(&queue, i+20);
	}

	for(int i = 0; i < 5; i++)
	{
		if(dequeue(&queue, &val) == RET_OK)
		{
			printf("dequeue : %d\n", val);
		}
	}
	
	return 0;
}

