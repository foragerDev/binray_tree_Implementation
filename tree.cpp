#include <iostream>
#include <memory>

struct Node{
    int* parent; //Parent of the tree
    int* right; // left child of the tree
    int* left;  // right child of the tree
    int data;     // data containing in the node
    Node(const int item):
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
    int* root;
    
    //return new_node
    Node* new_node(const int item){
        return new Node(item);
 }

public:
    Tree(): size(0),
    root(nullptr){

    }
    
    ~Tree(){

    }
};