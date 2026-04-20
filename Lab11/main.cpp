#include <iostream>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node;
    }

    bool search(Node* node, int val) {
        if (!node) return false;
        if (val == node->data) return true;
        return (val < node->data) ? search(node->left, val) : search(node->right, val);
    }

    Node* findMin(Node* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = remove(node->left, val);
        else if (val > node->data) node->right = remove(node->right, val);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(root); }

    void insert(int val) { root = insert(root, val); }
    bool search(int val) { return search(root, val); }
    void remove(int val) { root = remove(root, val); }

    void printInorder() { inorder(root); cout << endl; }
    void printPreorder() { preorder(root); cout << endl; }
    void printPostorder() { postorder(root); cout << endl; }
};

int main() {
    BinarySearchTree bst;
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };

    for (int v : values) bst.insert(v);

    cout << "BST Traversals:\n";
    cout << "Inorder:   "; bst.printInorder();
    cout << "Preorder:  "; bst.printPreorder();
    cout << "Postorder: "; bst.printPostorder();

    cout << "\nSearch 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 99: " << (bst.search(99) ? "Found" : "Not Found") << endl;

    cout << "\nRemoving 30..." << endl;
    bst.remove(30);
    cout << "Inorder after remove: "; bst.printInorder();

    return 0;
}
