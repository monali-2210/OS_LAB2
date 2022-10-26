#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
sem_t mutex[5];
void* func(void* argument){
    int i = (int)argument;
    if(i%2==1){
        sem_wait(&mutex[i]);
        sem_wait(&mutex[(i+1)%5]);
        printf("NOW PHILOSOPHER %d IS EATING!!!\n",i);
        sem_post(&mutex[(i+1)%5]);
        printf("NOW PHILOSOPHER %d RELEASED FORK!!!\n",i);
        sem_post(&mutex[i]);
        printf("NOW PHILOSOPHER %d IS THINKING!!!\n",i);
    }
    else{
        sem_wait(&mutex[(i+1)%5]);
        sem_wait(&mutex[i]);
        printf("NOW PHILOSOPHER %d IS EATING!!!\n",i);
        sem_post(&mutex[i]);
        printf("NOW PHILOSOPHER %d RELEASED FORK!!!\n",i);
        sem_post(&mutex[(i+1)%5]);
        printf("NOW PHILOSOPHER %d IS THINKING!!!\n",i);    
    }

}

int main(){
    pthread_t threads[5];
    for(int i =0;i<5;i++)
        sem_init(&mutex[i],0,1);

    for(int i=0;i<5;i++){
        int rc = pthread_create(&threads[i],NULL,func,(void*)(i));
        if(rc <0){
            printf("Cant create thread!!exit");
            exit(0);
        }
    }

    for(int i=0;i<5;i++){
        pthread_join(threads[i],NULL);
    }
    pthread_exit(0);
    return 0;
}
