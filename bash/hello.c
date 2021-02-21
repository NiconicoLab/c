#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc != 1) {
		printf("Usage$%s\n", argv[0]);
		return 1;
	}

	printf("Hello world\n");

	return 0;
}
