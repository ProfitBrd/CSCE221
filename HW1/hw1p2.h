#ifndef HW1P2_H
#define HW1P2_H
#include <vector>
#include <stdexcept>

//int num_comp; //set to something in main
template <class T>
T Binary_Search(std::vector<T> &v, T x, int& num_comp) {
    int mid, low = 0;
    int high = (int) v.size()-1;
    while (low < high) {
        mid = (low+high)/2;
        if (num_comp++; v[mid] < x){
            low = mid+1;
        }
        else {
            high = mid;
        }
    }
    if (num_comp++; x == v[low]){
        return low; //Checking if actually founc
    }
    throw std::out_of_range("BRUH"); //exception: not found
}

#endif