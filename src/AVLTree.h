/**
 * @file AVLTree.h
 * @brief Interface for the AVL Tree data structure.
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include "Contact.h"

// Definition of a node in the AVL tree
struct Node {
    Contact contact;
    Node* left;
    Node* right;
    int height;

    Node(Contact c);
};

class AVLTree {
private:
    // Helper functions for tree balancing
    int height(Node* node);
    int balance(Node* node);
    
    // Rotation functions
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* minValueNode(Node* node);

public:
    AVLTree();
    Node* root;

    // Core AVL tree operations
    Node* insert(Node* node, Contact c);
    Node* search(Node* node, int id);
    Node* remove(Node* node, int id);
    
    // Utility functions
    void inorder(Node* node);
    void displayTree(Node* node, int space);
};

#endif // AVLTREE_H