#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	printf("bash start\n");
	system("bash script.sh");
	printf("bash end\n");
	
	return 0;
}
