/*********************************************************************
* Title: AVL Tree Header
* File: avltree.h - header file for the avltree.c source implementation.
* Author: Dinh Che (codeninja55) andrew at codeninja.me
* Last modified: 2018.08.19
*********************************************************************/

#ifndef AVLTREE_H
#define AVLTREE_H
#define PASSWORD_LEN 20

typedef struct {
    char str_passwd[PASSWORD_LEN];
    unsigned char *hashed_digest;
    int used;
} PasswordRecord;

typedef struct NODE {
    char key[PASSWORD_LEN];
    PasswordRecord password_record;
    struct NODE *left, *right;
    int height;
} NODE;

NODE *AVL_TREE;

extern NODE* insert(NODE* node, char *key, PasswordRecord pr);
extern NODE* rotate_right(NODE* n2);
extern NODE* rotate_left(NODE* n2);
extern NODE* double_rotate_right(NODE* n3);
extern NODE* double_rotate_left(NODE* n3);
extern void in_order_sort(NODE* root);
extern NODE* search();
extern int height(NODE* n);
extern int get_balance(NODE* n);
extern int max(int a, int b);
extern int str_cmp(const char *str1, const char *str2);

#endif //AVLTREE_H
