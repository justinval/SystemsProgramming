#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Sorter.h"
#define MAX 10000

int main (int argc, char *argv[]) 
{
	//Check to see if there is the proper number of params
	if (argc == 3) 
	{	 		
		//Check to see if 1st param is "-c"
		if (strcmp(argv[1], "-c") != 0) {
			printf("Can only sort by column. Please try again. \n");
			return 0;
		}

		//Read format line of CSV file into str[100]
		char str[2000];
		scanf("%s", str);				
		
		//Initializes ptr and movieList
		Movie *ptr;
		Movie **movieList = (Movie **)malloc(MAX * sizeof(Movie *));
		int numOfMovies = 0;

		//Loops until scanf is unsuccessful/reaches EOF
		while (scanf("%s", str) > 0)
		{			
			ptr = (Movie *)malloc(sizeof(Movie));
			parseMovie(str, ptr);					
			movieList[numOfMovies] = ptr;		
			printMovie(movieList[numOfMovies]);
			numOfMovies++;
		}
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
	printf("%s \n", str);

	const char s[2] = ",";
	char *token;

	//Initializes all fields
	token = strtok(str, s);
	//ptr->color = token;
	strcpy(ptr->color, token);
	token = strtok(NULL, s);
	//ptr->director_name = token;
	strcpy(ptr->director_name, token);
	token = strtok(NULL, s);
	printf("test \n");	
	ptr->num_critic_for_reviews = atoi(token);
	token = strtok(NULL, s);
	ptr->duration;
	token = strtok(NULL, s);
	ptr->director_facebook_likes;
	token = strtok(NULL, s);
	ptr->actor_3_facebook_likes;
	token = strtok(NULL, s);
	ptr->actor_2_name;
	token = strtok(NULL, s);
	ptr->actor_1_facecbook_likes;
	token = strtok(NULL, s);
	ptr->gross;
	token = strtok(NULL, s);
	ptr->genres;
	token = strtok(NULL, s);
	ptr->actor_1_name;
	token = strtok(NULL, s);
	ptr->movie_title;
	token = strtok(NULL, s);
	ptr->num_voted_users;
	token = strtok(NULL, s);
	ptr->cast_total_facebook_likes;
	token = strtok(NULL, s);
	ptr->actor_3_name;
	token = strtok(NULL, s);
	ptr->facenumber_in_poster;
	token = strtok(NULL, s);
	ptr->plot_keywords;
	token = strtok(NULL, s);
	ptr->movie_imbd_link;
	token = strtok(NULL, s);
	ptr->num_user_for_reviews;
	token = strtok(NULL, s);
	ptr->language;
	token = strtok(NULL, s);
	ptr->country;
	token = strtok(NULL, s);
	ptr->content_rating;
	token = strtok(NULL, s);
	ptr->budget;
	token = strtok(NULL, s);
	ptr->title_year;
	token = strtok(NULL, s);
	ptr->actor_2_facebook_likes;
	token = strtok(NULL, s);
	ptr->imbd_score;
	token = strtok(NULL, s);
	ptr->aspect_ratio;
	token = strtok(NULL, s);
	ptr->movie_facebook_likes;

	return;
}

void printMovie (Movie *ptr)
{	
	printf("Movie title: %s | Direcotr Name: %s \n", ptr->movie_title, ptr->director_name);
	printf("____________________________________\n");
	return;
}