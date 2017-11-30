#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000

//Read format line of CSV file into str[100]
void *sortFile(void *ptrIn)
{	
	printf("ThreadID: %i \n", syscall( __NR_gettid ));
	
	// Parse out data from sortFileParams
	SortFileStruct *sortFileParams = (SortFileStruct *)ptrIn;
	char *fileDirPath = sortFileParams->fileDirPath;
	char *filePath = sortFileParams->filePath;
	char *sortBy = sortFileParams->sortBy;
	char *outputFileName = sortFileParams->outputFileName;
	char *outputDir = sortFileParams->outputDir;

	FILE *file = fopen(filePath, "r");

    char line[1000];

    //reading the first row of column names
    fgets(line, 1000, file);
		
	Movie *ptr;
	Movie **movieList = (Movie **)malloc(MAX * sizeof(Movie *));
	int numOfMovies = 0;


	//Loops until scanf is unsuccessful/reaches EOF
	while (fgets(line, 1000, file))
	{
		ptr = (Movie *)malloc(sizeof(Movie));
		parseMovie(line, ptr);					
		movieList[numOfMovies] = ptr;		
		numOfMovies++;
	}

    fclose(file);
	
	//Mergesort list based off of field
	mergeSort(movieList, 0, numOfMovies-1, sortBy);

	pthread_mutex_lock(&mutex);
	int i = 0;
	while (movieList[i] != NULL)
	{
		masterMovieList[index] = movieList[i];
		index++;
		i++;
	}
	pthread_mutex_unlock(&mutex);


	return movieList;

}