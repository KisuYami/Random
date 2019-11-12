#include <stdio.h>
#include <stdlib.h>

#define get_place(x, y) y / 2 + (1 - x)

int main(int argc, char *argv[])
{
	if(argc != 2)
		return 1;

	size_t total_size = atoi(argv[1]);

	for(int i = 0; i < get_place(0, total_size) + 1; ++i) {

		for(int p = 0; p <= get_place(i, total_size); ++p)
			printf(" ");

		for(int p = 0; p <= i; ++p)
			printf(" *");

		printf("\n");
	}

	return 0;
}
