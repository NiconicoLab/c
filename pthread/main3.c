#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
void* sub_thread(void *pParam);
int mode;

#if 0
- support cond_wait mode
	sub_hreadを生成しmain処理はpthread_cond_waitにより
	sub_threadからのシグナルを待つ
- not support cond_wait mode
	sub_threadが生成されている間にmain処理は進み，
	pthread_joinでsub_threadが終了するまで待つ
#endif

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage $%s option\n \
option:0->not support cond_wait\n \
option:1->support cond_wait\n", argv[0]);
		return 1;
	}

	mode = atoi(argv[1]);
	if(mode)
	{
		printf("support cond_wait mode (%d)\n", mode);
	}
	else
	{
		printf("not support cond_wait mode (%d)\n", mode);
	}

	pthread_t thread_id = 0;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	if(pthread_create(&thread_id, NULL, sub_thread, NULL) < 0)
	{
		printf("error pthread_create\n");
		return 1;
	}

	if(mode)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
//		pthread_cond_signal(&cond); // こちらのパターンではシグナルを取り溢す
		pthread_mutex_unlock(&mutex);
	}

	printf("main process start\n");

	if(pthread_join(thread_id, NULL) < 0)
	{
		printf("errror pthread_join\n");
		return 1;
	}

	printf("main process end\n");
	return 0;
}

void* sub_thread(void *pParam)
{
	printf("sub_thread start\n");

	if(mode)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_signal(&cond);
//		pthread_cond_wait(&cond, &mutex); // こちらのパターンではシグナルを取り溢す
		pthread_mutex_unlock(&mutex);
	}

	printf("sub_thread end\n");

	pthread_exit(NULL);
}
