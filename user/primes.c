#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void f(int *pl)
{
    // 从左端读取
    int prime;

    if (read(pl[0], &prime, sizeof prime) == 0)
        return;
    printf("prime %d\n", prime);
    int pr[2];
    pipe(pr);
    int pid = fork();
    if (pid > 0)
    {
        close(pr[0]);
        for (int t; read(pl[0], &t, sizeof(t)) != 0;)
        {
            if (t % prime != 0)
            {
                write(pr[1], &t, sizeof(t));
            }
        }
        close(pr[1]);
        close(pr[0]);
        wait(0);
        exit(0);
    }
    else if (pid == 0)
    {
        close(pr[1]);
        close(pl[0]);
        f(pr);
        close(pr[0]);
        exit(0);
    }
    else
    {
        // 创建失败
        close(pl[0]);
        close(pl[1]);
        close(pr[1]);
        exit(1);
    }
}

int main()
{
    int pl[2];
    pipe(pl);
    int pid = fork();
    // 子进程
    if (pid == 0)

    {
        close(pl[1]);
        f(pl);
        close(pl[0]);
        exit(0);
    }
    else if (pid > 0)
    {
        close(pl[0]);
        for (int i = 2; i <= 35; i++)
        {
            write(pl[1], &i, sizeof i);
        }
        close(pl[1]);
        wait(0);
        exit(0);
    }
    else
    {
        // 进程创建发生错误
        close(pl[1]);
        close(pl[0]);
        exit(1);
    }
    return 0;
}
