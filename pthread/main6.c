#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

static pthread_once_t mutex_once = PTHREAD_ONCE_INIT;

static void once_func1(void)
{
	printf("%ld call once_func1\n", (unsigned long int)pthread_self());
}

static void wrapper_func1(const char* str)
{
	fprintf(stderr, "%ld(%s) call\n", (unsigned long int)pthread_self(), str);
	int ret;
	ret = pthread_once( &mutex_once, once_func1 );
	fprintf(stderr, "%ld ret=%d\n", (unsigned long int)pthread_self(), ret);
	return;
}

static void once_func2(void)
{
	printf("%ld call once_func2\n", (unsigned long int)pthread_self());
}

static void wrapper_func2(const char* str)
{
	fprintf(stderr, "%ld(%s) call\n", (unsigned long int)pthread_self(), str);
	int ret;
	ret = pthread_once( &mutex_once, once_func2 );
	fprintf(stderr, "%ld ret=%d\n", (unsigned long int)pthread_self(), ret);
	return;
}

void * thread1( void * arg )
{
	wrapper_func1("thread1");
	return 0;
}
void * thread2( void * arg )
{
	wrapper_func1("thread2");
	return 0;
}
void * thread3( void * arg )
{
	wrapper_func2("thread3");
	return 0;
}
void * thread4( void * arg )
{
	wrapper_func2("thread4");
	return 0;
}

int main(void)
{
        int i = 0, j = 0;
        int ret;
        pthread_t th[4];
	
        ret = pthread_create(&th[i], NULL, thread1, NULL);
        if (ret != 0)
	{
		fprintf(stderr, "error:pthread_create\n");
                goto out;
        }
	
        ret = pthread_create(&th[++i], NULL, thread2, NULL);
        if (ret != 0)
	{
		fprintf(stderr, "error:pthread_create\n");
                goto out;
        }
	
        ret = pthread_create(&th[++i], NULL, thread3, NULL);
        if (ret != 0)
	{
		fprintf(stderr, "error:pthread_create\n");
                goto out;
        }
	
        ret = pthread_create(&th[++i], NULL, thread4, NULL);
        if (ret != 0)
	{
		fprintf(stderr, "error:pthread_create\n");
                goto out;
        }
	
out:
        while (j < i)
	{
                pthread_join(th[j++], NULL);
	}
	
        return 0;
}

