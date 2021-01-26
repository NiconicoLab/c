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

#define TIMEOUT_ENABLE // タイムアウト付き

int main()
{
	int sock;
	struct sockaddr_in addr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_len = sizeof(addr);

	bind(sock, (struct sockaddr *)&addr, sizeof(addr));

#ifdef TIMEOUT_ENABLE
	fd_set fds, rfds;
	FD_ZERO(&rfds);
	FD_SET(sock, &rfds);

	struct timeval tv;
	tv.tv_sec  = 5;
	tv.tv_usec = 0;
#endif

	char buf[2048];
	int cnt = 0;
	while(cnt < 5)
	{
#ifdef TIMEOUT_ENABLE
		memcpy(&fds, &rfds, sizeof(fd_set)); // selectが毎回上書きするため初期化
		int judge = select(sock+1, &fds, NULL, NULL, &tv);
		if(judge < 0) {
			printf("error select\n");
		}
		else if(judge == 0) {
			printf("timeout\n");
			cnt++;
			continue;
		}

		if(FD_ISSET(sock, &fds)) // データがある場合
		{
#endif
			memset(buf, 0, sizeof(buf));
			recv(sock, buf, sizeof(buf), 0);
			printf("%s\n", buf);
			cnt++;
#ifdef TIMEOUT_ENABLE
		}
#endif
	}
	close(sock);

	return 0;
}

