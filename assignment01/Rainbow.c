/*********************************************************************
 * CSCI262 - Assignment 01
 * Rainbow.c - main() for assignment 01 execution
 * Description: The program is used to find pre-images for given hash values.
 * Author: Dinh Che better known as codeninja55 - dbac496 at uowmail.edu.au || andrew at codeninja55.me
 * Last modified: 2018.08.16
 *********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "md5.h"

#define MD5_DIGEST_LENGTH 16
#define USED 1
#define NOT_USED 0

/* ########## TYPEDEF ########## */
// typedef struct Hash Hash;

/* ########## STRUCT DEF ########## */
typedef struct Hash {
  unsigned char* md5_digest;
  int used;
} Hash;

/* ########## FUNCTION PROTOTYPES ########## */
void *ec_malloc(unsigned int size);
void fatal(char *message);
char* get_current_time();
unsigned char *md5_hash(unsigned char*);


int main( int argc, const char* argv[] )
{
    char buffer[200];
    if ( argc == 2 ) strcpy(buffer, argv[1]);
    else {
        fprintf(stderr, "[Usage]: Rainbow <filename> \n");
        exit(1);
    }

    FILE *fd;
    char word[60];
    unsigned char *current_hash;
    int count = 0;

    if ( (fd = fopen(buffer, "r")) == NULL )  {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    while ( fgets(word, 20, fd) != NULL ) {
        // printf("%s\n", word);
        if ( ferror(fd) ) break;

        current_hash = (unsigned char *) ec_malloc(MD5_DIGEST_LENGTH);
        current_hash = md5_hash((unsigned char *) word);

        Hash hash = { current_hash, USED };

        count++;
        free(current_hash);
    }

    fclose(fd);

    printf("Passwords read: %d\n", count);

    return 0;
}

// A hashing function to create MD5 Digest from a string passed in.
unsigned char *md5_hash(unsigned char * str)
{
    unsigned char *md5_digest;
    md5_digest = (unsigned char *) ec_malloc(MD5_DIGEST_LENGTH);

    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, str, strlen(str));
    MD5_Final(md5_digest, &md5_ctx);

    printf("MD5 Digest: ");
    for (int i=0; i < MD5_DIGEST_LENGTH; i++) printf("%02x ",  md5_digest[i]);
    printf("\n");

    return md5_digest;
}

void generate_rainbow(char * word)
{

}

/* ########## HELPER FUNCS ########## */

// A function to return the current time
/* Title: localtime reference
 * Author(s):
 * Date:
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

// A function to display an error message and then exit
void fatal(char *message)
{
    char error_message[200];

    strcpy(error_message, "[!!] Fatal Error ");
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