#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>

void *PrintHello(void *threadid)
{
	int tid= * (int*)threadid;
	printf("Hellow world! It's me, thread #%d\n", tid);
}
int main (int argc, char *argv[])
{
	pthread_t thread0;
	int rc, t=0;
	printf("In main: creating thread %d\n", t);
	rc=pthread_create(&thread0, NULL, PrintHello, &t);
	if (rc){
		printf("ERROR! return code is %d\n", rc);
		exit(-1);
	}
	pthread_exit(0);
}
