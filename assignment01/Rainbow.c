/*********************************************************************
 * CSCI262 - Assignment 01
 * Rainbow.c - main() for assignment 01 execution
 * Description: The program is used to find pre-images for given password string values.
 * Author: Dinh Che better known as codeninja55 || andrew at codeninja55.me
 * UOW Details: dbac496 || dbac496 at uowmail.edu.au
 * Last modified: 2018.08.16
 *********************************************************************/

#include <assert.h>
#include <math.h>
#include <openssl/md5.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "avltree.h"
#include "helper.h"

#define DEBUG true
#define USED 1
// #define NOT_USED 0

/* ########## GLOBAL VARS ########## */
NODE *RAINBOW_TREE;

/* ########## FUNCTION PROTOTYPES ########## */
unsigned char *generate_final_hash(const char *);
unsigned int *reduction(int, const unsigned char *);
unsigned char *md5_hash(const char*);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "KRUnspecifiedParameters"

int main( int argc, const char* argv[] )
{
    char buffer[200];
    if ( argc == 2 ) strcpy(buffer, argv[1]);
    else {
        fprintf(stderr, "Usage: Rainbow <filename> \n");
        exit(1);
    }

    FILE *fd;
    char str_passwd[PASSWORD_LEN];
    int count;
    count = 0;

    if ( (fd = fopen(buffer, "r")) == NULL )  {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    while ( fscanf(fd, "%s", str_passwd) == 1 ) {
        if ( ferror(fd) ) break;

        if ( DEBUG ) printf("String Password Read: %s\n", str_passwd);
        PasswordRecord password_rec;

        strcpy(password_rec.str_passwd, str_passwd);
        password_rec.used = USED;
        password_rec.hashed_digest = generate_final_hash((const char *) str_passwd);

        RAINBOW_TREE = insert(RAINBOW_TREE, str_passwd, password_rec);
        count++;
    }

    fclose(fd);

    printf("Passwords read: %d\n", count);

    in_order_sort(RAINBOW_TREE);

    return 0;
}
#pragma clang diagnostic pop

unsigned char *generate_final_hash(const char *value)
{
    unsigned char *current_hash;
    unsigned int *reduced_hash;

    /* FIRST HASH - REDUCE */
    current_hash = md5_hash(value);
    reduced_hash = reduction(10, current_hash);
    /* SECOND HASH - REDUCE */
    current_hash = md5_hash((const char *) reduced_hash);
    reduced_hash = reduction(8, current_hash);
    /* THIRD HASH - REDUCE */
    current_hash = md5_hash((const char *) reduced_hash);
    reduced_hash = reduction(4, current_hash);
    /* FOURTH HASH - REDUCE */
    current_hash = md5_hash((const char *) reduced_hash);
    reduced_hash = reduction(2, current_hash);
    /* FINAL HASH */
    return md5_hash((const char *) reduced_hash);
}

unsigned int *reduction(int i, const unsigned char *md5_digest)
{
    MD5_LONG a, b, c, d;
    MD5_LONG result;
    unsigned int *res_ptr;
    res_ptr = (unsigned int *) ec_malloc(sizeof(MD5_LONG) * 16);

    a = *&md5_digest[0];
    b = *&md5_digest[8];
    c = *&md5_digest[16];
    d = *&md5_digest[24];


    // Take a chunked 64-bits of the hashed digest and modulo it
    // with 26 to power of i, the number of characters in the password.
    assert(i != 0);

    a = a % (MD5_LONG) pow(26, i);
    b = b % (MD5_LONG) pow(26, i);
    c = c % (MD5_LONG) pow(26, i);
    d = d % (MD5_LONG) pow(26, i);
    result = (a * i + 1) + (b * i + 2) + (c * i + 3) + (d * i + 4);
    memset(res_ptr, result, sizeof(MD5_LONG) * 16);

    if ( DEBUG ) {
        printf("%x %x %x %x | %x\n", a, b, c, d, result);
        printf("%u \n", *res_ptr);
    }

    return res_ptr;
}

// A hashing function to create MD5 Digest from a string passed in.
unsigned char *md5_hash(const char * str)
{
    unsigned char *md5_digest;
    md5_digest = (unsigned char *) ec_malloc(MD5_DIGEST_LENGTH);

    // MD5_CTX md5c;
    // MD5_Init(&md5c);
    // MD5_Update(&md5c, str, (unsigned int) strlen((const char *) str));
    MD5((const unsigned char *) str, strlen(str), md5_digest);

    if ( DEBUG ) {
        printf("MD5 Digest: ");
        for (int i=0; i < MD5_DIGEST_LENGTH; i++) printf("%02x ", md5_digest[i]);
        printf("\n");
    }

    return md5_digest;
}
