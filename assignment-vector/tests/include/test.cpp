#include "Vector.h"
#include <iostream>

using namespace std;


int main(){
    //Vector <int>v;
    Vector <string>originalVector(3, "hello");
    Vector<string>otherVector(originalVector);
    otherVector = originalVector;
    cout << "SIZE: " << originalVector.size() << endl;
    cout <<"Capacity: " <<  originalVector.capacity() << endl;
    cout<< "Values: ";
    for (int i = 0; i < originalVector.capacity(); i++){
        cout << originalVector.at(i) << " ";
    }
    //originalVector.clear();
    cout << endl << "OTHER VECTOR: " << endl;
    cout<< "Values: ";
    for (int i = 0; i < otherVector.capacity(); i++){
        cout << otherVector.at(i) << " ";
    }
    cout << endl;
 
    cout << "FRONT: " <<  originalVector.front() << endl;
    cout << "BACK: " << originalVector.back() << endl;

}