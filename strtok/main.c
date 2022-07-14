#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER ","
#define SPLIT_NUM 5

int main(int argc, char* argv[])
{
	if(argc < 2) {
		printf("Usage $%s string\n", argv[0]);
		return -1;
	}

	int array[SPLIT_NUM];
	
	int cnt = 0;
	char* p = strtok(argv[1], DELIMITER);
	while ((p != NULL) && (cnt < SPLIT_NUM)) {
		array[cnt] = strtol(p, NULL, 16);
		p = strtok(NULL, DELIMITER); // 第1引数がNULLの時は前回の値の続きからになる
		cnt++;
	}

	printf("split num:%d\n", cnt);
	for(int i = 0; i < cnt; i++) {
		printf("array[%d] = %X\n", i, array[i]);
	}

	return 0;
}
