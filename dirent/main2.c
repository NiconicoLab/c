#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ARRAY_NUM 100
#define MAX_CREATE_FILE_NUM 5
#define SERATH_PATH "./"
#define FIX_NAME "_aaa.txt"
#define DIGIT 3
#define BACKUP_NAME ".bak"

int get_file(char *fname_create, char *fname_delete)
{
	DIR *dir = opendir(SERATH_PATH);
	struct dirent *dp;

	unsigned int cnt = 0;

	printf("---------Hit File List---------\n");
	int number[ARRAY_NUM];
	char *e;
	int len = strlen(FIX_NAME);
	int len2 = strlen(BACKUP_NAME);
	bool flag = false;
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir))
	{
		// printf(" -> %p %s\n", dp->d_name, dp->d_name); // debug
#if 1
		if(0 == memcmp(&dp->d_name[DIGIT+1], FIX_NAME, len))
		{
#else
		char *found = strstr(dp->d_name, FIX_NAME);
		if(found)
		{
#endif
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
		return -1;
	}
	if(true == flag)
	{
		sprintf(fname_delete, "%04d%s%s", number[cnt-1], FIX_NAME, BACKUP_NAME);
		sprintf(fname_create, "%04d%s", number[cnt-1], FIX_NAME);
		printf("interrupt delete %s : create %s\n", fname_delete, fname_create);
		return 2;
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
			printf("delete %04d_aaa.txt : create %04d_aaa.txt\n", number[total-over], number[total-over-1]+1);
			sprintf(fname_delete, "%04d%s", number[total-over], FIX_NAME);
			sprintf(fname_create, "%04d%s", number[total-over-1]+1, FIX_NAME);
		}
		else {
		}
	}
	else {
		printf("delete %04d%s : create %04d%s\n", number[0], FIX_NAME, number[total-1]+1, FIX_NAME);
		sprintf(fname_delete, "%04d%s", number[0], FIX_NAME);
		sprintf(fname_create, "%04d%s", number[total-1]+1, FIX_NAME);
	}

	if(total >= MAX_CREATE_FILE_NUM)
	{
		// printf("%d\n", total);
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char fname_create[256];
	char fname_delete[256];

	bool delete_flag = false;

	int ret = get_file(fname_create, fname_delete); 
	if(-1 == ret)
	{
		sprintf(fname_create, "%04d%s", 0, FIX_NAME);
	}
	else if(1 == ret)
	{
		delete_flag = true;
		// printf("delete %s : create %s\n", fname_delete, fname_create);
	}
	else if(2 == ret)
	{
		delete_flag = true;
	}
	else // if(0 == ret)
	{
		// printf("delete %s : create %s\n", fname_delete, fname_create);
	}

	printf("---------Main program---------\n");
	printf("create %s", fname_create);
	if(true == delete_flag)
	{
		printf(" : delete %s", fname_delete);
	}
	printf("\n");

	return 0;
}
