/**
 * @file main.c
 * @author Colin Francis
 * @brief A binary search tree implementation in C
 * @version 0.1
 * @date 2021-12-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <stdio.h>
#include <stdlib.h>

// represents a node in a binary search tree which contains a value
// a pointer to the left child and a pointer to the right child
struct nodeBST {
    int value;
    struct nodeBST *leftChild;
    struct nodeBST *rightChild;
};

/**
 * @brief Initializes a binary search tree by creating a root node with the
 * specified value
 * 
 * @param value The value of the root node to be created
 * @return struct nodeBST* The address of the created root node
 */
struct nodeBST * initBST(int value) {
    struct nodeBST node = {.value=value, .leftChild=NULL, .rightChild=NULL};
    struct nodeBST *nodePtr = (struct nodeBST*) malloc(sizeof(struct nodeBST));

    *nodePtr = node;

    return nodePtr;
}

/**
 * @brief Driver code for the binary search tree implementation
 * 
 * @return int 
 */
int main(void) {
    struct nodeBST *root = NULL;

    // initialize binary search tree
    root = initBST(50);

    return 0;
}
