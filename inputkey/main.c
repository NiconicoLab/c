#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit(void);

int main(int argc, char *argv[])
{
	bool loop = true;
	sleep(1);

	while(loop)
	{
		if (kbhit())
		{
			switch(getchar()) {
			case 'Q':
			case 'q':
				printf("\nexit\n");
				loop = false;
				break;
			default:
				break;
			}
		}
	}

	return 0;
}

int kbhit(void)
{
	struct termios old_fd, new_fd;
	int ret = 0;
	
	tcgetattr(STDIN_FILENO, &old_fd);
	new_fd = old_fd;
	new_fd.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_fd);
	int old = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, old | O_NONBLOCK);	
	int c = getchar();	
	tcsetattr(STDIN_FILENO, TCSANOW, &old_fd);
	fcntl(STDIN_FILENO, F_SETFL, old);
	
	if (c != EOF)
	{
		ungetc(c, stdin);
		ret = 1;
	}
	
	return ret;
}

