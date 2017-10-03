#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(Movie *arr[], int l, int m, int r, char* field)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    /* create temp arrays */
    Movie *L[n1], *R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray

    	if (strcmp ("color", field) == 0) 
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->color == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->color == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->color, R[j]->color)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
        }

    	else if (strcmp ("director_name", field) == 0) 
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->director_name == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->director_name == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->director_name, R[j]->director_name)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp ("num_critic_for_reviews", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->num_critic_for_reviews <= R[j]->num_critic_for_reviews)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
        }

    	else if (strcmp("duration", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->duration <= R[j]->duration)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("director_facebook_likes", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->director_facebook_likes <= R[j]->director_facebook_likes)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
        }

    	else if (strcmp("actor_3_facebook_likes", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->actor_3_facebook_likes <= R[j]->actor_3_facebook_likes)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("actor_2_name", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->actor_2_name == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->actor_2_name == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->actor_2_name, R[j]->actor_2_name)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
        }

    	else if (strcmp("actor_1_facecbook_likes", field) == 0) 
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->actor_1_facecbook_likes <= R[j]->actor_1_facecbook_likes)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("gross", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->gross <= R[j]->gross)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("genres",field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->genres == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->genres == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->genres, R[j]->genres)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("actor_1_name", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->actor_1_name == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->actor_1_name == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->actor_1_name, R[j]->actor_1_name)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("movie_title", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->movie_title == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->movie_title == NULL)
                {;
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->movie_title, R[j]->movie_title)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("num_voted_users", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->num_voted_users <= R[j]->num_voted_users)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("cast_total_facebook_likes", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->cast_total_facebook_likes <= R[j]->cast_total_facebook_likes)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("actor_3_name", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->actor_3_name == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->actor_3_name == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->actor_3_name, R[j]->actor_3_name)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("facenumber_in_poster", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->facenumber_in_poster <= R[j]->facenumber_in_poster)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("plot_keywords", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->plot_keywords == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->plot_keywords == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->plot_keywords, R[j]->plot_keywords)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("movie_imbd_link", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->movie_imbd_link == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->movie_imbd_link == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->movie_imbd_link, R[j]->movie_imbd_link)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("num_user_for_reviews", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->num_user_for_reviews <= R[j]->num_user_for_reviews)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("language", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->language == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->language == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->language, R[j]->language)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("country", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->country == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->country == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->country, R[j]->country)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("content_rating", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if(L[i]->content_rating == NULL)
                {
        			arr[k] = L[i];
        			i++;
        		}
        		else if(R[j]->content_rating == NULL)
                {
        			arr[k] = R[j];
        			j++;
        		}
        		else if (strcmp(L[i]->content_rating, R[j]->content_rating)<0)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("budget", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->budget <= R[j]->budget)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("title_year", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->title_year <= R[j]->title_year)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("actor_2_facebook_likes", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->actor_2_facebook_likes <= R[j]->actor_2_facebook_likes)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("imbd_score", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->imbd_score <= R[j]->imbd_score)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
			}
        }

    	else if (strcmp("aspect_ratio", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->aspect_ratio <= R[j]->aspect_ratio)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       		 	k++;
			}
      	}

    	else if (strcmp("movie_facebook_likes", field) == 0)
        {
        	while (i < n1 && j < n2)
            {
        		if (L[i]->movie_facebook_likes <= R[j]->movie_facebook_likes)
                {
           			arr[k] = L[i];
            		i++;
        		}
        		else
                {
            		arr[k] = R[j];
        			j++;
        		}
       	 		k++;
            }
        }

        else 
        {
         printf("Error: Please enter an appropriate field to sort by.\n" );
         return;
        }
   

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}



/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(Movie* arr[], int l, int r, char* field){
    if (l < r){
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l+(r-l)/2;

        // Sort first and second halves
        mergeSort(arr, l, m, field);
        mergeSort(arr, m+1, r, field);

        merge(arr, l, m, r, field);
    }
}

/*

IMPORTANT:

MAKE SURE TO CONVERT -1 TO NULL WHEN PRINTING OUT THE FINAL SORTED DATA.

*/







