#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include<semaphore.h>

#define INCR 1000000
int cnt = 0;
sem_t mutex;

void* Count(void * a){
	int i, tmp;
	for(i = 0; i < INCR; i++){
		sem_wait(&mutex);
		tmp = cnt;
		tmp = tmp+1;
		cnt = tmp;
		sem_post(&mutex);
	}
}



int main(){
	sem_init(&mutex, 0, 1);
	pthread_t thread0, thread1;
	pthread_create(&thread0, NULL, Count , NULL);
	pthread_create(&thread1, NULL, Count , NULL);
	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);
	printf("Count: %d\n", cnt);
	return 0;
	
	
}
