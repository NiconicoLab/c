#include <stdio.h>

#define RET_OK 1
#define RET_NG 0

#define MAX_STACK_SIZE  20 //  配列の最大の大きさ 
typedef struct {
	int array[MAX_STACK_SIZE]; // データを格納する配列
	unsigned int pos; //  現在の位置
} STACK_BUFF;

void init_stack(STACK_BUFF* stack)
{
	for(int i = 0; i < MAX_STACK_SIZE; i++)
	{
		stack->array[i] = 0;
	}
	stack->pos = 0;
}

int push(STACK_BUFF* stack, int val)
{
	int ret = RET_NG;

	// 配列に空き容量がある場合は格納
	if(stack->pos < MAX_STACK_SIZE)
	{
		stack->array[stack->pos] = val;
		stack->pos++;
		ret = RET_OK;
		printf("push : %d\n", val);
	}

	return ret;
}

int pop(STACK_BUFF* stack, int* val)
{
	int ret = RET_NG;

	// 格納されたデータがある場合
	if(stack->pos > 0)
	{
		stack->pos--;
		*val = stack->array[stack->pos];
		ret = RET_OK;
	}

	return ret;
}

int main(int argc, char *argv[])
{
	STACK_BUFF stack;

	init_stack(&stack);

	for(int i = 0; i < 10; i++)
	{
		push(&stack, i);
	}

	int val;
	while(pop(&stack, &val))
	{
		printf("pop : %d\n", val);
	}
	
	return 0;
}

