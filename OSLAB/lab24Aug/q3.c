#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(int argc, char* argv[]) {

    int i, n; // n -> no. of processes required in process chain given as cmd line argument

    if(argc != 2) { //checking for valid no. of cmd line arguments

        printf("No. of arguments are less. Try again\n");
        return 1;
    }

    n = atoi(argv[1]);
    while(n) {
        
        pid_t P = fork();

        if(P) {
            waitpid(P, 0, 0);
            printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
            break;
        }

        else {
            n--;
        }
    }

    
    return 0;
}
