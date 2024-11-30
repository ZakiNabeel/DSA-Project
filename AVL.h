#pragma once
#include <iostream>
using namespace std;

template <typename T>
class node_T {
private:
    T data;
    int count;

public:
    node_T* left;
    node_T* right;

    node_T(T d = 0) {
        data = d;
        count = 1;
        left = right = nullptr;
    }

    T getData() {
        return data;
    }

    void setData(T d) {
        data = d;
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

template <typename T>
class AVL {
private:
    node_T<T>* root;

    int height(node_T<T>* root) {
        if (!root) return -1;
        int left = height(root->left);
        int right = height(root->right);
        return max(left, right) + 1;
    }

    int balanceFactor(node_T<T>* root) {
        return height(root->right) - height(root->left);
    }

    void leftRotation(node_T<T>*& root) {
        node_T<T>* candidate = root->right;
        root->right = candidate->left;
        candidate->left = root;
        root = candidate;
    }

    void rightRotation(node_T<T>*& root) {
        node_T<T>* candidate = root->left;
        root->left = candidate->right;
        candidate->right = root;
        root = candidate;
    }

    void AVLTreeRebalancingInsertion(node_T<T>*& root) {
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

    void AVLTreeRebalancingDeletion(node_T<T>*& root) {
        if (!root) return;
        int balance = balanceFactor(root);
        if (balance == 2) {
            if (balanceFactor(root->right) >= 0) {
                leftRotation(root);
            }
            else {
                rightRotation(root->right);
                leftRotation(root);
            }
        }
        else if (balance == -2) {
            if (balanceFactor(root->left) <= 0) {
                rightRotation(root);
            }
            else {
                leftRotation(root->left);
                rightRotation(root);
            }
        }
    }

    void inorderTraversal(node_T<T>* root) {
        if (!root) return;
        inorderTraversal(root->left);
        cout << root->getData() << "(" << root->getCount() << ") ";
        inorderTraversal(root->right);
    }

    void preorderTraversal(node_T<T>* root) {
        if (!root) return;
        cout << root->getData() << "(" << root->getCount() << ") ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }

    void postorderTraversal(node_T<T>* root) {
        if (!root) return;
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->getData() << "(" << root->getCount() << ") ";
    }

    void deletion(node_T<T>*& root, T d) {
        if (!root) return;
        if (root->getData() == d) {
            if (root->getCount() > 1) {
                root->decrementCount();
                return;
            }
            node_T<T>* temp = root;
            if (!root->left) {
                root = root->right;
                delete temp;
            }
            else if (!root->right) {
                root = root->left;
                delete temp;
            }
            else {
                temp = root->right;
                while (temp->left) temp = temp->left;
                root->setData(temp->getData());
                root->decrementCount();
                deletion(root->right, temp->getData());
            }
        }
        else if (root->getData() > d) {
            deletion(root->left, d);
        }
        else {
            deletion(root->right, d);
        }
        AVLTreeRebalancingDeletion(root);
    }

public:
    AVL() : root(nullptr) {}

    void insert(T d) {
        insert(root, d);
    }

    void insert(node_T<T>*& root, T d) {
        if (!root) {
            root = new node_T<T>(d);
        }
        else {
            if (root->getData() > d) {
                insert(root->left, d);
            }
            else if (root->getData() < d) {
                insert(root->right, d);
            }
            else if (root->getData() == d) {
                root->incrementCount();
            }
        }
        AVLTreeRebalancingInsertion(root);
    }

    void deletion(T d) {
        deletion(root, d);
    }

    void displayInorder() {
        inorderTraversal(root);
        cout << endl;
    }

    void displayPreorder() {
        preorderTraversal(root);
        cout << endl;
    }

    void displayPostorder() {
        postorderTraversal(root);
        cout << endl;
    }
};
