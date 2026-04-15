// Lab11/main.cpp
// Лабораторна робота №11. Бінарне дерево пошуку (BST).

#include <iostream>
#include <windows.h>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* newNode(int val) {
    Node* n = new Node;
    n->data = val;
    n->left = n->right = nullptr;
    return n;
}

Node* insert(Node* root, int val) {
    if (!root) return newNode(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else if (val > root->data)
        root->right = insert(root->right, val);
    return root;
}

bool search(Node* root, int val) {
    if (!root) return false;
    if (val == root->data) return true;
    if (val < root->data) return search(root->left, val);
    return search(root->right, val);
}

Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int val) {
    if (!root) return nullptr;
    if (val < root->data) {
        root->left = deleteNode(root->left, val);
    }
    else if (val > root->data) {
        root->right = deleteNode(root->right, val);
    }
    else {
        if (!root->left) {
            Node* tmp = root->right;
            delete root;
            return tmp;
        }
        if (!root->right) {
            Node* tmp = root->left;
            delete root;
            return tmp;
        }
        // Два нащадки — замінюємо мінімальним з правого піддерева
        Node* minNode = findMin(root->right);
        root->data = minNode->data;
        root->right = deleteNode(root->right, minNode->data);
    }
    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Node* root = nullptr;
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };
    for (int v : values)
        root = insert(root, v);

    cout << "=== Бінарне дерево пошуку (BST) ===\n";
    cout << "Вставлено: 50 30 70 20 40 60 80\n\n";

    cout << "Inorder (відсортовано):   ";
    inorder(root);
    cout << "\n";

    cout << "Preorder:                 ";
    preorder(root);
    cout << "\n";

    cout << "Postorder:                ";
    postorder(root);
    cout << "\n\n";

    cout << "Пошук 40: " << (search(root, 40) ? "знайдено" : "не знайдено") << "\n";
    cout << "Пошук 99: " << (search(root, 99) ? "знайдено" : "не знайдено") << "\n\n";

    root = deleteNode(root, 30);
    cout << "Після видалення 30:\n";
    cout << "Inorder: ";
    inorder(root);
    cout << "\n";

    freeTree(root);
    return 0;
}
