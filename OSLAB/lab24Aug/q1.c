#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int G; //global variable

int main() {

    int L = 0; //local variable
    pid_t P = fork(); //creating a child process

    if(P >= 0) {  //checking for successful fork
        if(P == 0) { //child

            printf("For Child process,\nInitial values :\nG : %d, L : %d\n", G, L);
            G++;
            L++;
            printf("Incrementing both by 1:\nG : %d, L : %d\n", G, L);
        }

        else {   //parent

            printf("For Parent Process,\nInitial values :\nG : %d, L : %d\n", G, L);
            G += 10;
            L += 10;
            printf("Incrementing both by 10:\nG : %d, L : %d\n", G, L);
        } 
    }

    else {

        printf("Fork was unsuccessful\n");
        return 1;
    }
    return 0;
}
