/**
 * @file AVLTree.cpp
 * @brief Implementation of AVL Tree balancing, insertion, and deletion logic.
 */

#include "AVLTree.h"
#include <iostream>

Node::Node(Contact c) : contact(c), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

// Return height of the node
int AVLTree::height(Node* node) {
    if (node == nullptr) {
        return 0; 
    }

    return node->height;
}

// Get balance factor of node (Left Height - Right Height)
int AVLTree::balance(Node* node) {
    if (node == nullptr) {
        return 0; 
    }

    return height(node->left) - height(node->right);
}

// Right Rotation for Left-Left imbalance
Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left Rotation for Right-Right imbalance
Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Get node with minimum value (used in deletion)
Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left) {
        current = current->left;
    }
    return current;
}

Node* AVLTree::insert(Node* node, Contact c) {
    if (node == nullptr) {
        return new Node(c); 
    }

    // Perform normal BST insertion
    if (c.id < node->contact.id) {
        node->left = insert(node->left, c);
    }
    else if (c.id > node->contact.id) {
        node->right = insert(node->right, c);
    }
    else {
        return node; // Duplicate IDs are not allowed
    }

    node->height = max(height(node->left), height(node->right)) + 1; // Update height
    int b = balance(node);

    // Left-Left Case
    if (b > 1 && c.id < node->left->contact.id) {
        return rightRotate(node);
    }
    // Right-Right Case
    if (b < -1 && c.id > node->right->contact.id) {
        return leftRotate(node);
    }
    // Left-Right Case
    if (b > 1 && c.id > node->left->contact.id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right-Left Case
    if (b < -1 && c.id < node->right->contact.id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* AVLTree::search(Node* node, int id) {
    if (node == nullptr || node->contact.id == id) {
        return node;
    }

    return (id < node->contact.id) ? search(node->left, id) : search(node->right, id);
}

Node* AVLTree::remove(Node* node, int id) {
    if (node == nullptr) {
        return node;
    }

    // Standard BST Removal logic
    if (id < node->contact.id) {
        node->left = remove(node->left, id);
    }
    else if (id > node->contact.id) {
        node->right = remove(node->right, id);
    }
    else { 
        // Node with only one child or no child
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } 
            else {
                *node = *temp;
            }
            delete temp;
        } 
        // Node with two children: Get the inorder successor
        else {
            Node* temp = minValueNode(node->right);
            node->contact.id = temp->contact.id;
            node->right = remove(node->right, temp->contact.id);
        }         
    }

    if (node == nullptr) {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1; // Update height
    int b = balance(node);

    // Left-Left Case
    if (b > 1 && balance(node->left) >= 0) {
        return rightRotate(node);
    }
    // Right-Right Case
    if (b < -1 && balance(node->right) <= 0) {
        return leftRotate(node);
    }
    // Left-Right Case
    if (b > 1 && balance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right-Left Case
    if (b < -1 && balance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// Traverses the tree and prints contacts in ascending order of ID
void AVLTree::inorder(Node* node) {
    if (node == nullptr) { 
        return;
    }

    inorder(node->left);
    cout << "ID: " << node->contact.id << ", Name: " << node->contact.name 
         << ", Phone: " << node->contact.phone << ", Email: " << node->contact.email << endl;
    inorder(node->right);
}

// Prints a visual representation of the tree structure (Horizontal)
void AVLTree::displayTree(Node* node, int space) {
    if (node == nullptr) { 
        return; 
    }
    
    int indent = 6;
    space += indent;
    displayTree(node->right, space);
    cout << endl;

    for (int i = indent; i < space; i++) {
        cout << " ";
    }
    
    cout << node->contact.id << " (h=" << node->height << ")";
    displayTree(node->left, space);
}