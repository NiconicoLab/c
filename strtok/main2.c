#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITER ","
#define SPLIT_NUM 5

void split_str(char *str)
{
	int array[SPLIT_NUM];
	
	int cnt = 0;
	char* p = strtok(str, DELIMITER);
	while ((p != NULL) && (cnt < SPLIT_NUM)) {
		array[cnt] = strtol(p, NULL, 16);
		p = strtok(NULL, DELIMITER); // 第1引数がNULLの時は前回の値の続きからになる
		cnt++;
	}

	printf("num:%d| ", cnt);
	for(int i = 0; i < cnt; i++) {
		printf("%X ", array[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	char str[128];
	FILE *fp = fopen("../../data/sample2.txt", "r");
	while(fgets(str, 128, fp) != NULL) {
		int len = strlen(str);
		if(str[len-2] == '\r') { // Windowsの場合はCRLF
			str[len-2] = '\0';
		}
		else{
			str[len-1] = '\0';
		}
		split_str(str);
	}
	fclose(fp);

	return 0;
}
