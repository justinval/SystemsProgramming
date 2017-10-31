#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include "sorter.h"
#include "mergesort.c"
#include <dirent.h>

void traverseDir (char *targetDir) 
{
	DIR *dir, *subDir;
	struct dirent *ent;

	if ((dir = opendir(targetDir)) != NULL) 
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) 
		{
			char *path = (char *)malloc(1024 * sizeof(char));
			strcpy(path, targetDir);
			strcat(path, "/");
			strcat(path, ent->d_name);
			if ((subDir = opendir(path)) != NULL)
			{	
				closedir(subDir);
				printf("found directory: %s \n", path);
				// Parent process
				// fork()
				// if ()
				// {
				// 	traverseDir(path);
				// }
			}
			// else if (csvfile) 
			// {

			// }
			//printf ("%s\n", ent->d_name);
			free(path);
		}
		closedir (dir);
	}
	else 
	{
	  /* could not open directory */
	  	perror ("");
		return;
	}
}

int main (int argc, char *argv[]) 
{
	char *targetDir = argv[1];
	traverseDir(targetDir);

}