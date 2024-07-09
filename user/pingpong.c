#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main()
{
    int p[2];
    pipe(p);
    // 子进程
    char str[] = "This is a byte stream~";
    int pid = fork();
    if (pid == 0)
    {
        if (read(p[0], str, sizeof str) != 0)
        {
            printf("%d: received ping\n", getpid());
        }
        write(p[1], str, sizeof str);
        close(p[1]);
    }
    else
    {
        write(p[1], str, sizeof str);
        close(p[1]);
        if (read(p[0], str, sizeof str) != 0)
        {
            printf("%d: received pong\n", getpid());
        }
        close(p[0]);
    }
    exit(0);
}