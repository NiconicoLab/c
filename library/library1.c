#include <stdio.h>
#include "library1.h"

int library_func(int i)
{
	printf("call library func\n");
	return (i + 1);
}
