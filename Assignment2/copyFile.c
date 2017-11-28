#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define NUMFILES 100
#define NUMDIR 1 
#define FILENAME "movie_metadata.csv"
#define DIRNAME "someDir"

int main (int argc, char *argv[]) {
	mkdir(DIRNAME, 0777);	
	char *tempFileName =  (char *)malloc(10 * sizeof(char));
	int i;
	for (i = 0; i < NUMFILES; i++)
	{
		FILE *file = fopen(FILENAME, "r");
		sprintf(tempFileName, "%s/%d.txt", DIRNAME, i);
		printf("%s \n", tempFileName);
		FILE *destFile = fopen(tempFileName, "w");
		char c;
		while ((c = fgetc(file)) != EOF)
		{
			fputc(c, destFile);
		}
		fclose(file);
		fclose(destFile);
	}
}