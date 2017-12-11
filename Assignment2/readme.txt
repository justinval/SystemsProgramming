~ReadMe.txt for Project 2 by Justin Valeroso~

Design:
The design of this code is similar to the Project 1 structure. However, there are a few key differences. 
For instance, certain functionality from the file sortFile.c was moved into the sorter.c file. This
is so the sortFile can be in scope of the global variable masterMovieList. Also, the sortFile function 
was modified in order to output all Movie structs that it sorts into the masterMovieList. 
The masterMovieList is then sorted, traversed, and printed out into an output file at the given directory. 
If not output directory was specified, the program will spit out the file in the directory
that the program resides in. 

Another key difference is that the code was modified in order to accomodate threads. Basically,
the threads are spawned in the same places the processes were spawned. But in order for this 
to work, the parameters of the functions were modified so it could take a single input:
a struct that holds all the parameters of the function.

Difficulties:
The difficulties of this project stemmed from the way threads are implemented and the 
resources they share. In order to keep synchronization in line, the threads locked
the global variable masterMovieList. Another difficulty that was found while developing this code
was to keep track of the threads. Similar to the multiprocessing, a FILE * was passed through each
function in order to log the thread that was spawned to create it. At the end of the project,
the file was read in order to list the threads. 


