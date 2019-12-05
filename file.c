#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int fd[3] = 0;

	fd[0] = open("file.c", 0);
	fd[1] = open("law.c", 0);
	fd[2] = open("NONE", 0);

	for(int i = 0; i < 3; ++i)
		printf("FD: %d\n", i);

	for(int i = 0; i < 3; ++i)
		printf("FD: %d\n", fd[i]);

	close(fd);
    return 0;
}
