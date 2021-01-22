#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int main()
{
	int sd;
	struct sockaddr_in addr;

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(sd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

	if(send(sd, "TCP TEST COMMAND", 16, 0) < 0) {
		perror("send");
		return -1;
	}

	close(sd);

	return 0;
}
