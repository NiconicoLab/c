#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	DIR *dir = opendir("./");
	struct dirent *dp;

	unsigned int cnt = 1;

	printf("---------Folder File List---------\n");
	for(dp = readdir(dir); dp != NULL; dp = readdir(dir))
	{
		printf("%d : %s\n", cnt, dp->d_name);
		cnt++;
	}
	closedir(dir);

	return 0;
}
