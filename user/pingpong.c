#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int pipe1[2],pipe2[2];
    int pid;
    pipe(pipe1);
    pipe(pipe2);
    char buf[] = {'a'};
    pid = fork();   
    if(pid == 0)//c
    {
        close(pipe1[1]);
        close(pipe2[0]);
        read(pipe1[0], buf, 1);
        printf("%d: received ping\n", getpid());
        write(pipe2[1], buf, 1);
        exit(0);

    }
    else//p
    {
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1], buf, 1);
        read(pipe2[0], buf, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }
}