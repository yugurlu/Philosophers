
#include "philo.h"
#define ARRAY_SIZE 10

pthread_mutex_t mutex;
int variable = 0;

int arr[] = {112, 434, 23, -22, 1, 3239, 0, -211, 583, 554};

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

void 	*find_min(void *arg)
{
	int i;

	i = 0;
	while (i < ARRAY_SIZE)
	{
		if(arr[i] < 0)

	}

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
	pthread_t thread2;

	pthread_mutex_init(&mutex, NULL);
	pthread_create(&thread1, NULL, function, NULL);
	pthread_create(&thread2, NULL, function, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Variable = %d\n", variable);
	pthread_mutex_destroy(&mutex);

	//örnek program 2
	pthread_t thread3;
	pthread_t thread4;

	pthread_create(&thread3, NULL, find_min, NULL);
	return 0;
}
