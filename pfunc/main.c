#include <stdio.h>

int add(int a, int b)
{
	return (a+b);
}

int minus(int a, int b)
{
	return (a-b);
}

int main(void)
{
	int (*pfunc)(int, int);
	printf("%d\n", add(1, 10));

	pfunc = add;
	printf("%d\n", pfunc(1, 10));

	printf("%d\n", minus(6, 3));

	pfunc = minus;
	printf("%d\n", minus(6, 3));

	return 0;
}
