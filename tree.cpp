#include <iostream>
#include <memory>

struct Node{
    Node* parent; //Parent of the tree
    Node* right; // left child of the tree
    Node* left;  // right child of the tree
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
    Node* root;
    
    //return new_node
    Node* new_node(const int item){
        return new Node(item);
    }
    void freememory(){

    }

public:
    Tree(): size(0),
    root(nullptr){

    }

    void insert(int number){
        Node* element = new_node(number);
        Node* parent = nullptr;
        Node* x = root;
        while( x != nullptr){
            parent = x;
            if(element->data < x->data){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }
        element->parent = parent;
        if (parent == nullptr){
            root = element;
            ++size;
        }
        else{
            if (element->data < parent->data){
                parent->left = element;
                ++size;
            }
            else{
                parent->right = element;
                ++size;
            }
        }
    }
    
    ~Tree(){

    }
};

int main(){
    Tree tree;
    tree.insert(6); //this will result in memory leak, so I have to solve this issue; in the free memory function
    return 0;

}