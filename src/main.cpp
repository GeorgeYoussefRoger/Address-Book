/**
 * @file main.cpp
 * @brief Entry point for the AVL Address Book Application. Handles file I/O and user interaction.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "AVLTree.h"

AVLTree tree;
string filename;

// Load contacts from CSV file into AVL tree
void load() {
    ifstream file(filename);
    if (!file) {
        cout << "No existing file found. Starting with an empty address book." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Contact c;
        string id;
        
        // Parse CSV line
        getline(ss, id, ',');
        getline(ss, c.name, ',');
        getline(ss, c.phone, ',');
        getline(ss, c.email, ',');

        c.id = stoi(id); // Convert ID string to integer
        tree.root = tree.insert(tree.root, c);
    }
}

// Recursively saves the AVL tree to a CSV file using in-order traversal
void save(Node* node, ofstream& file) {
    if (node == nullptr) {
        return;
    }
    
    save(node->left, file); // Save left subtree
    file << node->contact.id << "," << node->contact.name << "," << node->contact.phone << "," << node->contact.email << "\n";
    save(node->right, file); // Save right subtree
}

int main() {
    cout << "Enter filename to load/save contacts (must be a .csv file): ";
    cin >> filename;
    // File validation loop
    while (filename.length() < 4 || filename.substr(filename.length() - 4) != ".csv") {
        cout << "Invalid file format. Enter a .csv file:";
        cin >> filename;
    }
    load();
    string choice;

    while (true) {
        cout << "\nAddress Book Application" << endl;
        cout << "------------------------" << endl;
        cout << "1. Add New Contact" << endl;
        cout << "2. Search for Contact" << endl;
        cout << "3. Delete Contact" << endl;
        cout << "4. List All Contacts" << endl;
        cout << "5. Display Current Tree Structure" << endl;
        cout << "6. Exit" << endl;
        cout << "------------------------" << endl;
        cout << "Enter operation (1-6): ";
        cin >> choice;

        if (choice == "1") {
            Contact c;
            cout << "Enter unique ID (integer): "; 
            // Integer ID validation loop
            while (!(cin >> c.id)) {
                cout << "ID must be integer: ";
                cin.clear();
                cin.ignore();
            }
            cin.ignore();
            cout << "Enter name: "; 
            getline(cin, c.name);
            cout << "Enter phone: "; 
            getline(cin, c.phone);
            cout << "Enter email: ";
            getline(cin, c.email);

            if (tree.search(tree.root, c.id)) {
                cout << "Contact with this ID already exists." << endl;
            }
            else {
                tree.root = tree.insert(tree.root, c);
                cout << "Contact added successfully." << endl;
            }
        }
        else if (choice == "2") {
            int id;
            cout << "Enter ID to search: "; 
            // Integer ID validation loop
            while (!(cin >> id)) {
                cout << "ID must be integer: ";
                cin.clear();
                cin.ignore();
            }

            Node* found = tree.search(tree.root, id);
            if (found) {
                cout << "Contact found:" << endl;
                cout << "ID: " << found->contact.id << endl;
                cout << "Name: " << found->contact.name << endl;
                cout << "Phone: " << found->contact.phone << endl;
                cout << "Email: " << found->contact.email << endl;
            }
            else {
                cout << "Contact not found." << endl;
            }
        }
        else if (choice == "3") {
            int id;
            cout << "Enter ID to delete: "; 
            // Integer ID validation loop
            while (!(cin >> id)) {
                cout << "ID must be integer: ";
                cin.clear();
                cin.ignore();
            }

            if (!tree.search(tree.root, id)) {
                cout << "Contact not found." << endl;
            }
            else {
                tree.root = tree.remove(tree.root, id);
                cout << "Contact deleted successfully." << endl;
            }
        }
        else if (choice == "4") {
            cout << "Contacts in Address Book (sorted by ID):" << endl;
            tree.inorder(tree.root);
        }
        else if (choice == "5") {
            cout << "Current AVL Tree:" << endl;
            tree.displayTree(tree.root, 0);
        }
        else if (choice == "6") {
            ofstream file(filename);
            save(tree.root, file); // Save contacts to file before exiting
            return 0;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    }
}