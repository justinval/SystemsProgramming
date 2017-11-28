#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#define NUMFILES 1
#define NUMDIR 1 
#define FILENAME "movie_metadata.csv"
#define DIRNAME "someDir"

int main (int argc, char *argv[]) {
	printf("test");
	//mkdir("someDir", 0777);
	printf("test");

	FILE *file = fopen(FILENAME, "r");	
	char *tempFileName =  (char *)malloc(10 * sizeof(char));
	int i;
	for (i = 0; i < NUMFILES; i++)
	{
		sprintf(tempFileName, "%s/%d.txt", "someDir", i);
		FILE *destFile = fopen(tempFileName, "w");
		char c;
		while ((c = fgetc(file)) != EOF)
		{
			fputc(c, destFile);
		}
	}
}