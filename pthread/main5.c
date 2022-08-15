#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // usleep

void* thread1(void *pParam);

int main(int argc, char *argv[])
{
	pthread_t tid1; // スレッド識別変数

	// スレッド生成
	pthread_create(&tid1, NULL, thread1, NULL);

	for(int i = 0; i < 5; i++)
	{
		fprintf(stderr, "main thread : %d\n", i);
		usleep(500000);
	}

	// スレッド終了待ち
	pthread_join(tid1, NULL);

	printf("finish main program\n");

	return 0;
}

void* thread1(void *pParam)
{
	for(int i = 0; i < 10; i++)
	{
		fprintf(stderr, "child thread : %d\n", i);
		usleep(1000000); // 1000ms
	}
	pthread_exit(NULL);
	return NULL; // ここには到達しない
}
