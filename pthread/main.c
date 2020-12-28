#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h> // usleep

#define MUTEX_ON // 排他制御有効

void* thread1(void *pParam);
void* thread2(void *pParam);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // mutex生成と初期化

int global_cnt;
bool thread_active_flag;

int main(int argc, char *argv[])
{
	pthread_t tid1, tid2; // スレッド識別変数
	thread_active_flag = true;
	
	// mutexの初期化
	pthread_mutex_init(&mutex, NULL);
	
	// スレッド生成
	pthread_create(&tid1, NULL, thread1, NULL);
	pthread_create(&tid2, NULL, thread2, NULL);

	while(thread_active_flag)
	{
		char c = fgetc(stdin);
		printf("key command is entered\n");
		if( (c == 'Q') || (c == 'q') )
		{
			// スレッド終了フラグを設定
			thread_active_flag = false;
		}
	}

	// スレッド終了待ち
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	// mutex削除
	pthread_mutex_destroy(&mutex); 

	return 0;
}

void* thread1(void *pParam)
{
	int local_cnt;
	while(thread_active_flag)
	{
#ifdef MUTEX_ON // 排他制御
		pthread_mutex_lock(&mutex); // 排他制御開始
#endif
		local_cnt = global_cnt;
		local_cnt++;
		global_cnt = local_cnt;
#ifdef MUTEX_ON // 排他制御
		pthread_mutex_unlock(&mutex); // 排他制御終了
#endif
		printf("%s : %d\n", __func__, local_cnt);
	}
	printf("%s exit\n", __func__);
	pthread_exit(NULL);
}

void* thread2(void *pParam)
{
	int local_cnt;
	while(thread_active_flag)
	{
#ifdef MUTEX_ON // 排他制御
		pthread_mutex_lock(&mutex); // 排他制御開始
#endif
		local_cnt = global_cnt;
		local_cnt++;
		usleep(10); // 10us sleep
		global_cnt = local_cnt;
#ifdef MUTEX_ON // 排他制御
		pthread_mutex_unlock(&mutex); // 排他制御終了
#endif
		printf("%s : %d\n", __func__, local_cnt);
	}
	printf("%s exit\n", __func__);
	pthread_exit(NULL);
}

