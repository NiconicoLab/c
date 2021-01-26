#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

#define TIMEOUT_ENABLE // タイムアウト付き

int main()
{
	int sd;
	int acc_sd;
	struct sockaddr_in addr;
	char buf[128];
	
	socklen_t sin_size = sizeof(struct sockaddr_in);
	struct sockaddr_in from_addr;

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	addr.sin_addr.s_addr = INADDR_ANY;

#ifdef TIMEOUT_ENABLE
	fd_set fds, rfds;
	FD_ZERO(&rfds);
	FD_SET(sd, &rfds);

	struct timeval tv;
	tv.tv_sec  = 5;
	tv.tv_usec = 0;
#endif

	if(bind(sd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("bind");
		return -1;
	}

	// パケット受信待ち状態(待ち受けキュー10に設定)
	if(listen(sd, 10) < 0) {
		perror("listen");
		return -1;
	}

	unsigned char cnt = 0;
	while(cnt < 5){		
#ifdef TIMEOUT_ENABLE
		memcpy(&fds, &rfds, sizeof(fd_set)); // selectが毎回上書きするため初期化
		int judge = select(sd+1, &fds, NULL, NULL, &tv);
		if(judge < 0) {
			printf("error select\n");
		}
		else if(judge == 0) {
			printf("timeout\n");
			cnt++;
			continue;
		}
#endif

		// クライアントからコネクト要求が来るまで停止し，サーバはacc_sdを使ってパケットの送受信
		if((acc_sd = accept(sd, (struct sockaddr *)&from_addr, &sin_size)) < 0) {
			perror("accept");
			return -1;
		}
		
#ifdef TIMEOUT_ENABLE
		if(FD_ISSET(sd, &fds)) // データがある場合
		{
#endif
		
			int num = recv(acc_sd, buf, sizeof(buf), 0);
			if(num < 0) {
				perror("recv");
				return -1;
			}
		
			for(int i = 0; i < num; i++) {
				printf("%c", buf[i]);
			}
			printf("\n");
			cnt++;
#ifdef TIMEOUT_ENABLE
		}
#endif
	}

	// パケット送受信用ソケットのクローズ
	close(acc_sd);

	// 接続要求待ち受け用ソケットをクローズ
	close(sd);

	return 0;
}
