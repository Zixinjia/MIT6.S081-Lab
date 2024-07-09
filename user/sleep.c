#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[])
{
	// printf("argc[0]==%s\n", argv[0]);
	if (argc == 0)
	{
		printf("there are no arguments\n");
		exit(0);
	}
	int t = atoi(argv[1]);
	sleep(t);
	exit(0);
}
