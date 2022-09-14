#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//char *message = "This is a message!!!";

int main (int argc, char **argv){
    int pipe1[2];
    int pipe2[2];

    pid_t childpid[2];

    FILE *fdin;
    char buf[1024];

    //long fsize;

    pipe(pipe1);
    pipe(pipe2);

// error handling
    if ((childpid[0] = fork()) == -1)
    {
        perror("fork");
        exit(1);
    }

    // parent load file, write to pipe1
    if (childpid[0] != 0){

        close(pipe1[0]);
        close(pipe2[1]);


        fdin = fopen(argv[1], "r");

        //fseek(fdin, 0, SEEK_END);
        //fsize = ftell(fdin);
        //fseek(fdin, 0, SEEK_SET);

        fread(buf, sizeof(buf), 1, fdin);
        fclose(fdin);

        dup2(pipe1[1],STDOUT_FILENO);
        write(pipe1[1], buf, sizeof(buf));
        close(pipe1[1]);
    }
    else if (childpid[0] == 0){
        buf[0] = '\0';
        int pipe3[2];

        pipe(pipe3);

        close(pipe1[1]);
        close(pipe2[0]);

        //dup2(pipe2[1], STDOUT_FILENO);
        dup2(pipe1[0], STDIN_FILENO);
        //dup2(pipe3[1],STDOUT_FILENO);

        read(pipe1[0], buf, sizeof(buf));
        close(pipe1[0]);

        write(pipe3[1], buf, sizeof(buf));
        printf("-PIPED BUFF-\n%s\n\n", buf);

        if ((childpid[1] = fork()) == -1){
            perror("fork second child");
            exit(1);
        }
        // Child of child (sort call)
        if (childpid[1] != 0){
            close(pipe2[1]);
            close(pipe3[0]);
            printf("I AM YOUR FATHER LOOK\n");
        }else{
            printf("a\n");
            buf[0] = '\0';
            printf("b\n");
            close(pipe3[1]);
            printf("c\n\n");

            dup2(pipe3[0], STDIN_FILENO);
            read(pipe3[0], buf, sizeof(buf));
            close(pipe3[0]);

            //printf("-SORT BUFF-\n%s\n\n", buf);
            //dup2(pipe2[1], STDOUT_FILENO);
            close(pipe2[1]);

            execlp("sort","sort",(char *)0);

            printf("-SORTED BUFF-\n%s\n\n", buf);
            exit(0);
        }
        // wait second child exec
        wait(NULL);

        //printf("%s\n", buf);
        exit(0);
    }

    // wait child exec
    //wait(NULL);

    int status;
    pid_t pid;
    int n = 2;
    while (n > 0){
        pid = wait(&status);
        printf("-SORTED BUFF-\n%s\n\n", buf);
        --n;
    }
    // parent read pipe 2 and print
    if (childpid[0] != 0){
        printf("asd\n");
        buf[0] = '\0';
        dup2(pipe2[0], STDIN_FILENO);
        read(pipe2[0], buf, sizeof(buf));
        close(pipe2[0]);
        printf("-SORTED BUFF-\n%s\n\n", buf);
    }
    return 0;
}

