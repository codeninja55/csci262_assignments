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

#define PASSWORD_LEN 30
#define MD5_DIGEST_LENGTH 16
#define USED 1
#define NOT_USED 0

/* ########## STRUCT DEF ########## */
typedef struct PasswordRecord {
  char str_passwd[PASSWORD_LEN];
  unsigned char* hashed_digest;
  int used;
} PasswordRecord;

/* ########## GLOBAL VARS ########## */
PasswordRecord RAINBOW_TABLE[1000000];

/* ########## FUNCTION PROTOTYPES ########## */
void *ec_malloc(unsigned int size);
void fatal(char *message);
char* get_current_time();
unsigned char *md5_hash(unsigned char*);
void reduction();
void make_rainbow_value();

int main( int argc, const char* argv[] )
{
    char buffer[200];
    if ( argc == 2 ) strcpy(buffer, argv[1]);
    else {
        fprintf(stderr, "[Usage]: Rainbow <filename> \n");
        exit(1);
    }

    FILE *fd;
    char str_passwd[PASSWORD_LEN];
    int i, count;
    i = count = 0;

    if ( (fd = fopen(buffer, "r")) == NULL )  {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    while ( fgets(str_passwd, 20, fd) != NULL ) {
        // printf("%s\n", word);
        if ( ferror(fd) ) break;

        /*
         * 2. For each previously unused word W, first mark it as used and then carry out the following process.
         * a) Apply the hash function H to the word W to produce a hash value H(W), which we refer to as the current hash.
         * b) Apply the reduction function R to the current hash, which will give a different possible password
         *    which should be marked as used and then hashed. The resulting hash value is recorded as the current hash.
         * c) Repeat the previous step four times. You can deal with collisions if you like but are not required to.
         * d) Store the original word W and the final current hash as an entry in your entry table.
         * */
        PasswordRecord current_hash;

        strcpy(current_hash.str_passwd, str_passwd);
        current_hash.hashed_digest = md5_hash((unsigned char *) str_passwd);
        current_hash.used = USED;

        RAINBOW_TABLE[i++] = current_hash;

        count++;
    }

    fclose(fd);

    printf("Passwords read: %d\n", count);

    return 0;
}

void make_rainbow_value()
{

}

void reduction()
{
    // Apply the reduction function R to the current hash, which will give a different possible
    // password which should be marked as used and then hashed.
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

    // printf("MD5 Digest: ");
    // for (int i=0; i < MD5_DIGEST_LENGTH; i++) printf("%02x ",  md5_digest[i]);
    // printf("\n");

    return md5_digest;
}

/* ########## HELPER FUNCS ########## */

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