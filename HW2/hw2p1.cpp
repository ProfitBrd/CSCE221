#include <iostream>
#include <list>




std::list <int> intersection (const std::list<int>& l1, const std::list<int>& l2){
    auto i = l1.begin(); //iterator
    auto j = l2.begin();
    std::list<int> newList;
    while (i != l1.end() && j != l2.end()){
        if ((*i) > (*j)){
            j++;
        }
        else if((*i) < (*j)){
            i++;
        }
        else if ((*i) == (*j)){
            newList.push_back(*i);
            i++;
            j++;
        }
    }
    return newList;
}


int main(){
    std::list<int> newList1;
    newList1.push_back(5);
    newList1.push_back(9);
    newList1.push_back(55); //3 elements

    std::list<int> newList2;
    newList2.push_back(5);
    newList2.push_back(7);
    newList2.push_back(8);
    newList2.push_back(9);
    newList2.push_back(10); //5 elements

    std::list<int> newList3;
    newList3 = intersection(newList1, newList2);
    
    std::cout << "First List:" << std::endl;
    for (auto i = newList3.begin(); i != newList3.end(); i++){
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    std::list<int> newList4;
    newList4.push_back(5);
    newList4.push_back(8);
    newList4.push_back(10);
    newList4.push_back(13);
    newList4.push_back(69);

    std::list<int> newList5;
    newList5.push_back(8);
    newList5.push_back(10);
    newList5.push_back(25);
    newList5.push_back(69);

    std::list<int> newList6;
    newList6 = intersection(newList4, newList5);

    std::cout << "Second List:" << std::endl;
    for (auto i = newList6.begin(); i != newList6.end(); i++){
        std::cout << *i << " ";
    }
    std::cout << std::endl;
    return 0;
}
