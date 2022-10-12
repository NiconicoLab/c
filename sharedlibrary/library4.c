#include <stdio.h>
#include "library3.h"
#include "library4.h"

// UnixやLinuxのC言語で共有ライブラリ(.so)を作成

void wrapper_library_call(void)
{
	printf("wrapper_library_call : ");
	library_call();
	return;
}

