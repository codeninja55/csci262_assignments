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
#include <ctype.h>
#include "avltree.h"
#include "helper.h"

#define DEBUG false
#define USED 1
// #define NOT_USED 0

/* NOTE: MD5_LONG macro from openssl md5.h to use unsigned int 4 bytes i.e. 32 bits*/
/* NOTE: MD5_CHAR macro from avltree.h to use unsigned char 1 byte i.e. 8 bits*/

/* ########## GLOBAL VARS ########## */
NODE *RAINBOW_TREE;
int COUNT = 0;
int REDUCE_VALS[] = {12, 8, 6, 4};

/* ########## FUNCTION PROTOTYPES ########## */
void traverse_tree(NODE*, FILE*);
MD5_CHAR *generate_final_hash(const char *);
MD5_CHAR *reduction(int, const unsigned char *);
MD5_CHAR *md5_hash(const char*);

#pragma clang diagnostic push
#pragma ide diagnostic ignored "KRUnspecifiedParameters"

int main( int argc, const char* argv[] )
{
    /* ==========| PART 1 |========== */
    char buffer[200];
    if ( argc == 2 ) strcpy(buffer, argv[1]);
    else {
        fprintf(stderr, "Usage: Rainbow <filename> \n");
        exit(1);
    }

    FILE *fd;

    /* READING AND BUILDING AVL TREE */
    if ( (fd = fopen(buffer, "r")) == NULL )  {
        fprintf(stderr, "Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    // READING from file descriptor fd FILE stream.
    char str_passwd[PASSWORD_LEN];

    while ( fscanf(fd, "%s", str_passwd) == 1 ) {
        if ( ferror(fd) ) break;

        COUNT++;

        PasswordRecord password_rec;
        strcpy(password_rec.str_passwd, str_passwd);
        password_rec.used = USED;
        password_rec.hashed_digest = generate_final_hash((const char *) str_passwd);

        for (int pos=0; pos < MD5_DIGEST_LENGTH; pos++)
            sprintf(password_rec.str_hash+(pos*2), "%02x", password_rec.hashed_digest[pos]);

        RAINBOW_TREE = insert(RAINBOW_TREE, password_rec.str_hash, password_rec);
    }
    fclose(fd);

    /* WRITING TO FILE */

    // WRITING to Rainbow.txt with file descriptor fd
    if ( (fd = fopen("Rainbow.txt", "w")) == NULL )  {
        fprintf(stderr, "[DEBUG]: Failed to open file [ %s ]\n", strerror(1));
        exit(1);
    }

    fprintf(fd, "%-32s %s\n","message_digest", "string_password");
    traverse_tree(RAINBOW_TREE, fd);
    fclose(fd);

    // Print to stdout the RAINBOW_TREE
    // pre_order_sort(RAINBOW_TREE);
    in_order_sort(RAINBOW_TREE);

    printf("Passwords read: %d\n", COUNT);

    /* ==========| PART 2 |========== */
    char hash_input_str[33];
    bool valid = false;

    while ( !valid ) {
        printf("Input Hash Hex: ");
        scanf("%s", hash_input_str);

        // Check the input from the user
        if ( strlen(hash_input_str) > 32 ) {
            printf("Tooooooooooooooo many characters mate.\n"
                   "Must be 32 chars in length.\n"
                   "Please try again...\n\n");
            valid = false;
        } else if ( strlen(hash_input_str) < 32 ) {
            printf("Not enough characters for a hashed message digest.\n"
                   "Must be 32 chars in length.\n"
                   "Please try again...\n\n");
            valid = false;
        } else {
            for ( int j=0; j < strlen(hash_input_str); j++ ) {
                if ( isxdigit(hash_input_str[j]) == 0 ) {  // The char read is not a hex digit
                    printf("Not a valid message digest string.\n"
                           "Please try again\n\n");
                    valid = false;
                } else if ( j == strlen(hash_input_str) - 1 )  // If it reaches end, then valid hash
                    valid = true;
            }
        }
    }

    NODE *found = search(RAINBOW_TREE, hash_input_str);
    int search_ctr = 0;

    // Test hex digest to use: 56dc13fd4d31f9b178831a274e6d22e2 (should map to 'andrew')
    if ( found != NULL )  // found it on first attempt
        printf("FOUND (1): %s", found->password_record.str_passwd);
    else {

        MD5_CHAR *reduced_input = reduction(REDUCE_VALS[search_ctr%4], (const MD5_CHAR *) hash_input_str);
        MD5_CHAR *hashed_input = md5_hash((const char *) reduced_input);
        while ( search_ctr < COUNT ) {
            found = search(RAINBOW_TREE, hashed_input);

            if ( found != NULL ) { // found a match
                MD5_CHAR *pre_image_hash = md5_hash(found->password_record.str_passwd);
                printf("FOUND: %s", found->password_record.str_passwd);  // found password

                if ( strncmp((const char *) hashed_input, (const char *) pre_image_hash, 32) == 0 ) {
                    printf("YIPPEEEE YOU HAVE FOUND IT");
                    break;
                } else {

                    unsigned long crack = 2000000;

                    while ( crack != 0 ) {
                        MD5_CHAR *reduced_pre_image = reduction(REDUCE_VALS[search_ctr%4], pre_image_hash);
                        MD5_CHAR *new_pre_image_hash = md5_hash((const char *) reduced_pre_image);
                        if (strncmp((const char *) new_pre_image_hash, (const char *) pre_image_hash, 32) == 0 ) {
                            printf("YIPPEEEE YOU HAVE FOUND SOMETHING ON YOUR 2nd ATTEMPT");
                            break;
                        }
                        crack--;
                    }
                }

            } else {
                search_ctr++;
                printf("DID NOT FIND A MATCH FOR: %s\n", hashed_input);
                reduced_input = reduction(REDUCE_VALS[search_ctr%4], hashed_input);
                hashed_input = md5_hash((const char *) reduced_input);
            }
        }
    }

    return 0;
}
#pragma clang diagnostic pop

// Traverse the RAINBOW AVL tree and write to file for each node.
void traverse_tree(NODE *node, FILE *fd)
{
    if ( node != NULL ) {
        traverse_tree(node->left, fd);
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            fprintf(fd, "%02x", node->password_record.hashed_digest[i]);
        }
        fprintf(fd, " ");
        fprintf(fd, "%s\n", node->password_record.str_passwd);
        traverse_tree(node->right, fd);
    }
}

// Use the steps of hashing then reducing to generate a hashing chain and return the final hash
MD5_CHAR *generate_final_hash(const char *value)
{
    MD5_CHAR *current_hash;
    MD5_CHAR *reduced_hash;

    /* FIRST HASH - REDUCE */
    current_hash = md5_hash(value);
    reduced_hash = reduction(REDUCE_VALS[0], current_hash);
    /* SECOND HASH - REDUCE */
    current_hash = md5_hash((const char *) reduced_hash);
    reduced_hash = reduction(REDUCE_VALS[1], current_hash);
    /* THIRD HASH - REDUCE */
    current_hash = md5_hash((const char *) reduced_hash);
    reduced_hash = reduction(REDUCE_VALS[2], current_hash);
    /* FOURTH HASH - REDUCE */
    current_hash = md5_hash((const char *) reduced_hash);
    reduced_hash = reduction(REDUCE_VALS[3], current_hash);
    /* FINAL HASH */
    return md5_hash((const char *) reduced_hash);
}

MD5_CHAR *reduction(int i, const unsigned char *md5_digest)
{
    MD5_LONG digest_sum = 0;
    MD5_LONG result = 0;
    MD5_CHAR *res_ptr;

    res_ptr = (MD5_CHAR *) ec_malloc(sizeof(MD5_LONG) * 16);

    // Decode the digest by using bitwise operators and shifting bits
    for (int j=0; j < 16; j++) {
        digest_sum = (MD5_LONG) md5_digest[j] | (MD5_LONG) md5_digest[j + 1] << 8 |
                     (MD5_LONG) md5_digest[j + 2] << 16 | (MD5_LONG) md5_digest[j + 3] << 24;
    }

    assert(i != 0);
    result = (digest_sum) % (MD5_LONG) pow(26, i);

    // Encode the MD5_LONG to MD5_CHAR by shifting bits and bitwise operators with 0
    int k, l;
    for (k=0, l=0; l < MD5_DIGEST_LENGTH; k++, l+=4) {
        res_ptr[l] = (MD5_CHAR) (result & 0xff);
        res_ptr[l+1] = (MD5_CHAR) ((result >> 8) & 0xff);
        res_ptr[l+2] = (MD5_CHAR) ((result >> 16) & 0xff);
        res_ptr[l+3] = (MD5_CHAR) ((result >> 24) & 0xff);
    }

    if ( DEBUG ) {
        printf("res_ptr: %u \n", *res_ptr);
        printf("Digest Sum: %d \n", digest_sum);
        printf("Result: %d \n", result);
    }

    return res_ptr;
}

// A hashing function to create MD5 Digest from a string passed in using openssl implementation.
MD5_CHAR *md5_hash(const char * str)
{
    unsigned char *md5_digest;
    md5_digest = (unsigned char *) ec_malloc(MD5_DIGEST_LENGTH);

    // If using the other md5.h implementation, follow these steps.
    // MD5_CTX md5c;
    // MD5_Init(&md5c);
    // MD5_Update(&md5c, str, (unsigned int) strlen(str));

    // If using the openssl/md5.h, do all steps in one
    MD5((const unsigned char *) str, strlen(str), md5_digest);

    if ( DEBUG ) {
        printf("MD5 Digest: ");
        for (int i=0; i < MD5_DIGEST_LENGTH; i++) printf("%02x", md5_digest[i]);
        printf("\n");
    }

    return md5_digest;
}
