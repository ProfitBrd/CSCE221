#include <iostream>

template<typename T>
struct Node{
    Node* next;
    T obj;

    Node(T obj, Node* next = nullptr):obj(obj), next(next){}
};


template<typename T>
int count_node(Node<T>* temp, int count = 0){
    if (temp == nullptr){
        return count;
    }
    return (count_node(temp->next, count + 1));
}

int main(){
    Node<int>* node5 = new Node<int>(1, nullptr);
    Node<int>* node4 = new Node<int>(1, node5);
    Node<int>* node3 = new Node<int>(1, node4);
    Node<int>* node2 = new Node<int>(1, node3);
    Node<int>* node1 = new Node<int>(1, node2);

    std::cout << count_node(node1) << std::endl;
}