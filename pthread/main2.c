#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // usleep

void* thread1(void *pParam);
void* thread2(void *pParam);

sem_t sem; // セマフォ
bool thread_active_flag;

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2; // スレッド識別変数
	thread_active_flag = true;

	// 第2引数が0以外であればプロセス間で共有可能(0の場合はプロセス内のスレッド間の共有), 第3引数がセマフォの初期値
#if 1
	sem_init(&sem, 0, 0); // ここでセマフォの初期値を1にしておき，先に立ち上がるスレッドに依存せず，待ち状態にさせる
#else // 0以外にしたい場合
	sem_init(&sem, 0, 1);
	sem_post(&sem); sem に 1 加算
#endif

	// スレッド生成
	pthread_create(&tid1, NULL, thread1, NULL);
	pthread_create(&tid2, NULL, thread2, NULL);

	while(thread_active_flag)
	{
		char c = fgetc(stdin);
		printf("key command is %c\n", c);
		if( (c == 'Q') || (c == 'q') )
		{
			// スレッド終了フラグを設定
			thread_active_flag = false;
		}
	}

	// スレッド終了待ち
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// セマフォ削除
	sem_destroy(sem);

	return 0;
}

void* thread1(void *pParam)
{
	printf("%s create\n", __func__);
	sem_wait(&sem); // sem > 0 なら sem から 1 減算します。sem が 0 なら呼び出したスレッドはブロックされる
	printf("%s start\n", __func__);
	while(thread_active_flag)
	{
		usleep(1000);
	}
	printf("%s exit\n", __func__);
	pthread_exit(NULL);
}

void* thread2(void *pParam)
{
	printf("%s create\n", __func__);
	sem_wait(&sem); // sem > 0 なら sem から 1 減算します。sem が 0 なら呼び出したスレッドはブロックされる
	printf("%s start\n", __func__);
	while(thread_active_flag)
	{
		usleep(1000);
	}
	printf("%s exit\n", __func__);
	pthread_exit(NULL);
}

