#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10000

//Read format line of CSV file into str[100]
Movie **sortFile(char *fileDirPath, char *filePath, char *sortBy, char *outputFileName, char *outputDir)
{
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

	// Print the movie list into a CSV file either at the specified outputDir, or in
	// the fileDirPath where the original CSV file was found
	printAllCSVFile (movieList, fileDirPath, filePath, outputFileName, outputDir);
	
	return movieList;

}