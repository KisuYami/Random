#include <stdio.h>
#include <stdlib.h>

int 
main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("usage: leading-char <set-of-char> <string>\n");
		return 1;
	}

	int count;

	for (int i = 0; argv[2][i] != '\0'; ++i) 
	{
		if(argv[2][i] == argv[1][0])
			count++;

		if(argv[2][i] == argv[1][1])
			count--;
	}

	if(count < 0)
		count = abs(count);

	printf("Result: %d\n", count);
	return 0;
}
