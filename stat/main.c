#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat directory;
	if(stat("log", &directory) != 0)
	{
		printf("\"log\" directory is not exist\n");
		mkdir("log", 0775);
	}
	else
	{
		printf("\"log\" directory is exist\n");	
	}
	
	struct stat file;
	if(stat("log/output.txt", &file) == 0)
	{
		printf("\"log/output.txt\" is exist\n");
	}
	else
	{
		printf("\"log/output.txt\" is not exist\n");
		char fname[15];
		sprintf(fname, "log/output.txt");
		FILE *fo = fopen(fname, "w");
		fprintf(fo, "test\n");
		fclose(fo);
	}	
	
	return 0;
}

