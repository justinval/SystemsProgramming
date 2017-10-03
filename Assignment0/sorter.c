/*******
*
*
*	A beautiful list sorter program written by
*	Justin Valeroso & Tim Song
*
*
*******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sorter.h"
#include "mergesort2.c"
#define MAX 10000

int main (int argc, char *argv[]) 
{
	//Check to see if there is the proper number of params
	if (argc == 3) 
	{	 		
		//Check to see if 1st param is "-c"
		if (strcmp(argv[1], "-c") != 0) 
		{
			printf("Can only sort by column. Please try again. \n");
			return 0;
		}

		//Read format line of CSV file into str[100]
		char str[1000];
		scanf("%s\n", str);				

		//Initializes ptr and movieList
		Movie *ptr;
		Movie **movieList = (Movie **)malloc(MAX * sizeof(Movie *));
		int numOfMovies = 0;

		//Loops until scanf is unsuccessful/reaches EOF
		while (fgets(str, 1000, stdin))
		{	
			//printf("%s \n", str);		
			ptr = (Movie *)malloc(sizeof(Movie));
			parseMovie(str, ptr);					
			movieList[numOfMovies] = ptr;		
			//printMovieFull(movieList[numOfMovies]);
			numOfMovies++;
		}

		//Mergesort list based off of field
		mergeSort(movieList, 0, numOfMovies-1, argv[2]);
		printAll(movieList);
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
		printf("%i. Movie Title: %s \n", i, movieList[i]->movie_title);
		i++;
	}
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
		memcpy(token, str + 1, index);
		
		// +2 b/c of quote and comma
		strcpy(str, temp + 2);
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