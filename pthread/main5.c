#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // usleep

void* thread1(void *pParam);

int main(int argc, char *argv[])
{
	pthread_t tid1; // スレッド識別変数

	// スレッド生成
	pthread_create(&tid1, NULL, thread1, NULL);

	// スレッド終了待ち
	pthread_join(tid1, NULL);

	printf("finish main program\n");

	return 0;
}

void* thread1(void *pParam)
{
	for(int i = 0; i < 100; i++)
	{
		printf("%d\n", i);
		usleep(100000); // 100ms
	}
	pthread_exit(NULL);
}
