/*Julia Pittner*/
#include <stdio.h>
/*This prototype opens a file using command line args*/
int main(int argc, char *argv[])
{
	struct File 
	{
		FILE *input;
		int argc;
		char **argv;
	};
	struct File inputFile;
	inputFile.argc = argc;
	inputFile.argv = argv;
	inputFile.input = fopen(inputFile.argv[1], "r");
	if(inputFile.input != NULL)
	{
		printf("File successfully opened!\n");
	}
	fclose(inputFile.input);

	return 0;
}
