#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "q1"
int main() {
   int fd;
   int e;
   int ssize;
   char s[80];
   char terminate[10];
   mkfifo(FIFO_FILE, 0666);
   printf("Send messages, to end enter \"Exit\"\n");
   fd = open(FIFO_FILE, O_WRONLY);
   strcpy(terminate, "Thanks");
   
   while (1) {
      printf("Enter message: ");
      fgets(s, sizeof(s), stdin);
      ssize = strlen(s);
      s[ssize - 1] = '\0';
      e = strcmp(s, terminate);
      
      if (e != 0) {
         write(fd, s, strlen(s));
         printf("Message Sent! : %s\n", s);
      } else {
         write(fd, s, strlen(s));
         printf("Message Sent! : %s\n", s);
         close(fd);
         break;
      }
   }
   return 0;
}

