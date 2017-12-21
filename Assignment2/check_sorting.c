#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define STRLEN 3000
#define ARRAYLEN 30
#define INPUTCOLUME 28
#define LINENUM 25000

typedef struct
{
    char *token[ARRAYLEN];

} Row;

const char *header[] = {"color", "director_name", "num_critic_for_reviews", "duration", "director_facebook_likes", "actor_3_facebook_likes", "actor_2_name", "actor_1_facebook_likes", "gross", "genres", "actor_1_name", "movie_title", "num_voted_users", "cast_total_facebook_likes", "actor_3_name", "facenumber_in_poster", "plot_keywords", "movie_imdb_link", "num_user_for_reviews", "language", "country", "content_rating", "budget", "title_year", "actor_2_facebook_likes", "imdb_score", "aspect_ratio", "movie_facebook_likes"};
static int sortIndex;

void checkItem(Row row[], unsigned long lineNum)
{
    unsigned long i = 0;
    Row*a=NULL;
    Row*b=NULL;
    for (i = 0; i < lineNum - 1; i++)
    {
        a=&row[i];
        b=&row[i+1];

        int elemTypea = checkType(a->token[sortIndex]);
        int elemTypeb = checkType(b->token[sortIndex]);

        //if (elemTypea!=elemTypeb){
        //    printf("sorting element is in different type lineNum (%d,%d), values (%s,%s)\n",
        //    i,i+1,row[i]->token[sortIndex],row[i+1]->token[sortIndex]);
        //    exit(EXIT_FAILURE);
        //}

        //empty value return -1

        //integer return2

        //float return1

        //string return0

        if (elemTypea == -1 && elemTypeb != -1)
        {
            elemTypea = elemTypeb;
        }

        if (elemTypeb == -1 && elemTypea != -1)
        {
            elemTypeb = elemTypea;
        }
        if (elemTypeb == -1 && elemTypea == -1)
        {
            elemTypea = 0;
            elemTypeb = 0;
        }

        if (elemTypea == 0)
        {
            if (strcmp(a->token[sortIndex], b->token[sortIndex]) > 0)
            {
                exit(EXIT_FAILURE);
            }
        }
        else if (elemTypea == 2)
        {
            int Inta = atof(a->token[sortIndex]);
            int Intb = atof(b->token[sortIndex]);
            if (Inta > Intb)
            {
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            float fa = atof(a->token[sortIndex]);
            float fb = atof(b->token[sortIndex]);
            if (fa > fb)
            {
                exit(EXIT_FAILURE);
            }
        }
    }
}

int containComma(char *str)
{
    int len = strlen(str);
    int i = 0;
    for (i = 0; i < len; i++)
    {
        if (str[i] == ',')
        {
            return 1;
        }
    }
    return 0;
}

//assume all the input is valid
int checkType(char str[])
{

    int len = strlen(str);
    char *strtemp = str;
    int i = 0;

    while (*strtemp == '\0' || *strtemp == 13 || *strtemp == 10)
    {
        return -1;
    }

    while (*strtemp == ' ')
    {
        strtemp++;
    }

    //special input: 50 Cent...

    if (*strtemp >= '0' && *strtemp <= '9')
    {

        char *strfilter = strtemp;
        // \n 10 \r 13
        while (*strfilter != '\0' && *strfilter != 13 && *strfilter != 10 )
        {
            if ((*strfilter) < '0' || (*strfilter) > '9')
            {
                if ((*strfilter) == '.' || (*strfilter) == ' ')
                {
                    strfilter++;
                    continue;
                }
                else
                {
                    return 0;
                }
            }
            strfilter++;
        }

        while (*strtemp != '\0' && *strfilter != 13 && *strfilter != 10)
        {
            if (*strtemp == '.')
            {
                return 1;
            }
            strtemp++;
        }
        return 2;
    }

    return 0;

    //empty value return -1

    //integer retur2

    //float return1

    //string return0
}
//TODO consider the output like "" , there is a blank between the " and ,
void split(char *returnstr[], char *inputstr, char seprator)
{
    if (inputstr == NULL)
    {
        exit(EXIT_FAILURE);
    }

    //printf("inpit (%s)\n",inputstr);
    int len = strlen(inputstr);
    //int len=INPUTCOLUME;
    int lindex = 0;
    int rindex = 0;
    int flag = 0;
    int num = 0;
    char *temp = inputstr;
    for (rindex = 0; rindex <= len; rindex++, temp++)
    {

        if (rindex == len)
        {
            returnstr[num] = (char *)malloc(rindex - lindex + 2);
            if (returnstr[num] == NULL)
            {
                exit(EXIT_FAILURE);
            }
            memcpy(returnstr[num], inputstr + lindex, rindex - lindex);
            //the last value is '\n' for this case
            char *last = returnstr[num] + rindex - lindex - 1;
            if (*last == '\n')
            {
                //TODO, bug here, extra blank after " like ""  ,
                if (*(last - 1) == '"')
                {
                    *(returnstr[num] + rindex - lindex - 2) = '\0';
                }
                else
                {
                    *(returnstr[num] + rindex - lindex - 1) = '\0';
                }
            }
            else
            {
                *(returnstr[num] + rindex - lindex) = '\0';
            }

            //printf("token:(%s)\n", returnstr[num]);
            num++;
            break;
        }
        if (*temp == '"' && flag == 0)
        {
            lindex = rindex + 1;
            flag = 1;
            continue;
        }
        if (*temp == ',' && *(temp - 1) == '"' && flag == 1)
        {
            returnstr[num] = (char *)malloc(rindex - lindex + 2);
            if (returnstr[num] == NULL)
            {
                exit(EXIT_FAILURE);
            }
            memcpy(returnstr[num], inputstr + lindex, rindex - lindex - 1);
            *(returnstr[num] + rindex - lindex) = '\0';
            flag = 0;
            lindex = rindex + 1;
            num++;
            continue;
        }

        if (*temp == ',' && flag == 0)
        {
            //printf("debug\n");
            returnstr[num] = (char *)malloc(rindex - lindex + 2);
            if (returnstr[num] == NULL)
            {
                exit(EXIT_FAILURE);
            }
            memcpy(returnstr[num], inputstr + lindex, rindex - lindex);
            *(returnstr[num] + rindex - lindex + 1) = '\0';
            //printf("token:(%s)\n", returnstr[num]);
            lindex = rindex + 1;
            num++;
        }
    }
}

int checkSortIndex(char str[])
{
    int i = 0;
    //printf("get sort item %s\n",str);
    //printf("%s\n",header[1]);
    //printf("%d\n",strcmp(str,header[1]));

    for (i = 0; i < INPUTCOLUME; i++)
    {
        //printf("%s %d\n",header[i],i);
        if (strcmp(str, header[i]) == 0)
        {
            return i;
        }
    }

    return -1;
}

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "-c") != 0)
    {
        exit(EXIT_FAILURE);
    }

    //get sort index

    sortIndex = checkSortIndex(argv[2]);
    if (sortIndex == -1)
    {
        exit(EXIT_FAILURE);
    }


    char input[STRLEN];
    int index = 0;
    char *line[ARRAYLEN];
    Row row[LINENUM];
    char *token;
    //FILE *file;
    //file = fopen("movie_metadata_dname.csv", "at+");
    
    
    //get first line and process the input argument  //Gang: this line is the heading
    if (fgets(input, STRLEN, stdin) != NULL)
    {

    }

    unsigned long lineNum = 0;
    while (fgets(input, STRLEN, stdin) != NULL)
    {
        int i = 0;
        for (i = 0; i < ARRAYLEN; i++)
        {
            line[i] = NULL;
        }


        split(line, input, ',');

        for (i = 0; i < INPUTCOLUME; i++)
        {
            row[lineNum].token[i] = line[i];
        }
        lineNum++;
    }
    //fclose(file);
    checkItem(row, lineNum);
    
    //Gang: if all movies are correctly sorted, return 0 
    return 0;
}
