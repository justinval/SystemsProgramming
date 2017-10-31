#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include "sorter.h"
#include "mergesort.c"
#include <dirent.h>

int main (int argc, char *argv[]) 
{
	char *targetDir = argv[1];
	traverseDir(targetDir);

}

void traverseDir (char *targetDir) 
{
	char *path;
	DIR *dir, *subDir;
	struct dirent *ent;
	if ((dir = opendir(targetDir)) != NULL) 
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) 
		{
			if ((subDir = opendir(ent->d_name)) != NULL)
			{	
				close(subdir);
				strcpy(path, targetDir)
				strcat(path, "/");
				strcat(path, ent->d_name);
				printf("%s", path);
				// fork()
				// if ()
				// {
				// 	traverseDir(path);
				// }
			}
			// else if (csvfile) 
			// {

			// }
			printf ("%s\n", ent->d_name);
		}
		closedir (dir);
	}
	else 
	{
	  /* could not open directory */
	  	perror ("");
		return EXIT_FAILURE;
	}
}