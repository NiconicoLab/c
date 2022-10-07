#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#if 0 // glicbで定義されている構造体
struct dirent {
	ino_t          d_ino;       /* inode 番号 */
	off_t          d_off;       /* オフセットではない; 下記を参照 */
	unsigned short d_reclen;    /* このレコードの長さ */
	unsigned char  d_type;      /* ファイル種別。全ファイルシステム でサポートされているわけではない */
	char           d_name[256]; /* ヌル終端されたファイル名 */
};
#endif

int main(int argc, char *argv[])
{
	DIR *dir = opendir("./");
	struct dirent *dp;

	unsigned int cnt = 1;

	printf("---------Folder File List---------\n");
#if 0
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir))
	{
		printf("%d : %s\n", cnt, dp->d_name);
		cnt++;
	}
	closedir(dir);
#else
	int number[100];
	cnt = 0;
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir))
	{
		char *s = "_aaa.txt";
		// "aaa"という文字列を検索する
		char *found = strstr(dp->d_name, s);
		if(found) {
			printf("%d : %s :", cnt, dp->d_name);
			dp->d_name[4] = '\0';
			number[cnt] = atoi(dp->d_name);
			printf("%d\n", number[cnt]);
			cnt++;
		}
	}
	closedir(dir);
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

	printf("--- sort ---\n");
	for (int i = 0; i < total; i++) {
		printf("%d\n", number[i]);
	}
	printf("---\n");

	printf("--- result ---\n");
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
		}
		else {
		}
	}
	else {
		printf("delete %04d_aaa.txt : create %04d_aaa.txt\n", number[0], number[total-1]+1);
	}
#endif

	return 0;
}
