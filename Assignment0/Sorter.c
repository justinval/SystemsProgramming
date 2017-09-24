#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Sorter.h"

int main (int argc, char *argv[]) 
{
	//Check to see if there is the proper number of params
	if (argc == 3) 
	{	
		char *sortByParam = argv[1];

		//Check to see if 1st param is "-c"
		if (strcmp(sortByParam, "-c") != 0) {
			printf("Can only sort by column. Please try again.");
			return 0;
		}
    }

    //If the user didn't have the proper number of params
    else
    {
    	printf("Invalid number of inputs. Please try again.");
    	return 0;
    }
}