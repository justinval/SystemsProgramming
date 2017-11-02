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
	printf("%d \n", getpid());

	fork();
	printf("%d \n", getpid());
}