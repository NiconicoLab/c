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
	execl("../bash/hello", "../bash/hello", NULL);
	
	if(errno != 0) {
		perror(strerror(errno));
		return -1;
	}

error:
	printf("not exist\n");
	
	return 0;
}

