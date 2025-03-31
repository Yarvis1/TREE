#include <iostream>
#include <queue>
#include <cstring>
#include "node.h"
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Node* insert(Node* x, int i);
void print(Node* x, int space, int count);
Node* search(Node* root, int key);
Node* deleteNode(Node* root, int key);
Node* findMin(Node* node);

int main() {
    vector<int> numbers;
    Node* root = nullptr;
    char input[10];
    bool quit = false;

    while (!quit) {
        cout << "Options: print(p), delete(d), insert(i), search(s), exit(e)" << endl;
        cin.getline(input, 10);

        if (strcmp(input, "p") == 0) {
            print(root, 0, 3); // Print tree structure
        } else if (strcmp(input, "d") == 0) {
            int deleteVal;
            cout << "Enter value to delete: ";
            cin >> deleteVal;
            cin.ignore();
            root = deleteNode(root, deleteVal); // Delete node
        } else if (strcmp(input, "i") == 0) {
            cout << "From file(F) or input manually(M)?" << endl;
            cin.getline(input, 10);

            if (strcmp(input, "F") == 0) {
                cout << "Using numbers from file \"number.txt\"" << endl;
                int val;
                ifstream number("number.txt");

                while (number >> val) {
                    numbers.push_back(val);
                }

                for (int i = 0; i < numbers.size(); i++) {
                    root = insert(root, numbers[i]); // Insert from file
                }
            } else if (strcmp(input, "M") == 0) {
                string input;
                cout << "Enter numbers separated by spaces: ";
                getline(cin, input);
                stringstream ss(input);
                int num;
                vector<int> tempNumbers;
                while (ss >> num) {
                    tempNumbers.push_back(num); // Insert manually
                }

                for (int i = 0; i < tempNumbers.size(); i++) {
                    root = insert(root, tempNumbers[i]);
                }
            }
        } else if (strcmp(input, "s") == 0) {
            int searchVal;
            cout << "Enter value to search: ";
            cin >> searchVal;
            cin.ignore();
            Node* found = search(root, searchVal); // Search for value
            if (found) {
                cout << "Value " << found->token << " found." << endl;
            } else {
                cout << "Value not found." << endl;
            }
        } else if (strcmp(input, "e") == 0) {
            quit = true;
        }
    }
    return 0;
}

Node* insert(Node* x, int i) {
    if (x == nullptr) {
        x = new Node(i, NULL); // Create a new node if tree is empty
        return x;
    } else {
        queue<Node*> q;
        q.push(x);
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->left != NULL) {
                q.push(current->left);
            } else {
                current->left = new Node(i, current); // Insert left child
                return x;
            }

            if (current->right != NULL) {
                q.push(current->right);
            } else {
                current->right = new Node(i, current); // Insert right child
                return x;
            }
        }
    }
    return x;
}

void print(Node* root, int space, int count) {
    if (root == nullptr) return;
    space += count;
    print(root->right, space, 3); // Print right subtree
    cout << endl;
    for (int i = count; i < space; i++) cout << " ";
    cout << root->token << endl; // Print current node
    print(root->left, space, 3); // Print left subtree
}

Node* search(Node* root, int key) {
    if (root == nullptr || root->token == key) return root; // Found node or reached end
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        if (current->token == key) return current; // Found value
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    return nullptr; // Not found
}

Node* findMin(Node* node) {
    while (node && node->left != nullptr) node = node->left; // Find the minimum value
    return node;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return nullptr;

    if (key < root->token) {
        root->left = deleteNode(root->left, key); // Recur on left
        if (root->left != nullptr) root->left->parent = root;
        return root;
    } else if (key > root->token) {
        root->right = deleteNode(root->right, key); // Recur on right
        if (root->right != nullptr) root->right->parent = root;
        return root;
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root; // Leaf node
            return nullptr;
        }

        if (root->left == nullptr) {
            Node* temp = root->right;
            if (temp != nullptr) temp->parent = root->parent;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            if (temp != nullptr) temp->parent = root->parent;
            delete root;
            return temp;
        }

        Node* successor = findMin(root->right);
        root->token = successor->token; // Replace with successor
        root->right = deleteNode(root->right, successor->token);
        if (root->right != nullptr) root->right->parent = root;
        return root;
    }
}