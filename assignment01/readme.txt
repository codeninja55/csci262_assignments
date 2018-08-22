CSCI262 - Systems Security | Assignment 01 Readme
Author: Dinh Che (dbac496)
Date: 20.08.2018

Compile
$ gcc -std=c99 avltree.h avltree.c helper.h helper.c Rainbow.c -o Rainbow -lssl -lcypto -lm
$ ./Rainbow <filename>

Additional Notes:
A 'words' and 'Passwords.txt' file has been provided as part of the folder.

Reduction Function Implementation
The 'reduction' function takes an int i and the unsigned char pointer md5_digest.
I then use bitwise operators and bit shifting to try to get the 32-bit width of the message
digest which is a 128-bit / 32 byte hex value to decode it to an MD5_LONG type (macro for
unsigned int) called digest_sum. After getting the bit sum for the digest_sum I then
take this value and apply the modulo of 26 to the power of the int i passed. The i has been
defined as a global array with 4 possible values of 12, 8, 6, and 4 based on how many
words the password contains.

After doing the calculations to get an integer, I endcode the value back to an unsigned
char pointer and return that to be hashed again.
