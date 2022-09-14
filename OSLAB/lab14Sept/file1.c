#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#define FIFO_NAME "myfile.txt"

int main(void)
{ 
	char s[300];
	int num,fd;
	mkfifo(FIFO_NAME,0666);
	printf("waiting for readers...\n");
	fd=open(FIFO_NAME,O_WRONLY);
	printf("got a reader--type some stuff\n");
	gets(s);
	if((num=write(fd,s,strlen(s)))==-1)
		perror("write");
	else
		printf("Writer wrote %d bytes\n",num);
	return 0;
}
