/*******
*
*
*	A beautiful list sorter program written by
*	Justin Valeroso & Yong Jun Song
*
*
*******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include "sorter.h"
#include "mergesort.c"
#include "sortFile.c"
#define MAX 1000000

//movieMasterList is the global data structure that will hold all the sorted movie files
long long index = 0; 
Movie **masterMovieList = (Movie **)malloc(MAX * sizeof(Movie *));

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main (int argc, char *argv[]) 
{
	//Check to see if there is the proper number of params
	if (argc == 5 || argc == 7) 
	{	 		
		// Use switch-case to parse flags
		char *column, *targetDir, *outputDir; 
		int index;
		for (index = 2; index < argc; index+=2) {
			switch (argv[index-1][1]) {
				case 'c':
					column = argv[index];
					break;
				case 'd':
					targetDir = argv[index];
					break;
				case 'o':
					outputDir = argv[index];
			}
		}
		
		//Print out the process ID as per Tjang's instructions
		printf("Initial PID: %d \n", getpid());

		//Open up a file so threads can write to it
		char *tempFileName = "threadsList.txt";
		FILE *file = fopen(tempFileName, "w");

		//Store parameters for sortDir function and sort directories using sortDir
		SortDirStruct *sortDirParams = (SortDirStruct *)malloc(sizeof(SortDirStruct));
		sortDirParams->targetDir = targetDir;
		sortDirParams->outputDir = outputDir;
		sortDirParams->sortBy = column;
		sortDirParams->file = file;
		sortDir((void *)sortDirParams);

		//Close file
		fclose(file);

		//Print threads using the tempFileName that all threads wrote to
		printThreads(tempFileName);
		return 0;
    }

    //If the user didn't have the proper number of params
    else
    {
    	printf("Invalid number of inputs. Please try again. \n");
    	return 0;
    }
}

void parseMovie (char str[], Movie *ptr)
{	
	const char s[2] = ",";
	char *temp = (char *)malloc(2000 * sizeof(char));
	char *token;
	strcpy(temp, str);
	//Initializes all fields within the Movie struct
	//token = strtokPlus(temp, s);
	// strcpy(ptr->color, token);
	strcpy(ptr->color, strtokPlus(temp, s));
	token = strtokPlus(temp, s);
	strcpy(ptr->director_name, token);
	token = strtokPlus(temp, s);
	ptr->num_critic_for_reviews = atoi(token);
	token = strtokPlus(temp, s);
	ptr->duration = atoi(token);
	token = strtokPlus(temp, s);
	ptr->director_facebook_likes = atoi(token);
	token = strtokPlus(temp, s);
	ptr->actor_3_facebook_likes = atoi(token);
	token = strtokPlus(temp, s);
	strcpy(ptr->actor_2_name, token);
	token = strtokPlus(temp, s);
	ptr->actor_1_facecbook_likes = atoi(token);
	token = strtokPlus(temp, s);
	ptr->gross = atoi(token);
	token = strtokPlus(temp, s);
	strcpy(ptr->genres, token);
	token = strtokPlus(temp, s);
	strcpy(ptr->actor_1_name, token);
	token = strtokPlus(temp, s);
	strcpy(ptr->movie_title, token);
	token = strtokPlus(temp, s);
	ptr->num_voted_users = atoi(token);
	token = strtokPlus(temp, s);
	ptr->cast_total_facebook_likes = atoi(token);
	token = strtokPlus(temp, s);
	strcpy(ptr->actor_3_name, token);
	token = strtokPlus(temp, s);
	ptr->facenumber_in_poster = atoi(token);
	token = strtokPlus(temp, s);
	strcpy(ptr->plot_keywords, token);
	token = strtokPlus(temp, s);
	strcpy(ptr->movie_imbd_link, token);
	token = strtokPlus(temp, s);
	ptr->num_user_for_reviews = atoi(token);
	token = strtokPlus(temp, s);
	strcpy(ptr->language, token);
	token = strtokPlus(temp, s);
	strcpy(ptr->country, token);
	token = strtokPlus(temp, s);
	strcpy(ptr->content_rating, token);
	token = strtokPlus(temp, s);
	ptr->budget = atoi(token);
	token = strtokPlus(temp, s);
	ptr->title_year = atoi(token);
	token = strtokPlus(temp, s);
	ptr->actor_2_facebook_likes = atoi(token);
	token = strtokPlus(temp, s);
	ptr->imbd_score = atof(token);
	token = strtokPlus(temp, s);
	ptr->aspect_ratio = atof(token);
	token = strtokPlus(temp, s);
	ptr->movie_facebook_likes = atoi(token);

	return;
}

void printMovie (Movie *ptr)
{	
	printf("Movie title: %s | Director Name: %s | # of Critics: %i\n", ptr->movie_title, ptr->director_name, ptr->num_critic_for_reviews);
	printf("____________________________________\n");
	return;
}

void printMovieFull (Movie *ptr)
{
	printf("Color: %s | Director Name: %s | No. of Critics for Reviews: %i | Duration: %i | Director Facebook Likes: %i | \n"
			"Actor 3 Facebook Likes: %i | Actor 2 Name: %s | Actor 1 Facebook Likes: %i | Gross: %i | Genres: %s | \n"
			"Actor 1 Name: %s | Movie Title: %s | No. of Voted Users: %i | Cast Total Facebook Likes: %i | Actor 3 Name: %s | \n"
			"Face No. in Poster: %i | Plot Keywords: %s | Movie IMBD Link: %s | No. of Users for Reviews: %i | Language: %s | \n"
			"Country: %s | Content Rating: %s | Budget: %i | Title Year: %i | Actor 2 Facebook Likes: %i | IMBD Score: %f | \n"
			"Aspect Ratio: %f | Movie Facebook Likes: %i \n", ptr->color, ptr->director_name, ptr->num_critic_for_reviews, 
			ptr->duration, ptr->director_facebook_likes, ptr->actor_3_facebook_likes, ptr->actor_2_name, ptr->actor_1_facecbook_likes, 
			ptr->gross, ptr->genres, ptr->actor_1_name, ptr->movie_title, ptr->num_voted_users, ptr->cast_total_facebook_likes, 
			ptr->actor_3_name, ptr->facenumber_in_poster, ptr->plot_keywords, ptr->movie_imbd_link, ptr->num_user_for_reviews, 
			ptr->language, ptr->country, ptr->content_rating, ptr->budget, ptr->title_year, ptr->actor_2_facebook_likes, ptr->imbd_score, 
			ptr->aspect_ratio, ptr->movie_facebook_likes);

	printf("___________________________________________________________________ \n");	
}

void printAll (Movie **movieList)
{
	int i = 0;
	while (movieList[i] != NULL)
	{
		printMovieFull(movieList[i]);
		i++;
	}
}

void printAllCSV (Movie **movieList)
{
	printf("color,director_name,num_critic_for_reviews,duration,director_facebook_likes"
			",actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,"
			"actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,"
			"facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,"
			"country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,"
			"aspect_ratio,movie_facebook_likes\n");	

	int i = 0;
	while (movieList[i] != NULL)
	{
		if (strchr(movieList[i]->movie_title, ',') != NULL)
		{
			printf("%s,%s,%i,%i,%i,%i,%s,%i,%i,%s,%s,\"%s\",%i,%i,%s,%i,%s,%s,%i,%s,%s,%s,%i,%i,%i,%f,%f,%i\n",
				movieList[i]->color, movieList[i]->director_name, movieList[i]->num_critic_for_reviews, movieList[i]->duration, 
				movieList[i]->director_facebook_likes, movieList[i]->actor_3_facebook_likes, movieList[i]->actor_2_name,
				movieList[i]->actor_1_facecbook_likes, movieList[i]->gross, movieList[i]->genres, movieList[i]->actor_1_name, 
				movieList[i]->movie_title, movieList[i]->num_voted_users, movieList[i]->cast_total_facebook_likes, 
				movieList[i]->actor_3_name, movieList[i]->facenumber_in_poster, movieList[i]->plot_keywords, 
				movieList[i]->movie_imbd_link, movieList[i]->num_user_for_reviews, movieList[i]->language, 
				movieList[i]->country, movieList[i]->content_rating, movieList[i]->budget, movieList[i]->title_year, 
				movieList[i]->actor_2_facebook_likes, movieList[i]->imbd_score, movieList[i]->aspect_ratio, 
				movieList[i]->movie_facebook_likes);
		i++;
		}

		else {
			printf("%s,%s,%i,%i,%i,%i,%s,%i,%i,%s,%s,%s,%i,%i,%s,%i,%s,%s,%i,%s,%s,%s,%i,%i,%i,%f,%f,%i\n",
				movieList[i]->color, movieList[i]->director_name, movieList[i]->num_critic_for_reviews, movieList[i]->duration, 
				movieList[i]->director_facebook_likes, movieList[i]->actor_3_facebook_likes, movieList[i]->actor_2_name,
				movieList[i]->actor_1_facecbook_likes, movieList[i]->gross, movieList[i]->genres, movieList[i]->actor_1_name, 
				movieList[i]->movie_title, movieList[i]->num_voted_users, movieList[i]->cast_total_facebook_likes, 
				movieList[i]->actor_3_name, movieList[i]->facenumber_in_poster, movieList[i]->plot_keywords, 
				movieList[i]->movie_imbd_link, movieList[i]->num_user_for_reviews, movieList[i]->language, 
				movieList[i]->country, movieList[i]->content_rating, movieList[i]->budget, movieList[i]->title_year, 
				movieList[i]->actor_2_facebook_likes, movieList[i]->imbd_score, movieList[i]->aspect_ratio, 
				movieList[i]->movie_facebook_likes);
			i++;
		}
	}
}

void printAllCSVFile (Movie **movieList, char *fileDirPath, char *filePath, char *outputFileName, char *outputDir)
{	
	// If outputDir wasn't inputted, create an output file in the directory that the CSV file was found in
	FILE *outputFile;

	if (outputDir == NULL)
	{
		strcat(fileDirPath, "/");
		strcat(fileDirPath, outputFileName);
		outputFile = fopen(fileDirPath, "w");
	}
	else
	{
		strcat(outputDir, "/");
		strcat(outputDir, outputFileName);
		outputFile = fopen(outputDir, "w");
	}
	
	// If you couldn't create the file or open it, exit
	if (outputFile == NULL) {
  		fprintf(stderr, "Can't open output file %s!\n", outputFileName);
	  	exit(1);
	}

	fprintf(outputFile, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes"
			",actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,"
			"actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,"
			"facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,"
			"country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,"
			"aspect_ratio,movie_facebook_likes\n");	

	int i = 0;
	while (movieList[i] != NULL)
	{
		if (strchr(movieList[i]->movie_title, ',') != NULL)
		{
			fprintf(outputFile, "%s,%s,%i,%i,%i,%i,%s,%i,%i,%s,%s,\"%s\",%i,%i,%s,%i,%s,%s,%i,%s,%s,%s,%i,%i,%i,%f,%f,%i\n",
				movieList[i]->color, movieList[i]->director_name, movieList[i]->num_critic_for_reviews, movieList[i]->duration, 
				movieList[i]->director_facebook_likes, movieList[i]->actor_3_facebook_likes, movieList[i]->actor_2_name,
				movieList[i]->actor_1_facecbook_likes, movieList[i]->gross, movieList[i]->genres, movieList[i]->actor_1_name, 
				movieList[i]->movie_title, movieList[i]->num_voted_users, movieList[i]->cast_total_facebook_likes, 
				movieList[i]->actor_3_name, movieList[i]->facenumber_in_poster, movieList[i]->plot_keywords, 
				movieList[i]->movie_imbd_link, movieList[i]->num_user_for_reviews, movieList[i]->language, 
				movieList[i]->country, movieList[i]->content_rating, movieList[i]->budget, movieList[i]->title_year, 
				movieList[i]->actor_2_facebook_likes, movieList[i]->imbd_score, movieList[i]->aspect_ratio, 
				movieList[i]->movie_facebook_likes);
		i++;
		}

		else {
			fprintf(outputFile, "%s,%s,%i,%i,%i,%i,%s,%i,%i,%s,%s,%s,%i,%i,%s,%i,%s,%s,%i,%s,%s,%s,%i,%i,%i,%f,%f,%i\n",
				movieList[i]->color, movieList[i]->director_name, movieList[i]->num_critic_for_reviews, movieList[i]->duration, 
				movieList[i]->director_facebook_likes, movieList[i]->actor_3_facebook_likes, movieList[i]->actor_2_name,
				movieList[i]->actor_1_facecbook_likes, movieList[i]->gross, movieList[i]->genres, movieList[i]->actor_1_name, 
				movieList[i]->movie_title, movieList[i]->num_voted_users, movieList[i]->cast_total_facebook_likes, 
				movieList[i]->actor_3_name, movieList[i]->facenumber_in_poster, movieList[i]->plot_keywords, 
				movieList[i]->movie_imbd_link, movieList[i]->num_user_for_reviews, movieList[i]->language, 
				movieList[i]->country, movieList[i]->content_rating, movieList[i]->budget, movieList[i]->title_year, 
				movieList[i]->actor_2_facebook_likes, movieList[i]->imbd_score, movieList[i]->aspect_ratio, 
				movieList[i]->movie_facebook_likes);
			i++;
		}
	}
}


// Read threads from a file and output them in a proper format
void printThreads (char *fileName)
{
	FILE *file = fopen(fileName, "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int numOfThreads = 0;
	while (getline(&line, &len, file) != -1)
	{	
		int bytes = strlen(line)-2;
		char *temp = (char *)malloc(bytes * sizeof(char));
		strncpy(temp, line, bytes);
		if (numOfThreads == 0)
		{
			printf("TIDS of all child threads: %s", temp);
		}
		else 
		{
			printf(", %s", temp);
		}
		numOfThreads++;
	}

	printf("\n Total number of threads: %i \n", numOfThreads);

	fclose(file);
}


/*Created b/c regular strtok wouldn't take in to consideration 
consecutive delims (',')*/
char *strtokPlus (char *str, const char *delim) 
{
	int index;
	char *token;
	char *temp = (char *)malloc((strlen(str) * sizeof(char)) + 1);

	//Check to see if NULL token
	if (str[0] == ',') 
	{
		token = (char *)malloc(2 * sizeof(char));
		token = " \0";

		strcpy(str, str + 1);
	}

	//Check to see if quotes are used
	else if (str[0] == '"')
	{
		//Check for second '"'
		char *temp2 = (strstr(str + 1, "\""));
		strcpy(temp, temp2);

		//Count all the bytes from the first char after the 
		//first quote to the last char before the last quote
		index = temp2 - (str + 1);
		token = (char *)malloc((index * sizeof(char)) + 1);
		memcpy(token, str + 1, index);
		
		// +2 b/c of quote and comma
		strcpy(str, temp + 2);

		token[index] = '\0';
		free(temp);
	}

	//If not NULL, tokenize the string until the next ','
	else 
	{		
		char *temp2 = (strstr(str, delim));

		//If str still has more values
		if (temp2 != NULL)
		{	
			strcpy(temp, temp2);			

			//Figure out how many bytes to allot and copy str into token
			index = temp2 - str;
			token = (char *)malloc((index * sizeof(char)) + 1);  
			memcpy(token, str, index);			
			strcpy(str, temp + 1);	
		}

		//If str doesn't have more values, tokenize the remaining string
		else 
		{
			//Figure out how many bytes to allot and copy str into token
			index = strlen(str);
			token = (char *)malloc((index * sizeof(char)) + 1);
			memcpy(token, str, index);
		}

		token[index] = '\0';
		//printf("TOKEN: %s \n", token);
		//printf("%s \n", str);		

		free(temp);
	}

	return token;
}

void *sortDir (void *ptrIn) 
{
	printf("ThreadID: %i \n", syscall( __NR_gettid ));

	// Parse out data from sortDirParams
	SortDirStruct *sortDirParams = (SortDirStruct *)ptrIn;
	char *targetDir = sortDirParams->targetDir;
	char *outputDir = sortDirParams->outputDir;
	char *sortBy = sortDirParams->sortBy; 
	FILE *file = sortDirParams->file;

	int t1,t2,t3,t4;
	
	pthread_t dtid, ftid;
	int err;

	// Try to open targetDir
	DIR *dir, *subDir;
	struct dirent *ent;
	if ((dir = opendir(targetDir)) != NULL) 
	{
		// Iterate through each directory entry within dir
		while ((ent = readdir(dir)) != NULL) 
		{
			// Create a path for each directory entry
			char *path = (char *)malloc(256 * sizeof(char));
			strcpy(path, targetDir);
			strcat(path, "/");
			strcat(path, ent->d_name);

			// Try to open each path, and if successful, it's a directory
			if ((subDir = opendir(path)) != NULL)
			{	
				closedir(subDir);

				// Ignore some weird folders
				if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".git") == 0)
				{
                	continue;
				}
				//printf("found directory: %s \n", path);
				
				// Create new thread to traverse the found directory
				t1 = pthread_create(&dtid, NULL, sortDir, (void *)sortDirParams);

				// Waits for the newly created thread to terminate before continuing
				t2 = pthread_join(dtid, NULL);
			}

			// If the directory entry is a CSV file and is not already sorted
			else if (strstr(ent->d_name, ".csv") != NULL && (strstr(ent->d_name, "-sorted-") == NULL)) 
			{
				//printf("Found CSV file: %s \n", path);

				char *outputFileName = (char *)calloc(256, sizeof(char));
				strncpy(outputFileName, ent->d_name, strlen(ent->d_name)-4);
				strcat(outputFileName, "-sorted-");
				strcat(outputFileName, sortBy);
				strcat(outputFileName, ".csv");

				// Initialize a fileStruct to pass into pthread_create
				SortFileStruct *sortFileParams = (SortFileStruct *)malloc(sizeof(SortFileStruct));
				sortFileParams->fileDirPath = targetDir;
				sortFileParams->filePath = path;
				sortFileParams->sortBy = sortBy;
				sortFileParams->outputFileName = outputFileName;
				sortFileParams->outputDir = outputDir;

				// Use the child process to sort the found CSV file
				t3 = pthread_create(&ftid, NULL, sortFile, (void *)sortFileParams);

				// Waits for the newly created thread to terminate before continuing				
				t4 = pthread_join(ftid, NULL);

				free(outputFileName);
			}
			free(path);
		}
		closedir(dir);
	}
	else 
	{
		// Could not open directory
	  	perror ("Cannot find directory");
		return NULL;
	}
	return NULL;
}