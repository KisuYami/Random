#include <stdio.h>
#include <string.h>

const char ohms_law[] = "V = Voltage, R = Resistency, I = Current, P = power.\n\nV = I*R\nI = V/R\nR = V/I\n";

int main(int argc, char *argv[])
{
	if(argc <= 1) return 1;

	if(strcmp(argv[1], "ohms") == 0) printf(ohms_law);
	return 0;
}
