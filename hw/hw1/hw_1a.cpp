#include <stdio.h>
int main(int argc, char **argv)
{
	printf("Num args = %d\n", argc);
	for(int i = 0; i < argc; i++)
	{
		printf("argv[%d] = %p %s\n", i, argv[i], argv[i]);
	}

	return 0;
}
