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
			// Create a path for each directory entry
			char *path = (char *)malloc(1024 * sizeof(char));
			strcpy(path, targetDir);
			strcat(path, "/");
			strcat(path, ent->d_name);

			// Try to open each path, and if successful, it's a directory
			if ((subDir = opendir(path)) != NULL)
			{	
				closedir(subDir);
				if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                	continue;
				}
				printf("found directory: %s \n", path);
				
				// Use the child process to traverse the found directory
				pid_t pid = fork();
				if (pid == 0)
				{
					traverseDir(path);
					return;
				}
			}
			// else if (csvfile) 
			// {

			// }
			//printf ("%s\n", ent->d_name);
			free(path);
		}
		return;
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