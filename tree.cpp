// Copyright 2020 Mohsan

#include <iostream>
#include <memory>

struct Node{
    Node* parent;   // Parent of the tree
    Node* right;    // left child of the tree
    Node* left;     // right child of the tree
    int data;       // data containing in the node

    explicit Node(const int item):
        parent(nullptr),
        right(nullptr),
        left(nullptr),
        data(item){
            // this will stay empty
        }
};



class Tree{
 private:
    std::size_t size;
    Node* root;

    // return new_node
    Node* new_node(const int item) {
        return new Node(item);
    }
    void freememory(Node* node) {
        if (node == nullptr) {
            return;
        } else {
            freememory(node->right);
            freememory(node->left);
            delete node;
        }
    }

 public:
    Tree(): size(0),
    root(nullptr) {
    }
    void insert(int number) {
        Node* element = new_node(number);
        Node* parent = nullptr;
        Node* x = root;

        while ( x != nullptr ) {
            parent = x;
            if (element->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        element->parent = parent;
        if (parent == nullptr) {
            root = element;
            ++size;
        } else {
            if (element->data < parent->data) {
                parent->left = element;
                ++size;
            } else {
                parent->right = element;
                ++size;
            }
        }
    }
    const Node* getRoot() const{
        return root;
    }
    const Node* search(const Node* node, int key) {
        if (node == nullptr || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return search(node->left, key);
        }else { 
            return search(node->right, key);
        }
    }

    bool isEmpty() const {
        if (root == nullptr) {
            return true;
        }
        return false;
    }
    ~Tree(){
        if (!isEmpty()){
            freememory(root);
        }
    }
};

int main() {
    Tree tree;
    tree.insert(6);
    tree.insert(5);
    const Node* item = tree.search(tree.getRoot(), 5);
    if(item){
        std::cout << "item found" << std::endl;
    }
    else{
        std::cout << "Item does not find" << std::endl;
    }
    return 0;
}
