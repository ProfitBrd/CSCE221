#include <iostream>

template<typename T>
struct Node{
    Node<T> *left, *right;
    T obj;

    Node (T obj, Node<T>* left = nullptr, Node<T>* right = nullptr):obj(obj), left(left), right(right){}
};

template<typename T>
int count_filled_nodes(const Node<T>* node){
    if (!node) return 0;
    if (node->right != nullptr && node->left != nullptr){
        return (1 + count_filled_nodes(node->left) + count_filled_nodes(node->right));
    }
    else if (node->right != nullptr){
        return (count_filled_nodes(node->right));
    }
    else if (node->left != nullptr){
        return (count_filled_nodes(node->left));
    }
    else{
        return 0;
    }
}

int main(){
    



    return 0;
}