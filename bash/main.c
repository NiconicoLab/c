#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	printf("bash start\n");
	system("bash script.sh");
	printf("bash end\n");

	char program[] = "./hello"; // 実行する別プログラム名
	int result = system(program); // 別プログラムを実行
	if ( result == EXIT_SUCCESS )
	{
		printf("正常に実行できました\n");
	} else
	{
		printf("正常に実行できませんでした\n");
	}

	return 0;
}
