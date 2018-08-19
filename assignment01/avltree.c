/********************************************************************
* Title: AVL Tree Source File
* File: avltree definitions and implementation an AVL tree
*      data structure to be used.
* Author: Dinh Che (codeninja55) andrew at codeninja.me
* Last modified: 2018.08.19
*********************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include "avltree.h"
#include "helper.h"


// Recursively insert a node into the tree and then fix it's balance by rotations
NODE* insert(NODE* node, char *key, PasswordRecord pr)
{
    if ( node != NULL ) {
        // printf("Key: [ %02x ]", (unsigned int) key);
        // printf("%d\n", strncmp((const char *) key, (const char *) node->key, 8));
        // printf("%d\n", memcmp(key, node->key, 6));

        // printf("Key: %s  ; Node Key: %s \n", key, node->key);
    }
    if ( node == NULL ) {
        NODE *new_node = (NODE *) ec_malloc(sizeof(NODE));
        strcpy(new_node->key, key);
        new_node->password_record = pr;
        new_node->left = new_node->right = NULL;
        new_node->height = 0;
        return new_node;
    } else if ( strcmp(key, node->key ) < 0 ) {
        node->left = insert(node->left, key, pr);
    } else if ( strcmp(key, node->key) > 0 ) {
        node->right = insert(node->right, key, pr);
    } else
        return node;  // Equal keys not allowed

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = get_balance(node);

    // Checking the imbalance and balancing the BST.
    /* CASE 1 - left left case */
    // if ( balance > 1 && key < (node->left)->key )
    if ( balance > 1 && strcmp(key, (node->left)->key) < 0 )
        return rotate_right(node);

    /* CASE 2 - right right case */
    if ( balance < -1 && strcmp(key, (node->right)->key) > 0 )
        return rotate_left(node);

    /* CASE 3 - left right case */
    if ( balance > 1 && strcmp(key, (node->left)->key) > 0 )
        return double_rotate_right(node);

    /* CASE 4 - right left case */
    if ( balance < -1 && strcmp(key, (node->right)->key) < 0 )
        return double_rotate_left(node);

    return node;
}

NODE* rotate_right(NODE* n2)
{
    NODE *n1 = n2->left;
    NODE *t2 = n1->right;

    n1->right = n2;
    n2->left = t2;
    n2->height = 1 + max(height(n2->left), height(n2->right));
    n1->height = 1 + max(height(n1->left), height(n2));
    return n1;
}

NODE* rotate_left(NODE* n2)
{
    NODE *n1 = n2->right;
    NODE *t2 = n1->left;

    n1->left = n2;
    n2->right = t2;

    n2->height = 1 + max(height(n2->left), height(n2->right));
    n1->height = 1 + max(height(n2), height(n1->right));
    return n1;
}

NODE* double_rotate_right(NODE* n3)
{
    n3->left = rotate_left(n3->left);
    return rotate_right(n3);
}

NODE* double_rotate_left(NODE* n3)
{
    n3->right = rotate_right(n3->right);
    return rotate_left(n3);
}

// Traverse and sort the BST in-order
void in_order_sort(NODE *root)
{
    if ( root != NULL ) {
        in_order_sort(root->left);
        // for ( int i = 0; i < 16; i++ ) printf("%02x ", (unsigned int) root->key[i]);
        // printf("\n");
        printf("%s\n", root->key);
        in_order_sort(root->right);
    }
}

// Traverse the tree to search for a node based on key
NODE* search(NODE* ROOT, char *key)
{
    if ( ROOT == NULL )
        return NULL;

    if ( strcmp(key, ROOT->key ) == 0 )
        return ROOT;

    if ( strcmp(key, ROOT->key ) < 0 )
        return search(ROOT->left, key );
    else
        return search(ROOT->right, key);
}

/* HELPER FUNCTIONS */

// A helper function to get the height of the tree
int height(NODE *n)
{
    return (n == NULL) ? 0 : n->height;
}

// Get Balance factor of node N
int get_balance(NODE *n)
{
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int str_cmp(const char *str1, const char *str2)
{
    while ( *str1 || *str2 ) {
        if ( *str1 != *str2 ) return *str1 - *str2;
        printf("str1: %s ; str2: %s\n", str1, str2);
        ++str1;
        ++str2;
    }
    return 0;
}
