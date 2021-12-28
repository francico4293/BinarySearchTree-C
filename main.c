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
 * @brief Performs an in order traversal of the binary tree and prints
 * the values of each node based on this tree traversal
 * 
 * @param root The address of the root of the binary tree or subtree to
 * start the in order traversal from
 */
void inOrderTraversal(struct nodeBST *root) {
    if (root) {
        inOrderTraversal(root->leftChild);  // move to left subtree
        inOrderTraversal(root->rightChild);  // move to right subtree
        printf("%d - ", root->value);  // process node
    }
}

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

void addNode(int value, struct nodeBST *root) {
    struct nodeBST *prevNode = NULL;
    struct nodeBST *currNode = root;
    struct nodeBST node = {.value=value, .leftChild=NULL, .rightChild=NULL};
    struct nodeBST *nodePtr = (struct nodeBST*) malloc(sizeof(struct nodeBST));

    *nodePtr = node;

    while (currNode) {
        prevNode = currNode;
        if (value < currNode->value) {
            currNode = currNode->leftChild;
        } else {
            currNode = currNode->rightChild;
        }
    }

    if (value < prevNode->value) {
        prevNode->leftChild = nodePtr;
    } else {
        prevNode->rightChild = nodePtr;
    }
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

    printf("In order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    addNode(30, root);
    addNode(70, root);

    printf("In order traversal: ");
    inOrderTraversal(root);

    return 0;
}
