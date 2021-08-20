#include <stdio.h>
#include "library1.h"

// UnixやLinuxのC言語で共有ライブラリ(.so)を作成

int library_func(int i)
{
	printf("call library func\n");
	return (i + 1);
}
