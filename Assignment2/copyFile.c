#define NUMFILES 1
#define NUMDIR 1 
#define FILENAME "movie_metadata.csv"
#define DIRNAME "someDir"

int main (int argc, char *argv[]) {
	mkdir(DIRNAME, 0777);


	FILE *file = fopen(FILENAME, "r");	
	char *tempFileName =  (char *)malloc(10 * sizeof(char));
	int i;
	for (i = 0; i < NUMFILES; i++)
	{
		sprintf(tempFileName, "%s/%d.txt", DIRNAME, j);
		FILE *destFile = fopen(tempFileName, "w");
		char c;
		while ((c = fgetc(file)) != EOF)
		{
			fputc(destFle);
		}
	}
}