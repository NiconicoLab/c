#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define THREADS_NUM 5
int g_cnt;
pthread_mutex_t mutex, mutex_start;
pthread_cond_t cond_start;
pthread_t thread_id[THREADS_NUM];
void* thread(void *param);

int main(int argc, char* argv[])
{
	// mutexの値の初期化
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&mutex_start, NULL);
	pthread_cond_init(&cond_start, NULL);

	// 5個のスレット生成
	for(int i = 0; i < THREADS_NUM; i++) {
		if(pthread_create(&thread_id[i], NULL, thread, (void *)&thread_id[i]) < 0) {
			perror("pthread_create error");
			exit(1);
		}
	}

	// 5秒後にpthread_cond_broadcast()で全スレッドに対して通知
	sleep(5);
	pthread_cond_broadcast(&cond_start);

	// 生成した5個のスレッドの終了を待つ
	for(int i = 0; i < THREADS_NUM; i++) {
		if(pthread_join(thread_id[i], NULL) < 0) {
			perror("pthread_join error");
			exit(1);
		}
	}
	printf("g_cnt = %d\n", g_cnt);
	return 0;
}

void* thread(void *param)
{
	pthread_t *pthread_id;

	pthread_id = (pthread_t *)param;
	printf("thread[%p] start\n", *pthread_id);
	pthread_mutex_lock(&mutex_start);
	pthread_cond_wait(&cond_start, &mutex_start);
	pthread_mutex_unlock(&mutex_start);

	/* グローバル変数を排他制御しながら10までインクリメント */
	for(int i = 0; i < 10; i++) {
		pthread_mutex_lock(&mutex);
		g_cnt++;
		pthread_mutex_unlock(&mutex);
	}
	printf("thread[%p] end\n", pthread_self());
	pthread_exit(NULL);
}

