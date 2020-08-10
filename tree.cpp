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

    void Transplant(Node* from, Node* with){
        if (from->parent == nullptr) { // if tree is already empty
            root = with;
        }
        if (from == from->left->parent) { // if tree  is the left child of its parents
            from->left->parent = with;
        }
        if (from == from->right->parent) { // if tree is the right child of its parents
            from->right->parent = from;
        }
        if (with != nullptr) {  // 
            with->parent = from->parent;
        }
    }

    Node* minimum(Node* node){
        while (node->left == nullptr){
            node = node->left;
        }
        return node;
    }

    Node* getRoot() {
        return root;
    }

 public:
    Tree(): size(0),
    root(nullptr) {
    }

    // Insert the element in the tree 
    void insert(int number) {
        Node* element = new_node(number);
        Node* parent = nullptr;
        Node* x = root;

        // find the parent
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

    // returns the root of the tree.
    const Node* getRoot(int) const {
        return root;
    }

    // Search the particular element and returs its node if exists
    Node* search(Node* node, int key) {
        if (node == nullptr || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    const Node* search(const Node* node, int key) {
        if (node == nullptr || key == node->data) {
            return node;
        }
        if (key < node->data) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    // Wheater tree is empty of not
    bool isEmpty() const {
        if (root == nullptr) {
            return true;
        }
        return false;
    }

    // Return the node with the maximu value
    const Node* maximum(const Node* node) const {
        while (node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    

    // returns the node with the minimum value
    const Node* minimum(const Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void delete_node(int item){
        Node* data = search(root, item); // Search for the data item in the tree

        if (data == nullptr){ // If data item is present in the tree 
            if (data->left == nullptr){  // if the deletion point does not have left side
                Transplant(data, data->right);
            }
            if (data->right == nullptr) {
                Transplant(data, data->left);
            }

            else {
                Node* successor = minimum(data->right);
                if (successor->parent != data) {
                    Transplant(successor, successor->right);
                    successor->right = data->right;
                    successor->right->parent = successor;
                }
                Transplant(data, successor);
                successor->left = data->left;
                successor->left->parent = successor;
                delete data;
            }
        }
    }


    // Free the memory allocated on the heap
    ~Tree(){
        if (!isEmpty()) {
            freememory(root);
        }
    }
};

int main() {
    Tree tree;
    tree.insert(44);
    tree.insert(55);
    tree.insert(6);
    tree.insert(5);
    tree.insert(7);
    const Node* item = tree.search(tree.getRoot(0), 5);
    if (item) {
        std::cout << "item found" << std::endl;
    } else {
        std::cout << "Item does not find" << std::endl;
    }
    const Node* maximum = tree.maximum(tree.getRoot(0));
    std::cout << maximum->data << std::endl;
    const Node* minimum = tree.minimum(tree.getRoot(0));
    std::cout << minimum->data << std::endl;
    tree.delete_node(44);
    const Node* another_item = tree.search(tree.getRoot(0), 44);
    if ( another_item ){
        std::cout << "item found" << std::endl;
    } else {
        std::cout << "Item did not found " << std::endl;
    }
    return 0;
}
