#include <stdio.h>

int main(int argc, char *argv[])
{

	if(argc < 1)
		return -1;

	long int first, second;
	char op;

	sscanf(argv[1], "%d %c %d", &first, &op, &second);

	if(op == '+') printf("%d\n", first + second);
	if(op == '-') printf("%d\n", first - second);
	if(op == '*') printf("%d\n", first * second);
	if(op == '/') printf("%d\n", first / second);

    return 0;
}
