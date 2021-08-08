#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat file;
	if(stat("../bash/hello", &file) == 0) {
		printf("exist\n");
	}
	else {
		goto error;
	}

	errno = 0;

	// execは現在のプロセスを指定したプログラムに置き換えて実行
	// 呼び出し元へ制御が戻ることはない
	// 第1引数は実行されるプログラムのパス
	// 第2引数以降はコマンドライン引数を渡すものと同じ
	// 第2引数に関してexeclは可変長の引数、execvは引数として配列が渡さ，
	// 引数リストの最後はNULLでなければならず、(char *)NULLとなる
	execl("../bash/hello", "../bash/hello", NULL);
	
	if(errno != 0) {
		perror(strerror(errno));
		return -1;
	}

error:
	printf("not exist\n");
	
	return 0;
}

