#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_NUM 100
#define MAX_CREATE_FILE_NUM 5
#define SERATH_PATH "./"
#define DIGIT 3
#define BACKUP_NAME ".bak"

typedef enum {
	RET_ERROR = 1,
	RET_REPLACE,
	RET_ONLY_CRE,
	RET_CRE_DEL
} ERet;

ERet get_file(char *fname_create, char *fname_delete, const char* fix_name)
{
	DIR *dir = opendir(SERATH_PATH);
	struct dirent *dp;

	unsigned int cnt = 0;

	printf("---------Hit File List---------\n");
	int number[ARRAY_NUM];
	char *e;
	int len = strlen(fix_name);
	int len2 = strlen(BACKUP_NAME);
	bool flag = false;
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir))
	{
		// printf(" -> %p %s\n", dp->d_name, dp->d_name); // debug
		if(0 == memcmp(&dp->d_name[DIGIT+1], fix_name, len))
		{
			printf("%d : %s :", cnt, dp->d_name);
			dp->d_name[DIGIT+1] = '\0'; // glibcではd_name[256]で定義
			number[cnt] = strtol(dp->d_name, &e, 10);
			printf("%d\n", number[cnt]);
			if(*e != '\0')
			{
				printf("fail (%d)\n", number[cnt]);
				continue;
			}
			if('\0' == (dp->d_name[DIGIT+len+1]))
			{
				cnt++;
			}
			else if((0 == memcmp(&dp->d_name[DIGIT+len+1], BACKUP_NAME, len2)) && ('\0' == (dp->d_name[DIGIT+len+len2+1])))
			{
				cnt++;
				flag = true;
				printf("hit!!!\n");
				break;
			}
			else
			{
			}
		}
	}
	closedir(dir);

	if(0 == cnt)
	{
		return RET_ERROR;
	}
	if(true == flag)
	{
		sprintf(fname_delete, "%04d%s%s", number[cnt-1], fix_name, BACKUP_NAME);
		sprintf(fname_create, "%04d%s", number[cnt-1], fix_name);
		printf("interrupt delete %s : create %s\n", fname_delete, fname_create);
		return RET_REPLACE;
	}

	int sum, i, j;
	int total = cnt;
	for(i = 0; i < total; ++i)
	{
		for(j = i+1; j < total; ++j)
		{
			if(number[i] > number[j])
			{
				sum = number[i];
				number[i] = number[j];
				number[j] = sum;
			}
		}
	}

	printf("---------File Number (after sort)---------\n");
	for (int i = 0; i < total; i++) {
		printf("%d\n", number[i]);
	}

	printf("---------Judge fname---------\n");
	int over = 0;
	if(999 == number[total-1]) {
		for (int i = total-1; i >= 0; i--) {
			// printf("%d\n", number[i]);
			if(900 < number[i]) {
				over++;
			}
		}
		// printf("over = %d\n", over);
		if(over) {
			if((999 == number[total-1]) && ((total == over))) {
				// printf("all over !!!\n");
				printf("delete %04d_aaa.txt : create %04d_aaa.txt\n", number[total-over], 1);
				sprintf(fname_delete, "%04d%s", number[total-over], fix_name);
				sprintf(fname_create, "%04d%s", 1, fix_name);
			}
			else {
				printf("delete %04d_aaa.txt : create %04d_aaa.txt\n", number[total-over], number[total-over-1]+1);
				sprintf(fname_delete, "%04d%s", number[total-over], fix_name);
				sprintf(fname_create, "%04d%s", number[total-over-1]+1, fix_name);
			}
		}
		else {
		}
	}
	else {
		printf("delete %04d%s : create %04d%s\n", number[0], fix_name, number[total-1]+1, fix_name);
		sprintf(fname_delete, "%04d%s", number[0], fix_name);
		sprintf(fname_create, "%04d%s", number[total-1]+1, fix_name);
	}

	if(total >= MAX_CREATE_FILE_NUM)
	{
		// printf("%d\n", total);
		return RET_CRE_DEL;
	}
	return RET_ONLY_CRE;
}

void func1(void)
{
	printf("---------Pattern A---------\n");
	char fname_create[256];
	char fname_delete[256];
	bool delete_flag = false;
	char *fix_name = "_aaa.txt";

	ERet ret = get_file(fname_create, fname_delete, fix_name);
	switch(ret) {
	case RET_ERROR:
		sprintf(fname_create, "%04d%s", 1, fix_name);
		break;
	case RET_REPLACE:
		delete_flag = true;
		break;
	case RET_ONLY_CRE:
		// printf("delete %s : create %s\n", fname_delete, fname_create);
		break;
	case RET_CRE_DEL:
		delete_flag = true;
		// printf("delete %s : create %s\n", fname_delete, fname_create);
		break;
	default:
		break;
	}

	printf("---------func1 program---------\n");
	printf("create %s", fname_create);
	if(true == delete_flag)
	{
		printf(" : delete %s", fname_delete);
	}
	printf("\n");
}

void func2(void)
{
	printf("---------Pattern B---------\n");
	char fname_create[256];
	char fname_delete[256];
	bool delete_flag = false;
	char *fix_name = "_aab.txt";

	ERet ret = get_file(fname_create, fname_delete, fix_name);
	switch(ret) {
	case RET_ERROR:
		sprintf(fname_create, "%04d%s", 1, fix_name);
		break;
	case RET_REPLACE:
		delete_flag = true;
		break;
	case RET_ONLY_CRE:
		// printf("delete %s : create %s\n", fname_delete, fname_create);
		break;
	case RET_CRE_DEL:
		delete_flag = true;
		// printf("delete %s : create %s\n", fname_delete, fname_create);
		break;
	default:
		break;
	}

	printf("---------func2 program---------\n");
	printf("create %s", fname_create);
	if(true == delete_flag)
	{
		printf(" : delete %s", fname_delete);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	func1();
	func2();
	return 0;
}
