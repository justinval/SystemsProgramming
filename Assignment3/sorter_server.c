#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "sorter_server.h"
#include "mergesort.c"
#define MAX 1000000
#define min(a, b) ((a) < (b) ? (a) : (b))

int portNo;
int main(int argc, char *argv[])
{	 
	// Check to see if the user input the corret number of parameters
    if (argc < 3)
	{
        printf("Not enough params, please try again. \n");
        exit(1);
    }
	 
	// Check to see if the user set up the flag correctly
	if (strcmp(argv[1], "-p") != 0)
	{
		printf("Wrong flag, please try again. \n");
		exit(1);
	}

	// Get portno from user and check if it's a vald port number 
	portNo = atoi(argv[2]);
	if (portNo < 0)
	{
		printf("Invalid port number, please try again. \n");
		exit(1);
	}


	// Create socket and check if it's a working socket
	int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockFD < 0)
	{
       error("Error creating socket. \n");
       exit(1);
	}

	// Create sockaddr_in struct and initialize
	struct sockaddr_in serverAddressInfo;
	bzero((char *) &serverAddressInfo, sizeof(serverAddressInfo));
	serverAddressInfo.sin_port = htons(portNo);
    serverAddressInfo.sin_family = AF_INET;
    serverAddressInfo.sin_addr.s_addr = INADDR_ANY;
     
    // Try to bind server socket
    if (bind(sockFD, (struct sockaddr *) &serverAddressInfo, sizeof(serverAddressInfo)) < 0)
	{
		printf("Error binding socket. \n");
		exit(1);
	}
			  
	// Make the server socket listen for connections
    listen(sockFD, 5);
	
	// Determine the size of a clientAddressInfo struct
	struct sockaddr_in clientAddressInfo;
    int clientLen = sizeof(clientAddressInfo);
	
	// Create a client socket when accepting
	int clientSockFD;
	pthread_t dtid;
    while(clientSockFD = accept(sockFD, (struct sockaddr *) &clientAddressInfo, &clientLen)){
		// if the connection blew up for some reason, complain and exit
	    if (clientSockFD < 0) 
		{
	        printf("Error accepting client socket. \n");
	        exit(1);
		}    	
		printf("Connected w/ a client! \n");
    	// TODO: When a thread is accepted, spawn a thread
    	pthread_create(&dtid, NULL, handleClient, (void *)&clientSockFD);
    }
	
	return 0; 
}

// TODO: create a method that handles connections
void *handleClient (void *args) 
{
	int *clientSockPtr = (int *)args;
	int clientSockFD = *clientSockPtr;

	// Instantiate buffer and zero it out
	char protocolBuffer[10];
	bzero (protocolBuffer, 10);
	
	// Get the column name from client
	read((int)clientSockFD, protocolBuffer, sizeof(protocolBuffer));
	char *column = getColString(protocolBuffer[2]);

	// Instantiate buffer to read data
	char buffer[10000];
	bzero(buffer, 10000);

	// Read all of the files it sends over and parse it into the masterMovieList
	Movie **masterMovieList = (Movie **)malloc(MAX * sizeof(Movie *));
	int masterIndex = 0;
	while (read(clientSockFD, buffer, sizeof(buffer)))
	{	
		// Check to see if the client wants the result
		if (buffer[0] == '<')
		{
			// Sort the masterMovieList and print it out to masterTempFile.txt
			mergeSort(masterMovieList, 0, masterIndex-1, column);
			printAllCSVSingleFile (masterMovieList, "masterTempFile.txt");
				
			// Send the masterTempFile's size
			FILE *file = fopen("masterTempFile.txt", "r");
			struct stat st;
			stat("masterTempFile.txt", &st);
			char fileLen[50];
			sprintf(fileLen, "%d", st.st_size);			
			write(clientSockFD, fileLen, sizeof(fileLen));
			read(clientSockFD, buffer, sizeof(buffer));
			printf("test \n");
			// Send the masterTempFile 
			int bytesToSend = st.st_size, bytesSent;
			off_t offset;
			while (bytesToSend > 0 && (bytesSent = sendfile(clientSockFD, file, &offset, min(bytesToSend, BUFSIZ))) > 0)
			{
				bytesToSend -= bytesSent;
			}
			return NULL;
		}

		// Else, grab data from client
		else 
		{
			
			// Get the incoming file length
			//read(clientSockFD, buffer, sizeof(buffer));
			int bytesToRead = atoi(buffer);
			char *serverMessage = "Server received file length.";
			write(clientSockFD, serverMessage, strlen(serverMessage));

			// Read bytes sent in
			int bytesReceived;
			FILE *tempFile = fopen("tempFile.txt", "w");
			while (bytesToRead > 0)
			{
				bzero(buffer, 10000);
				bytesReceived = read(clientSockFD, buffer, min(bytesToRead, BUFSIZ));
				fprintf(tempFile, "%s", buffer);
				bytesToRead -= bytesReceived;
			}
			fclose(tempFile);

			// Parse the data 
			Movie **movieList = sortFile("tempFile.txt", column);	
			int i = 0;
			while (movieList[i] != NULL)
			{
				masterMovieList[masterIndex] = movieList[i];
				masterIndex++;
				i++;
			}					
		}
	}
	return NULL;
}

char *getColString (char c)
{
	switch (c) {
		case 0:
			return "color";
		case 1:
			return "director_name";
		case 2:
			return "num_critic_for_reviews";
		case 3:
			return "duration";
		case 4:
			return "director_facebook_likes";
		case 5: 
			return "actor_3_facebook_likes";
		case 6:
			return "actor_2_name";
		case 7:
			return "actor_1_facebook_likes";
		case 8:
			return "gross";
		case 9:
			return "genres";
		case 10:
			return "actor_1_name";
		case 11:
			return "movie_title";
		case 12:
			return "num_voted_users";
		case 13:
			return "cast_total_facebook_likes";
		case 14:
			return "actor_3_name";
		case 15:
			return "facenumber_in_poster";
		case 16:
			return "plot_keywords";
		case 17:
			return "movie_imdb_link";
		case 18:
			return "num_user_for_reviews";
		case 19:
			return "language";
		case 20:
			return "country";
		case 21:
			return "content_rating";
		case 22:
			return "budget";
		case 23:
			return "title_year";
		case 24: 
			return "actor_2_facebook_likes";
		case 25:
			return "imdb_score";
		case 26:
			return "aspect_ratio";
		case 27:
			return "movie_facebook_likes";	
		default:
			exit(1);
	}
}

//Read format line of CSV file into str[100]
Movie **sortFile(char *filePath, char *sortBy)
{
	FILE *file = fopen(filePath, "r");

    char line[1000];

    //reading the first row of column names
    fgets(line, 1000, file);
		
	Movie *ptr;
	Movie **movieList = (Movie **)malloc(10000 * sizeof(Movie *));
	int numOfMovies = 0;


	//Loops until scanf is unsuccessful/reaches EOF
	while (fgets(line, 1000, file))
	{
		ptr = (Movie *)malloc(sizeof(Movie));
		parseMovie(line, ptr);					
		movieList[numOfMovies] = ptr;		
		numOfMovies++;
	}

    fclose(file);
	
	//Mergesort list based off of field
	mergeSort(movieList, 0, numOfMovies-1, sortBy);

	return movieList;
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
		token = (char *)malloc((index * sizeof(char)) + 1);
		memcpy(token, str + 1, index);
		
		// +2 b/c of quote and comma
		strcpy(str, temp + 2);

		token[index] = '\0';
		free(temp);
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

void printAllCSVSingleFile (Movie **masterMovieList, char *outputPath)
{
	FILE *outputFile;
	outputFile = fopen(outputPath, "w");

	int i = 0;
	while (masterMovieList[i] != NULL)
	{
		if (strchr(masterMovieList[i]->movie_title, ',') != NULL)
		{
			fprintf(outputFile, "%s,%s,%i,%i,%i,%i,%s,%i,%i,%s,%s,\"%s\",%i,%i,%s,%i,%s,%s,%i,%s,%s,%s,%i,%i,%i,%f,%f,%i\n",
				masterMovieList[i]->color, masterMovieList[i]->director_name, masterMovieList[i]->num_critic_for_reviews, masterMovieList[i]->duration, 
				masterMovieList[i]->director_facebook_likes, masterMovieList[i]->actor_3_facebook_likes, masterMovieList[i]->actor_2_name,
				masterMovieList[i]->actor_1_facecbook_likes, masterMovieList[i]->gross, masterMovieList[i]->genres, masterMovieList[i]->actor_1_name, 
				masterMovieList[i]->movie_title, masterMovieList[i]->num_voted_users, masterMovieList[i]->cast_total_facebook_likes, 
				masterMovieList[i]->actor_3_name, masterMovieList[i]->facenumber_in_poster, masterMovieList[i]->plot_keywords, 
				masterMovieList[i]->movie_imbd_link, masterMovieList[i]->num_user_for_reviews, masterMovieList[i]->language, 
				masterMovieList[i]->country, masterMovieList[i]->content_rating, masterMovieList[i]->budget, masterMovieList[i]->title_year, 
				masterMovieList[i]->actor_2_facebook_likes, masterMovieList[i]->imbd_score, masterMovieList[i]->aspect_ratio, 
				masterMovieList[i]->movie_facebook_likes);
		i++;
		}

		else {
			fprintf(outputFile, "%s,%s,%i,%i,%i,%i,%s,%i,%i,%s,%s,%s,%i,%i,%s,%i,%s,%s,%i,%s,%s,%s,%i,%i,%i,%f,%f,%i\n",
				masterMovieList[i]->color, masterMovieList[i]->director_name, masterMovieList[i]->num_critic_for_reviews, masterMovieList[i]->duration, 
				masterMovieList[i]->director_facebook_likes, masterMovieList[i]->actor_3_facebook_likes, masterMovieList[i]->actor_2_name,
				masterMovieList[i]->actor_1_facecbook_likes, masterMovieList[i]->gross, masterMovieList[i]->genres, masterMovieList[i]->actor_1_name, 
				masterMovieList[i]->movie_title, masterMovieList[i]->num_voted_users, masterMovieList[i]->cast_total_facebook_likes, 
				masterMovieList[i]->actor_3_name, masterMovieList[i]->facenumber_in_poster, masterMovieList[i]->plot_keywords, 
				masterMovieList[i]->movie_imbd_link, masterMovieList[i]->num_user_for_reviews, masterMovieList[i]->language, 
				masterMovieList[i]->country, masterMovieList[i]->content_rating, masterMovieList[i]->budget, masterMovieList[i]->title_year, 
				masterMovieList[i]->actor_2_facebook_likes, masterMovieList[i]->imbd_score, masterMovieList[i]->aspect_ratio, 
				masterMovieList[i]->movie_facebook_likes);
			i++;
		}
	}
}