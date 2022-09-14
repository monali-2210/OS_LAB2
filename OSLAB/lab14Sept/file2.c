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
	printf("waiting for writers...\n");
	fd=open(FIFO_NAME,O_RDONLY);
	printf("got a writer\n");
	

	if((num=read(fd,s,300))==-1)
		perror("read");
	else
		printf("Reader read %d bytes: %s\n",num, s);
	return 0;
}
