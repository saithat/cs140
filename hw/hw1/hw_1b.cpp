#include <stdio.h>
int strlen(char *str)
{
	int count = 0;
	for(int i = 0; *(str+i) != '\0'; i++)
	{
		count = i+1;
	}
	return count;
}
int main(int argc, char **argv)
{
	printf("Num args = %d\n", argc);
	for(int i = 0; i < argc; i++)
	{
		printf("argv[%d] = %p %s (strlen=%d)\n", i, argv[i], argv[i], strlen(argv[i]));
	}

	return 0;
}
