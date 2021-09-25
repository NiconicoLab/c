#include <stdio.h>

typedef struct {
	unsigned char sample1;
	unsigned char sample2;
	unsigned char sample3;
	unsigned char sample4;
	unsigned char sample5;
	unsigned char sample6;
	unsigned char sample7;
	unsigned char sample8;
	unsigned char sample9;
}FORMAT1;

typedef struct {
	unsigned char data1;
	unsigned char data2;
	unsigned char data3;
	unsigned char data4;
	unsigned char data5;
	unsigned char data6;
	unsigned char data7;
	unsigned char data8;
	unsigned char data9;
}FORMAT2;

void print1(void* str)
{
	FORMAT1* rcv;
	rcv = (FORMAT1*)str;
	printf("---FORMAT1\n");
	printf("%d\n", rcv->sample1);
	printf("%d\n", rcv->sample2);
	printf("%d\n", rcv->sample3);
	printf("%d\n", rcv->sample4);
	printf("%d\n", rcv->sample5);
	printf("%d\n", rcv->sample6);
	printf("%d\n", rcv->sample7);
	printf("%d\n", rcv->sample8);
	printf("%d\n", rcv->sample9);
}

void print2(void* str)
{
	FORMAT2* rcv;
	rcv = (FORMAT2*)str;
	printf("---FORMAT2\n");
	printf("%d\n", rcv->data1);
	printf("%d\n", rcv->data2);
	printf("%d\n", rcv->data3);
	printf("%d\n", rcv->data4);
	printf("%d\n", rcv->data5);
	printf("%d\n", rcv->data6);
	printf("%d\n", rcv->data7);
	printf("%d\n", rcv->data8);
	printf("%d\n", rcv->data9);
}

void convert(void* str)
{
	FORMAT1* rcv;
	rcv = (FORMAT1*)str;
	rcv->sample1 += 10;
	rcv->sample2 += 10;
	rcv->sample3 += 10;
	rcv->sample4 += 10;
	rcv->sample5 += 10;
	rcv->sample6 += 10;
	rcv->sample7 += 10;
	rcv->sample8 += 10;
	rcv->sample9 += 10;
}

int main(int argc, char *argv[])
{
	unsigned char str[10];
	for(int i = 0; i < 10; i++) {
		str[i] = i;
	}

	print1((void*)str);
	convert((void*)str);
	print2((void*)str);

	return 0;
}
