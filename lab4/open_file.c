/*Julia Pittner*/
#include <stdio.h>

/*This prototype opens a file*/
int main()
{
	FILE *inputFile = fopen("2fast.sa", "r");
	if(inputFile != NULL)
	{
		printf("File successfully opened!\n");
	}
	fclose(inputFile);

	return 0;
}
