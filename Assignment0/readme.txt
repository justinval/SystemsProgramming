DOC:
The design of the sorter program is as follows: 

The "sorter.c" file contains the main program and a lot of the definitions of its helper functions.
The helper functions help to parse the data and print it in different formats for testing purposes.
The sorting algorithm is located within "mergesort.c". There's an include tag on the top of "sorter.c"
that allows the file to use "mergesort.c" functions. 

The main function of "sorter.c" works so that it loops around after the column row until the EOF. 
While looping, the program parses and tokenizes the line with the help of "strtokPlus". After the while
loop, the program then merges the list based off of the field parameter. Then, a helper function prints
the result in CSV format. 

Some difficulties that we ran into while coding this was that there were a lot of seg faults, so memory
had to be allocated delicately and precisely. The trailing whitespace also gave us difficulty with the
formating. Also, some of the abstract rules of the CSV file such as the quotes in the movie titles
were something we had to take into consideration.

EXTRA CREDIT (2):
A way to generalize a sorter given any CSV file is to parse the column row (which should be the first
row). This would serve as a way to create an array that holds (char **). A row would be created so that it 
would hold data for each column read. Then, the program would parse the rest of the data into char * 
normally.

