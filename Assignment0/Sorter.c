#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Sorter.h"
#define MAX 10000

int main (int argc, char *argv[]) 
{
	printf("test\n");	
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
		Movie *ptr = (Movie *)malloc(sizeof(Movie));
		Movie **movieList = (Movie **)malloc(MAX * sizeof(Movie *));
		int numOfMovies = 0;

		//Loops until scanf is unsuccessful/reaches EOF
		while (scanf("%s,%s,%i,%i,%i,%i,%s,%i,%i,%s,%s,%s,%i,%i,%s,%i,%s,%s,%i,%s,%s,%s,%i,%i,%i,%f,%f,%i",
				&ptr->color, &ptr->director_name, &ptr->num_critic_for_reviews, &ptr->duration, &ptr->director_facebook_likes,
				&ptr->actor_3_facebook_likes, &ptr->actor_2_name, &ptr->actor_1_facecbook_likes, &ptr->gross, &ptr->genres,
				&ptr->actor_1_name, &ptr->movie_title, &ptr->num_voted_users, &ptr->cast_total_facebook_likes, &ptr->actor_3_name,
				&ptr->facenumber_in_poster, &ptr->plot_keywords, &ptr->movie_imbd_link, &ptr->num_user_for_reviews,
				&ptr->language, &ptr->country, &ptr->content_rating, &ptr->budget, &ptr->title_year, &ptr->actor_2_facebook_likes,
				&ptr->imbd_score, &ptr->aspect_ratio, &ptr->movie_facebook_likes) > 0)
		{					
			movieList[numOfMovies] = ptr;
			numOfMovies++;
			printMovie(movieList[numOfMovies]);
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

void printMovie (Movie *ptr)
{	
	printf("Movie title: %s | Direcotr Name: %s", ptr->movie_title, ptr->director_name);
	return;
}