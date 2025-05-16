#include <iostream>
#include <queue>
#include <cstring>
#include <sstream>
#include <fstream>
#include <vector>
#include "node.h"

using namespace std;

Node* insert(Node* root, int val, Node* parent);
void print(Node* root, int space, int count);
Node* search(Node* root, int val);
Node* findMin(Node* node);
Node* deleteNodeHelper(Node* root, int val);
void deleteNode(Node*& root, int val);

int main() {
    vector<int> numbers;
    Node* root = nullptr;
    char input[10];
    bool quit = false;

    while (!quit) {
        cout << "Options: print(p), delete(d), insert(i), search(s), exit(e)" << endl;
        cin.getline(input, 10);

        if (strcmp(input, "p") == 0) {
            print(root, 0, 3);
        } else if (strcmp(input, "d") == 0) {
            int deleteVal;
            cout << "Enter value to delete: ";
            cin >> deleteVal;
            cin.ignore();
            deleteNode(root, deleteVal);
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
                    root = insert(root, numbers[i], nullptr);
                }
            } else if (strcmp(input, "M") == 0) {
                string inputLine;
                cout << "Enter numbers separated by spaces: ";
                getline(cin, inputLine);
                stringstream ss(inputLine);
                int num;
                while (ss >> num) {
                    root = insert(root, num, nullptr);
                }
            }
        } else if (strcmp(input, "s") == 0) {
            int searchVal;
            cout << "Enter value to search: ";
            cin >> searchVal;
            cin.ignore();
            Node* found = search(root, searchVal);
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


Node* insert(Node* root, int val, Node* parent) {
    if (root == nullptr) {
        return new Node(val, parent);
    }

    if (val < root->token) {
        Node* leftChild = insert(root->left, val, root);
        root->left = leftChild;
    } else if (val > root->token) {
        Node* rightChild = insert(root->right, val, root);
        root->right = rightChild;
    }
    // Ignore duplicates
    return root;
}

//print
void print(Node* root, int space, int count) {
    if (root == nullptr) return;
    space += count;
    print(root->right, space, count);
    cout << endl;
    for (int i = count; i < space; i++) cout << " ";
    cout << root->token << endl;
    print(root->left, space, count);
}

//search
Node* search(Node* root, int val) {
    if (root == nullptr || root->token == val) return root;
    if (val < root->token) return search(root->left, val);
    return search(root->right, val);
}

// Find min value in tree
Node* findMin(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// delete
Node* deleteNodeHelper(Node* root, int val) {
    if (root == nullptr) return root;

    if (val < root->token) {
        root->left = deleteNodeHelper(root->left, val);
    } else if (val > root->token) {
        root->right = deleteNodeHelper(root->right, val);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->token = temp->token;
        root->right = deleteNodeHelper(root->right, temp->token);
    }
    return root;
}

void deleteNode(Node*& root, int val) {
    root = deleteNodeHelper(root, val);
}
