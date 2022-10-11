#include <stdio.h>
#include "library3.h"
#include <stdbool.h>

// UnixやLinuxのC言語で共有ライブラリ(.so)を作成

static int g_flag = false;

static void update_flag(void)
{
	if(g_flag == false)
	{
		printf("flg = false\n");
		g_flag = true;
	}
	else
	{
		printf("flg = true\n");
	}
}

void library_call(void)
{
	printf("library_call : ");
	update_flag();
	return;
}
