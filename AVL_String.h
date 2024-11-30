#pragma once
#include<iostream>
using namespace std;


void copyString(char*& destination, char* source) {
    if (destination != nullptr) {
        delete[] destination;
    }
    if (source == nullptr) {
        destination = nullptr;
    }
    else {
        int length = 0;
        while (source[length] != '\0') length++;
        destination = new char[length + 1];
        for (int i = 0; i < length; i++) {
            destination[i] = source[i];
        }
        destination[length] = '\0';
    }
}

class nodeString {
private:
    char* data; 
    int count;
public:
    nodeString* left;
    nodeString* right;

    nodeString(char* d) {
        data = nullptr;
        copyString(data, d); 
       // cout << data << endl;
        count = 1;
        left = right = nullptr;
    }

    ~nodeString() {
        delete[] data; 
    }

    char* getData() {
        return data;
    }

    void setData(char* d) {
        copyString(data, d); 
    }

    int getCount() {
        return count;
    }

    void incrementCount() {
        count++;
    }

    void decrementCount() {
        if (count > 0) count--;
    }
};




class AVLString {
public:
    nodeString* root;

    AVLString() {
        root = NULL;
    }

    int height(nodeString* root) {
        if (!root) return -1;
        int left = height(root->left);
        int right = height(root->right);
        return max(left, right) + 1;
    }

    int balanceFactor(nodeString* root) {
        return height(root->right) - height(root->left);
    }

    void insert(const char* d) {
        char* normalized = toLowerCase(d);
        insert(root, normalized);
        delete[] normalized; 
    }

    void insert(nodeString*& root, char* d) {
        if (!root) {
            root = new nodeString(d);
        }
        else {
            if (strcmp(root->getData(), d) > 0) {
                insert(root->left, d);
            }
            else if (strcmp(root->getData(), d) < 0) {
                insert(root->right, d);
            }
            else {
                root->incrementCount();
            }
        }
        AVLTreeRebalancingInsertion(root);
    }

    void leftRotation(nodeString*& root) {
        nodeString* candidate = root->right;
        root->right = candidate->left;
        candidate->left = root;
        root = candidate;
    }

    void rightRotation(nodeString*& root) {
        nodeString* candidate = root->left;
        root->left = candidate->right;
        candidate->right = root;
        root = candidate;
    }

    void AVLTreeRebalancingInsertion(nodeString*& root) {
        int balance = balanceFactor(root);
        if (balance == 2 && root->right && balanceFactor(root->right) >= 0) {
            leftRotation(root);
        }
        else if (balance == -2 && root->left && balanceFactor(root->left) <= 0) {
            rightRotation(root);
        }
        else if (balance == 2 && root->right && balanceFactor(root->right) < 0) {
            rightRotation(root->right);
            leftRotation(root);
        }
        else if (balance == -2 && root->left && balanceFactor(root->left) > 0) {
            leftRotation(root->left);
            rightRotation(root);
        }
    }

    void inorderTraversal(nodeString* root) {
        if (!root) return;
        inorderTraversal(root->left);
        cout << root->getData() << "(" << root->getCount() << ") ";
        inorderTraversal(root->right);
    }

    void preorderTraversal(nodeString* root) {
        if (!root) return;
        cout << root->getData() << "(" << root->getCount() << ") " << endl;
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }

    void preorderTraversal() {
        preorderTraversal(root);
    }

    char* toLowerCase(const char* str) {
        char* result = new char[strlen(str) + 1];
        for (size_t i = 0; i < strlen(str); i++) {
            result[i] = tolower(str[i]);
        }
        result[strlen(str)] = '\0';
        return result;
    }
};

