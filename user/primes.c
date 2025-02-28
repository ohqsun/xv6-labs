#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>

void
primescheck(int read_pipe)
{
    int my_num = 0;
    int read_num = 0;
    int forked = 0;
    int pipes[2];
    while(1)
    {
        int read_len = read(read_pipe, &read_num, 4);
        //cannot read more
        if(read_len == 0)
        {
            close(read_pipe);
            //has children
            if(forked)
            {
                close(pipes[1]);
                int child;

                wait(&child);

            }
            exit(0);
        }
        if(my_num == 0)
        {
            my_num = read_num;
            printf("prime %d\n", my_num);

        }
        if(read_num % my_num != 0)
        {
            if (!forked)
            {
                pipe(pipes);
                forked = 1;
                int ret = fork();
                if(ret == 0)
                {
                    close(pipes[1]);
                    close(read_pipe);
                    primescheck(pipes[0]);
                }
                else
                {
                    close(pipes[0]);
                }
            }
            
            write(pipes[1], &read_num, 4);
        }
        

    }
}


int main(int argc, char *argv[]) {
    int pipes[2];
    pipe(pipes);
    for (int i = 2; i <= 35; i++) {
        write(pipes[1], &i, 4);
    }
    close(pipes[1]);
    primescheck(pipes[0]);
    exit(0);
}