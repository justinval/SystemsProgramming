ReadMe

The design of this project heavily relied on the design of project 0. We modularized the code in 
project 0 so that the main parts that would sort out a file would be a function called sortFile. 
This method would take in a list of parameters that would be able to sort a file based off of the 
path given and output everything into a file. 

This function was then used within a recursive function called sortDir that would open a directory
based off of the input given by the user. If a directory was found, the process was fork()ed and
the child process recursively called the function sortDir. Similarly, if a CSV file was found
the process was fork()ed and called the sortFile function. Everytime a process was fork()ed, 
it was logged into a text file that kept track of the processes. 

This list of processes was then printed out at the end of the program. A problem that we ran into 
was that the process list had duplicates of PIDs. We believe this is because when one child process
ended, the others that spawned took the PID of the child that died. 

