#include <stdio.h>
#include "library1.h"

// UnixやLinuxのC言語で共有ライブラリ(.so)を作成

int library2_func(int i)
{
	printf("call library2 func\n");
	return (i + 1);
}
