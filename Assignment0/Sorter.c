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
		//Check to see if 1st param is "-c"
		if (strcmp(argv[1], "-c") != 0) {
			printf("Can only sort by column. Please try again. \n");
			return 0;
		}

		//Read format line of CSV file into str[100]
		char str[2000];
		scanf("%s", str);

		//Loops until scanf is unsuccessful/reaches EOF
		while (scanf("%s", str) > 0)
		{
			printf("%s \n", str);
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