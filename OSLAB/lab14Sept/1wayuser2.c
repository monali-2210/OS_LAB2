#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "q1"
int main() {
   int fd;
   char s[80];
   char end[10];
   int e;
   int read_bytes;
   

  
   strcpy(end, "Exit");
   while(1) {
      fd = open(FIFO_FILE, O_RDONLY);
      read_bytes = read(fd, s, sizeof(s));
      s[read_bytes] = '\0';
      printf("Received message : %s\n", s);
      e = strcmp(s, end);
      if (e == 0) {
         close(fd);
         break;
      }
   }
   return 0;
}

