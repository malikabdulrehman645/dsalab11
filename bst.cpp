#include <iostream>
using namespace std;

class TNode {
public:
    int data;
    TNode* left;
    TNode* right;

    // Constructor with assignment inside the body
    TNode() {
        data = 0;
        left = nullptr;
        right = nullptr;
    }

    TNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    TNode* root;

    // Helper function for inserting a value into the BST
    TNode* insertHelper(TNode* node, int value) {
        if (node == nullptr) {
            return new TNode(value);  // Create a new node if the current position is null
        }

        if (value < node->data) {
            node->left = insertHelper(node->left, value);  // Recur on left subtree
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value); // Recur on right subtree
        }

        return node;
    }

    // Helper function to find the maximum value in the tree
    TNode* findMaxHelper(TNode* node) {
        while (node && node->right != nullptr) {
            node = node->right;  // Traverse right to find the maximum value
        }
        return node;
    }

    // Helper function for searching a value in the BST
    bool searchHelper(TNode* node, int value) {
        if (node == nullptr) {
            return false;  // Node not found
        }
        if (node->data == value) {
            return true;  // Node found
        }

        return (value < node->data) ? searchHelper(node->left, value) : searchHelper(node->right, value);
    }

    // Helper function for deleting a node in the BST
    TNode* deleteHelper(TNode* node, int value) {
        if (node == nullptr) {
            return node;
        }

        // Search for the node to delete
        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else { // Node to be deleted found
            // Case 1: Node has no children (leaf node)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: Node has one child
            if (node->left == nullptr) {
                TNode* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                TNode* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Node has two children
            TNode* temp = findMaxHelper(node->right); // Find the minimum node in the right subtree
            node->data = temp->data; // Replace node data with the minimum node's data
            node->right = deleteHelper(node->right, temp->data); // Delete the in-order successor
        }

        return node;
    }

    // Helper function for in-order traversal
    void inOrderHelper(TNode* node) {
        if (node == nullptr) {
            return;
        }

        inOrderHelper(node->left); // Visit left subtree
        cout << node->data << " ";  // Print node data
        inOrderHelper(node->right); // Visit right subtree
    }

    // Helper function to get the parent of a node
    TNode* getParentHelper(TNode* node, int value) {
        if (node == nullptr || node->data == value) {
            return nullptr;
        }

        if ((node->left != nullptr && node->left->data == value) || 
            (node->right != nullptr && node->right->data == value)) {
            return node;  // Parent node found
        }

        if (value < node->data) {
            return getParentHelper(node->left, value);
        } else {
            return getParentHelper(node->right, value);
        }
    }

public:
    // Constructor for initializing an empty BST with assignment inside the body
    BST() {
        root = nullptr;
    }

    // Function to insert a value into the BST
    void insert(int value) {
        root = insertHelper(root, value);  // Start the insertion process from root
    }

    // Function to search for a value in the BST
    bool search(int value) {
        return searchHelper(root, value);  // Start the search process from root
    }

    // Function to delete a node from the BST
    void deleteNode(int value) {
        root = deleteHelper(root, value);  // Start deletion from root
    }

    // Function to check if the BST is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Function to perform an in-order traversal
    void inOrderTraversal() {
        inOrderHelper(root);  // Start in-order traversal from root
        cout << endl;
    }

    // Function to get the parent of a node
    TNode* getParent(int value) {
        return getParentHelper(root, value);
    }

    // Function to find the maximum value in the BST
    TNode* findMax() {
        return findMaxHelper(root);
    }

    // Function to get the root of the BST
    TNode* getRoot() {
        return root;
    }
};

// 1. Given an integer value, print the path of the node from the root to the node.
void printPathToNode(TNode* root, int value) {
    if (root == nullptr) {
        cout << "Node not found." << endl;
        return;
    }

    if (root->data == value) {
        cout << value << " ";
        return;
    }

    cout << root->data << " ";  // Print the current node
    if (value < root->data) {
        printPathToNode(root->left, value);  // Recur to left subtree
    } else {
        printPathToNode(root->right, value);  // Recur to right subtree
    }
}

// 2. Find the maximum value in the BST
int findMaxValue(BST& tree) {
    TNode* maxNode = tree.findMax();
    if (maxNode) {
        return maxNode->data;
    }
    return -1;  // Return -1 if tree is empty
}

// 3. Find the sibling of a given node, if it exists.
int findSibling(TNode* root, int value) {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return -1;  // No sibling or no node found
    }

    if (root->left && root->left->data == value) {
        return root->right ? root->right->data : -1;  // Return sibling's data
    }

    if (root->right && root->right->data == value) {
        return root->left ? root->left->data : -1;  // Return sibling's data
    }

    // Recur to find sibling in left or right subtree
    int leftSibling = findSibling(root->left, value);
    if (leftSibling != -1) {
        return leftSibling;
    }
    return findSibling(root->right, value);
}

int main() {
    BST tree;

    // Insert nodes into the tree
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Print in-order traversal
    cout << "In-order Traversal: ";
    tree.inOrderTraversal();

    // 1. Print the path to a given node
    int value = 40;
    cout << "Path to node " << value << ": ";
    printPathToNode(tree.getRoot(), value);
    cout << endl;

    // 2. Find maximum value in the BST
    cout << "Maximum value in the BST: " << findMaxValue(tree) << endl;

    // 3. Find sibling of a given node
    int siblingValue = 20;
    int sibling = findSibling(tree.getRoot(), siblingValue);
    if (sibling != -1) {
        cout << "Sibling of node " << siblingValue << " is " << sibling << endl;
    } else {
        cout << "Node " << siblingValue << " has no sibling." << endl;
    }

    return 0;
}
