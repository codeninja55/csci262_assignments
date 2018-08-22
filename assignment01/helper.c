/*********************************************************************
* Title: Helper Utility Functions
* File: helper.c - helper source file for utility functions.
* Author: Dinh Che (codeninja55) andrew at codeninja.me
* Last modified: 2018.08.19
*********************************************************************/

#include <bits/types/time_t.h>
#include <time.h>
#include <utime.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// A function to return the current time
/* Title: localtime reference
 * Availability: http://www.cplusplus.com/reference/ctime/localtime/
 * */
char* get_current_time()
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return asctime(timeinfo);
}

/* The functions below are referenced to:
 * Title: Hacking, 2nd edition
 * Author(s): Jon Erickson
 * Date: 2008
 * */

// A function to display an error message and then exit
void fatal(char *message)
{
    char error_message[200];

    strcpy(error_message, "[DEBUG - Fatal Error]: ");
    strncat(error_message, message, 83);
    perror(error_message);
    exit(-1);
}

// An error-checked malloc() wrapper function
void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(size);
    if(ptr == NULL)
        fatal("in ec_malloc() on memory allocation");
    return ptr;
}
