#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main() {

    int nodes = 1, D, N; //D -> Depth, N -> children for each node 
    printf("Enter the values :\n");
    printf("D : ");
    scanf("%d", &D);
    printf("N : ");
    scanf("%d", &N);

    if(D == 1) {
        printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
    }

    while(nodes <= N && D > 1) {
        
        pid_t P = fork();
        if(P == 0) { //for next level creation
            
            printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());
            nodes = 1;
            D = D-1;
            
        }

        else { //creating all child nodes for the parent

            waitpid(P, 0, 0);
            nodes += 1;
        }
    }
    return 0;
}
