#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
sem_t mutex;
sem_t num_loaded_buffer,num_empty_buffer;
int buffer[5] = {0,0,0,0,0};
int buffer_ctr = 0;
void* func(void* argument){
    int item_no = 0;
    int i = (int)argument;
    if(i<3){
        while(item_no<4){
            sem_wait(&num_empty_buffer);
            sem_wait(&mutex);
            item_no++;
            buffer[buffer_ctr] = 1;
            buffer_ctr +=1;
            printf("loaded data by thread %d at buffer[%d]\n",i,buffer_ctr-1);
            sem_post(&mutex);
            sem_post(&num_loaded_buffer);
            sleep(1);
        }
    }
    else{
        while(item_no<4){
            sem_wait(&num_loaded_buffer);
            sem_wait(&mutex);
            item_no++;
            buffer_ctr -=1;
            buffer[buffer_ctr] = 0;
            printf("taken data by thread %d from buffer[%d]\n",i,buffer_ctr+1);
            sem_post(&mutex);
            sem_post(&num_empty_buffer);
            sleep(1);
        }        
    }

}

int main(){
    pthread_t threads[6];
    sem_init(&mutex,0,1);
    sem_init(&num_loaded_buffer,0,0);
    sem_init(&num_empty_buffer,0,5);
    for(int i=0;i<6;i++){
        /*
        Note: threads with i<3 are producer and rest are consumer threads
        */

        int rc = pthread_create(&threads[i],NULL,func,(void*)(i));
        if(rc <0){
            printf("Cant create thread!!exit");
            exit(0);
        }
    }

    for(int i=0;i<6;i++){
        pthread_join(threads[i],NULL);
    }
    pthread_exit(0);
    return 0;
}
