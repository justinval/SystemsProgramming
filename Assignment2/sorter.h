/*****
*
*	Define structures and function prototypes for your sorter
*
*
*
******/

//Suggestion: define a struct that mirrors a record (row) of the data set


//Suggestion: prototype a mergesort function

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SortDirStructs{
	char *targetDir; 
	char *outputDir;	
	char *sortBy; 
	FILE *file;
} SortDirStruct;


typedef struct SortFileStructs{
	char *fileDirPath; 
	char *filePath;
	char *sortBy;
	char *outputFileName; 
	char *outputDir;
	FILE *threadsFile;
} SortFileStruct;

typedef struct Movies {
	char color[10];
	char director_name[30];
	int	num_critic_for_reviews;
	int duration;
	int director_facebook_likes;
	int actor_3_facebook_likes;
	char actor_2_name[30];
	int actor_1_facecbook_likes;
	int gross;
	char genres[100];
	char actor_1_name[30];
	char movie_title[100];
	int num_voted_users;
	int cast_total_facebook_likes;
	char actor_3_name[30];
	int facenumber_in_poster;
	char plot_keywords[100];
	char movie_imbd_link[150];
	int num_user_for_reviews;
	char language[20];
	char country[20];
	char content_rating[20];
	int budget;
	int title_year;
	int actor_2_facebook_likes;
	float imbd_score;
	float aspect_ratio;
	int movie_facebook_likes;
} Movie;

void parseMovie (char str[], Movie *ptr);
void printMovie (Movie *ptr); 
void printMovieFull (Movie *ptr);
void printAll (Movie **movieList);
void printAllCSV (Movie **movieList);
void printAllCSVFile (Movie **movieList, char *fileDirPath, char *filePath, char *outputFileName, char *outputDir);
void printAllCSVSingleFile (char *outputDir);
void printThreads(char *fileName);
char *strtokPlus (char *str, const char *delim);
void *sortDir (void *ptrIn);
void *sortFile (void *ptrIn);