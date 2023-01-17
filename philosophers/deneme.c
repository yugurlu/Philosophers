
#include "philo.h"
#include <time.h>

pthread_mutex_t mutex, mutex2;
int variable = 0;
int counter = 0;

void *thread1_func(void *arg)
{
    while (1) {
        pthread_mutex_lock(&mutex2);
        counter++;
        printf("Thread 1: Counter value: %d\n", counter);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void *thread2_func(void *arg)
{
    while (1) {
        pthread_mutex_lock(&mutex2);
        counter--;
        printf("Thread 2: Counter value: %d\n", counter);
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

void	*function(void *arg)
{
	int i;

	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
        variable++;
       	pthread_mutex_unlock(&mutex);
		i++;
	}
	return (NULL);
}

void 	*deneme(void *arg)
{
	printf("işlem parçacığı başladı...\n");
	usleep(1000000);
	return (NULL);
}

void	*routine(void *arg)
{
	(void)arg;
	return (NULL);
}

int main()
{
	//thread creat ve mutex deneme
	pthread_t thread;
	int err = pthread_create(&thread, NULL, &routine, NULL);
	if (err != 0)
	{
		printf("Can't create thread!\n");
		return -1;
	}
	printf("Thread created! ID = %p\n", thread);
	//pthread_detach(thread); -> işlem parçacığı sonlandırmak için.
	err = pthread_join(thread, NULL);
	if (err != 0)
	{
		printf("Can't join thread!\n");
		return -1;
	}
	printf("Thread joined! ID = %p\n", thread);
	printf("----------------------------------------\n");

	pthread_mutex_t mutex1;
	err = pthread_mutex_init(&mutex1, NULL);
	if (err != 0)
	{
		printf("Can't create mutex!\n");
		return -1;
	}
	printf("Mutex created!\n");
	err = pthread_mutex_lock(&mutex1);
	if (err != 0)
	{
		printf("Can't lock mutex!\n");
		return -1;
	}
	printf("Mutex locked!\n");
	printf("----------------------------------------\n");

	//--------------------------------------------------------------------------------------------//

	//örnek program
	pthread_t thread1;

	pthread_create(&thread1, NULL, &deneme, NULL);
	printf("işlem parçacığı oluşturuldu... ID = %p\n", thread1);
	pthread_join(thread1, NULL);
	pthread_detach(thread1);
	printf("işlem parçacığı sonlandırıldı...\n");
	printf("----------------------------------------\n");

	//örnek program2
	pthread_t thread2;
	pthread_t thread3;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread2, NULL, function, NULL);
	pthread_create(&thread3, NULL, function, NULL);

	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	printf("Variable = %d\n", variable);
	pthread_mutex_destroy(&mutex);
	printf("----------------------------------------\n");

	//--------------------------------------------------------------------------------------------//

	/*while(1) döngüsü ile sonsuza kadar çalışıcak iki fonksiyon aynı anda çalıştırılabilir ???
	-çoklu işlemcilerin avantajları*/

	pthread_t thread4, thread5;

	pthread_mutex_init(&mutex2, NULL);

    pthread_create(&thread4, NULL, thread1_func, NULL);
    pthread_create(&thread5, NULL, thread2_func, NULL);

    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);

    pthread_mutex_destroy(&mutex2);

	return 0;
}
