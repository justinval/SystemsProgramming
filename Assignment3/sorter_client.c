#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/time.h>

void *sender(void *path);
void *searchDirs(void *path);
void merge();
int newSocket();
void getCol();
void sendCol();

#include "sorter_client.h"

#define min(a, b) ((a) < (b) ? (a) : (b))


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

char sortedCol[100];
char outputFile[1000];

char coltype;
int sortCode;

char dirPaths[1000][300];
int numPaths = 0;

char domain[100];
int port;
int maxSocket = 1;

sem_t semaphore;
int sock;
int newSocket(){



    struct sockaddr_in address;
    struct hostent *server;


    sem_wait(&semaphore);


    server = gethostbyname(domain);

    if (server == NULL) {
        printf("ERROR! Host not found.\n");
        exit(0);
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    bcopy((char *)server->h_addr, (char *)&address.sin_addr.s_addr, server->h_length);

    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0) {
        printf("Socket error!\n");

        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("Connection error!\n");
        close(sock);
        sem_post(&semaphore);

        exit(EXIT_FAILURE);
    }

    return sock;
}

void *sender(void *path){

    char *filename = path;

    FILE *fp = fopen(filename, "r");
    char line[1000];

    fgets(line, 1000, fp);
    fclose(fp);
    int numOfCommas = 0;

    int i;
    for (i = 0; i < strlen(line); i++)

    	if (line[i] == ',')
            numOfCommas++;

    if (numOfCommas != 27)
        return NULL;


    int newFile = open(filename, O_RDONLY);
    
    struct stat stats;
    fstat(newFile, &stats);

    char fbuff[255];
   
    sprintf(fbuff, "%d",(int) stats.st_size);

    send(sock, fbuff, sizeof(fbuff), 0);

    int isSent;
    off_t offset = 0;
    int left = stats.st_size;
    char buffer[255];

    read(sock, buffer, sizeof(buffer));
    printf("%s \n", buffer);

    while (left > 0 && (isSent = sendfile(sock, newFile, &offset, min(left, BUFSIZ))) > 0) {
        left = left - isSent;
    }

    sem_post(&semaphore);
    
    close(newFile);

    return NULL;
}

void *searchDirs(void *path){

    char *newPath = path;
    DIR *newDir = opendir(newPath);

    pthread_t currtid;
    pthread_t waitpid[1000];

    int threads = 0;
    int count = 0;


    struct dirent *newEntry;

    if (newDir == NULL) {
        printf("ERROR! Failed to read directory!\n");

        return NULL;
    }

    int i;
    while ((newEntry = readdir(newDir)) != NULL){

    	if (strcmp(newEntry->d_name, ".") == 0 || strcmp(newEntry->d_name, "..") == 0)
            continue;

    	pthread_mutex_lock(&lock);

    	count = numPaths++ % 1000;

    	pthread_mutex_unlock(&lock);

    	sprintf(dirPaths[count], "%s/%s", newPath, newEntry->d_name);

        if (newEntry->d_type == DT_DIR) {
            pthread_create(&currtid, NULL, (void *)&searchDirs, (void *)&dirPaths[count]);
        } else {

        	if (strlen(dirPaths[count]) < 4 || strcmp(dirPaths[count] + strlen(dirPaths[count]) - 4, ".csv") != 0 || strstr(dirPaths[count], "-sorted-"))
                continue;

        	pthread_create(&currtid, NULL, (void *)&sender, (void *)&dirPaths[count]);
        }

        waitpid[threads++] = currtid;

        if (threads == 64) {

        	for (i = 0; i < threads; i++) {
                pthread_join(waitpid[i], NULL);
            }

        	threads = 0;
        }
    }

    for (i = 0; i < threads; i++) {
        pthread_join(waitpid[i], NULL);
    }

    closedir(newDir);

    return NULL;
}

void sendCol(){

    char protocol[4];

    protocol[0] = '>';
    protocol[1] = coltype;
    protocol[2] = sortCode;
    protocol[3] = '\0';

    send(sock, protocol, sizeof(protocol), 0);

    sem_post(&semaphore);
}

void merge(){

    char protocol[2];

    protocol[0] = '<';
    protocol[1] = '\0';
    send(sock, protocol, sizeof(protocol), 0);
    char buffer[10000] = "";

    recv(sock, buffer, sizeof(buffer), 0);
    send(sock, protocol, sizeof(protocol), 0);

    int left = atoi(buffer);
    char *file = (char *)malloc(left);
    *file = '\0';

    ssize_t len;
    while (left > 0) {
        len = recv(sock, buffer, min(left, BUFSIZ), 0);
        printf("Downloading file \n");
    	strncat(file, buffer, min(left, len));
    	left = left - len;
    }

    FILE *output = fopen(outputFile, "w");
    fprintf(output, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes\n%s", file);
    fclose(output);

    close(sock);
    sem_post(&semaphore);

}
int main(int argc, char **argv){

	// default values
    char path[500] = ".";
    char outpath[500] = ".";
    strcpy(sortedCol, "director_name");

    // check input
    if (argc < 7) {
        printf("Incorrect number of arguments\n");
        return 0;
    }

    int x = 1;
    while (x < argc - 1) {
        if (*(argv[x] + 1) == 'c')
            strcpy(sortedCol, argv[x + 1]);
        else if (*(argv[x] + 1) == 'd')
            strcpy(path, argv[x + 1]);
        else if (*(argv[x] + 1) == 'o')
            strcpy(outpath, argv[x + 1]);
        else if (*(argv[x] + 1) == 'h')
            strcpy(domain, argv[x + 1]);
        else if (*(argv[x] + 1) == 'p')
            port = atoi(argv[x + 1]);
        else if (*(argv[x] + 1) == 's')
            maxSocket = atoi(argv[x + 1]);
        x += 2;
    }

    sem_init(&semaphore, 0, maxSocket);

    sock = newSocket();
    getCol();
    sendCol();

    sprintf(outputFile, "%s/AllFiles-sorted-%s.csv", outpath, sortedCol);

    searchDirs(path);
    merge();

    pthread_mutex_destroy(&lock);

    return 0;
}

void getCol(){

	// 's' for string, 'n' for numerical
    if (strcmp(sortedCol, "color") == 0) {
        sortCode = 0;
        coltype = 's';
    } else if (strcmp(sortedCol, "director_name") == 0) {
        sortCode = 1;
        coltype = 's';
    } else if (strcmp(sortedCol, "num_critic_for_reviews") == 0) {
        sortCode = 2;
        coltype = 'n';
    } else if (strcmp(sortedCol, "duration") == 0) {
        sortCode = 3;
        coltype = 'n';
    } else if (strcmp(sortedCol, "director_facebook_likes") == 0) {
        sortCode = 4;
        coltype = 'n';
    } else if (strcmp(sortedCol, "actor_3_facebook_likes") == 0) {
        sortCode = 5;
        coltype = 'n';
    } else if (strcmp(sortedCol, "actor_2_name") == 0) {
        sortCode = 6;
        coltype = 's';
    } else if (strcmp(sortedCol, "actor_1_facebook_likes") == 0) {
        sortCode = 7;
        coltype = 'n';
    } else if (strcmp(sortedCol, "gross") == 0) {
        sortCode = 8;
        coltype = 's';
    } else if (strcmp(sortedCol, "genres") == 0) {
        sortCode = 9;
        coltype = 's';
    } else if (strcmp(sortedCol, "actor_1_name") == 0) {
        sortCode = 10;
        coltype = 's';
    } else if (strcmp(sortedCol, "movie_title") == 0) {
        sortCode = 11;
        coltype = 's';
    } else if (strcmp(sortedCol, "num_voted_users") == 0) {
        sortCode = 12;
        coltype = 'n';
    } else if (strcmp(sortedCol, "cast_total_facebook_likes") == 0) {
        sortCode = 13;
        coltype = 'n';
    } else if (strcmp(sortedCol, "actor_3_name") == 0) {
        sortCode = 14;
        coltype = 's';
    } else if (strcmp(sortedCol, "facenumber_in_poster") == 0) {
        sortCode = 15;
        coltype = 'n';
    } else if (strcmp(sortedCol, "plot_keywords") == 0) {
        sortCode = 16;
        coltype = 's';
    } else if (strcmp(sortedCol, "movie_imdb_link") == 0) {
        sortCode = 17;
        coltype = 's';
    } else if (strcmp(sortedCol, "num_user_for_reviews") == 0) {
        sortCode = 18;
        coltype = 'n';
    } else if (strcmp(sortedCol, "language") == 0) {
        sortCode = 19;
        coltype = 's';
    } else if (strcmp(sortedCol, "country") == 0) {
        sortCode = 20;
        coltype = 's';
    } else if (strcmp(sortedCol, "content_rating") == 0) {
        sortCode = 21;
        coltype = 's';
    } else if (strcmp(sortedCol, "budget") == 0) {
        sortCode = 22;
        coltype = 'n';
    } else if (strcmp(sortedCol, "title_year") == 0) {
        sortCode = 23;
        coltype = 'n';
    } else if (strcmp(sortedCol, "actor_2_facebook_likes") == 0) {
        sortCode = 24;
        coltype = 'n';
    } else if (strcmp(sortedCol, "imdb_score") == 0) {
        sortCode = 25;
        coltype = 'n';
    } else if (strcmp(sortedCol, "aspect_ratio") == 0) {
        sortCode = 26;
        coltype = 'n';
    } else if (strcmp(sortedCol, "movie_facebook_likes") == 0) {
        sortCode = 27;
        coltype = 'n';
    } else {
        exit(1);
    }
}
