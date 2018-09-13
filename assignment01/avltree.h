/*********************************************************************
* Title: AVL Tree Header
* File: avltree.h - header file for the avltree.c source implementation.
* Author: Dinh Che (codeninja55) andrew at codeninja.me
* Last modified: 2018.08.19
*********************************************************************/

#ifndef AVLTREE_H
#define AVLTREE_H

#define PASSWORD_LEN 20
#define MD5_CHAR unsigned char
#define MD5_LONG unsigned int

typedef struct {
    char str_passwd[PASSWORD_LEN];
    char str_hash[33];
    MD5_CHAR *hashed_digest;
    int used;
} PasswordRecord;

typedef struct NODE {
    char key[33];
    PasswordRecord password_record;
    struct NODE *left, *right;
    int height;
} NODE;

extern NODE* insert(NODE* node, char *key, PasswordRecord pr);
extern NODE* rotate_right(NODE* n2);
extern NODE* rotate_left(NODE* n2);
extern NODE* double_rotate_right(NODE* n3);
extern NODE* double_rotate_left(NODE* n3);
extern void in_order_sort(NODE* root);
extern void pre_order_sort(NODE *root);
extern NODE* search();
extern int height(NODE* n);
extern int get_balance(NODE* n);
extern int max(int a, int b);
extern int str_cmp(const char *str1, const char *str2);

#endif //AVLTREE_H
