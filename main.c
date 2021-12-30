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
 * @brief Performs a pre-order traversal of the binary tree and prints
 * the values of each node based on this tree traversal
 * 
 * @param root The address of the root of the binary tree or subtree to
 * start the pre-order traversal from
 */
void preOrderTraversal(struct nodeBST *root) {
    if (root) {
        printf("%d - ", root->value);
        preOrderTraversal(root->leftChild);
        preOrderTraversal(root->rightChild);
    }
}

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
        printf("%d - ", root->value);  // process node
        inOrderTraversal(root->rightChild);  // move to right subtree
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

/**
 * @brief Adds a new node to the binary search tree
 * 
 * @param value The value of the node to be added
 * @param root The address of the root of the binary tree or subtree to
 * start the in order traversal from
 */
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
 * @brief Finds the in order successor to the provided node
 * 
 * @param node The address of the node to find the in order successor
 * to
 * @return struct nodeBST* The address of the in order successor
 */
struct nodeBST * findInOrderSuccessor(struct nodeBST *node) {
    // declare and initialize prevNode and currNode
    struct nodeBST *prevNode = NULL;
    struct nodeBST *currNode = node->rightChild;

    // if no left child to currNode, then currNode is in order successor
    if (!currNode->leftChild) {
        return currNode;
    }

    // find the leftmost node in the right subtree
    while (currNode->leftChild) {
        prevNode = currNode;
        currNode = currNode->leftChild;
    }

    // link prevNode left child to currNode right child if there is one
    prevNode->leftChild = currNode->rightChild;
    return currNode;  // return in order successor to provided node
}

/**
 * @brief Removes the first node with the specified value from the BST
 * 
 * @param value The value of the node to remove
 * @param root The address of the root of the binary tree or subtree to
 * start the in order traversal from
 */
void removeNode(int value, struct nodeBST *root) {
    struct nodeBST *prevNode = NULL;
    struct nodeBST *currNode = root;

    // traverse the BST until a node with the correct value is found or
    // until all appropriate nodes have been searched
    while (currNode && currNode->value != value) {
        prevNode = currNode;
        // traverse left
        if (value < currNode->value) {
            currNode = currNode->leftChild;
        // traverse right
        } else {
            currNode = currNode->rightChild;
        }
    }

    // the specified value doesn't exist in the BST
    if (!currNode) {
        return;  // exit the function
    }

    // the specified value is a leaf node
    if (!currNode->leftChild && !currNode->rightChild) {
        // check if currNode is the left child of prevNode
        if (prevNode->leftChild && prevNode->leftChild == currNode) {
            prevNode->leftChild = NULL;
        // check if currNode is the right child of prevNode
        } else {
            prevNode->rightChild = NULL;
        }

        // free currNode from memory
        free(currNode);
        currNode = NULL;

        return;  // exit the function
    }

    // the specified value only has a left child
    if (currNode->leftChild && !currNode->rightChild) {
        // check if currNode is the left child of prevNode
        if (prevNode->leftChild && prevNode->leftChild == currNode) {
            prevNode->leftChild = currNode->leftChild;
        // check if currNode is the right child of prevNode
        } else {
            prevNode->rightChild = currNode->leftChild;
        }

        // free currNode from memory
        free(currNode);
        currNode = NULL;

        return;  // exit the function
    }

    // the specified value only has a right child
    if (currNode->rightChild && !currNode->leftChild) {
        // check if the currNode is the left child of prevNode
        if (prevNode->leftChild && prevNode->leftChild == currNode) {
            prevNode->leftChild = currNode->rightChild;
        // check if the currNode is the right child of prevNode
        } else {
            prevNode->rightChild = currNode->rightChild;
        }

        // free currNode from memory
        free(currNode);
        currNode = NULL;

        return;  // exit the function
    }

    // the specified value is a node with a left and right child
    struct nodeBST *inOrderSuccessor = findInOrderSuccessor(currNode);

    // in order successor is the right child
    if (inOrderSuccessor == currNode->rightChild) {
        // check if the currNode is the left child of prevNode
        if (prevNode->leftChild && prevNode->leftChild == currNode) {
            prevNode->leftChild = inOrderSuccessor;
            inOrderSuccessor->leftChild = currNode->leftChild;
        // check if the currNode is the right child of prevNode
        } else {
            prevNode->rightChild = inOrderSuccessor;
            inOrderSuccessor->leftChild = currNode->leftChild;
        }

        // free currNode from memory
        free(currNode);
        currNode = NULL;

        return;  // exit the function
    }

    if (prevNode->leftChild && prevNode->leftChild == currNode) {
        prevNode->leftChild = inOrderSuccessor;
        
    } else {
        prevNode->rightChild = inOrderSuccessor;
    }
    inOrderSuccessor->leftChild = currNode->leftChild;
    inOrderSuccessor->rightChild = currNode->rightChild;

    free(currNode);
    currNode = NULL;
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
    addNode(20, root);
    addNode(40, root);
    addNode(60, root);
    addNode(80, root);
    addNode(38, root);
    addNode(35, root);
    addNode(32, root);
    addNode(33, root);

    printf("In order traversal: ");
    inOrderTraversal(root);

    printf("\n");

    printf("Pre-order traversal: ");
    preOrderTraversal(root);

    printf("\n");
    
    removeNode(30, root);
    printf("In order traversal: ");
    inOrderTraversal(root);
    printf("\n");
    printf("Pre-order traversal: ");
    preOrderTraversal(root);

    return 0;
}
