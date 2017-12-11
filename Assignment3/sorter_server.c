#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int n = -1;																// utility variable - for monitoring reading/writing from/to the socket
	char buffer[256];													// char array to store data going to and coming from the socket
	 
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
	int portNo = atoi(argv[2]);
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
    int clientSockFD = accept(sockfd, (struct sockaddr *) &clientAddressInfo, &clientLen);
	 
	// if the connection blew up for some reason, complain and exit
    if (clientSockFD < 0) 
	{
        printf("Error accepting client socket. \n");
        exit(1);
	}
	
	// Instantiate buffer and zero it out
	char buffer[256];
    bzero(buffer, 256);
	
	// Read message from client socket into buffer
    n = read(clientSockFD, buffer, 255);
	
	// if the read from the client blew up, complain and exit
    if (n < 0)
	{
		printf("Error reading from socket. \n");
		exit(1);
	}
	
    printf("Here is the message: %s\n", buffer);
	return 0; 
}