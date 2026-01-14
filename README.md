# 📒 Address Book Application
A high-performance C++ address book application that utilizes a self-balancing AVL Binary Search Tree (BST) to manage contact information efficiently.
The system guarantees O(log n) time complexity for insertion, deletion, and search operations, while providing persistent CSV storage.

## 🚀 Features
- Self-Balancing Logic: Automatic LL, RR, LR, and RL rotations to maintain optimal height
- CSV Persistence: Loads contacts on startup and saves sorted data on exit
- Input Validation: Integer validation for IDs, CSV file extension checks for safe file handling
- Tree Visualization: Horizontal AVL tree display showing structure and node heights
- Sorted Management: Contacts are always maintained in ascending order by unique ID

## 🧠 Methodology
- Data Structures
    - Contact: Stores a unique ID, name, phone number, and email
    - AVL Tree: A height-balanced BST where the balance factor is kept within {-1, +1}
- Balancing Operations
    - Single Rotations: Left-Left (Right Rotate) and Right-Right (Left Rotate)
    - Double Rotations: Left-Right and Right-Left
- File Handling
    - Loading: CSV rows are parsed using `std::stringstream` and converted into `Contact` objects
    - Saving: An in-order traversal is used to export data back to CSV, ensuring sorted output by ID

## 🌲 Tree Visualization Example
- A horizontal representation is used for clarity:
```
        310 (h=1)
    210 (h=2)
        150 (h=1)
```
- Right subtree appears above
- Left subtree appears below
- Indentation represents tree depth
- h represents the height of each node

## 📂 Project Structure
```
Address-Book/
├── src/
│   ├── AVLTree.h      # AVL Tree class interface and Node structure
│   ├── Contact.h      # Definition of the Contact data structure
│   ├── AVLTree.cpp    # Implementation of balancing and tree logic
│   └── main.cpp       # UI logic and CSV file management
├── README.md
├── .gitignore
└── LICENSE
```
## 🧰 Technologies Used
- Language: C++ (Standard 17/20 recommended)
- Standard Library: `<iostream>`, `<fstream>`, `<sstream>`, `<string>`

## 📦 Installation & Usage

1. Clone the repository
```
git clone https://github.com/GeorgeYoussefRoger/Address-Book.git
cd Address-Book
```

2. Compile the Application
```
g++ -std=c++17 src/*.cpp -o AddressBook
```

3. Run the Program
```
./AddressBook
```

## 📜 License
- This project is licensed under the MIT License.
- See the `LICENSE` file for details.