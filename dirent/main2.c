#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#if 0 // glicbで定義されている構造体
struct dirent {
	ino_t          d_ino;       /* inode 番号 */
	off_t          d_off;       /* オフセットではない; 下記を参照 */
	unsigned short d_reclen;    /* このレコードの長さ */
	unsigned char  d_type;      /* ファイル種別。全ファイルシステム でサポートされているわけではない */
	char           d_name[256]; /* ヌル終端されたファイル名 */
};
#endif

#define MAX_CREATE_FILE_NUM 5
const char* fix_fname = "_aaa.txt";

int get_file(char *fname_create, char *fname_delete)
{
	DIR *dir = opendir("./");
	struct dirent *dp;
	
	unsigned int cnt = 1;

	printf("---------Hit File List---------\n");
	int number[100];
	cnt = 0;
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir))
	{
		char *found = strstr(dp->d_name, fix_fname);
		if(found) {
			printf("%d : %s :", cnt, dp->d_name);
			dp->d_name[4] = '\0';
			number[cnt] = atoi(dp->d_name);
			printf("%d\n", number[cnt]);
			cnt++;
		}
	}
	closedir(dir);

	if(0 == cnt)
	{
		return -1;
	}

	int sum, i, j;
	int total = cnt;
	for(i=0;i<total;++i)
	{
		for(j=i+1;j<total;++j)
		{
			if(number[i]>number[j])
			{
				sum=number[i];
				number[i]=number[j];
				number[j]=sum;
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
			sprintf(fname_delete, "%04d%s", number[total-over], fix_fname);
			sprintf(fname_create, "%04d%s", number[total-over-1]+1, fix_fname);
		}
		else {
		}
	}
	else {
		printf("delete %04d%s : create %04d%s\n", number[0], fix_fname, number[total-1]+1, fix_fname);
		sprintf(fname_delete, "%04d%s", number[0], fix_fname);
		sprintf(fname_create, "%04d%s", number[total-1]+1, fix_fname);
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
	char fname_create[50];
	char fname_delete[50];

	bool create_flag = false;
	bool delete_flag = false;
	
	int ret = get_file(fname_create, fname_delete); 
	if(-1 == ret)
	{
		sprintf(fname_create, "%04d%s", 0, fix_fname);
		delete_flag = false;
		create_flag = true;
	}
	else if(0 == ret)
	{
		delete_flag = false;
		create_flag = true;
		// printf("delete %s : create %s\n", fname_delete, fname_create);
	}
	else // 1 == ret
	{
		delete_flag = true;
		create_flag = true;
		// printf("delete %s : create %s\n", fname_delete, fname_create);
	}

	printf("---------Main program---------\n");
	if(true == create_flag)
	{
		printf("create %s\n", fname_create);
	}
	if(true == delete_flag)
	{
		printf("delete %s\n", fname_delete);
	}

	return 0;
}
