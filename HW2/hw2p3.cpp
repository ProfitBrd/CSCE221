#include <vector>
#include <iostream>

int find_max_value(std::vector<int> array, int max, int index){
    if (array.at(index) == array.front()){
        if (array.at(index) > max){
            return array.at(index);
        }
        else{
            return max;
        }
    }
    if (array.at(index) > max){
        int temp = array.at(index);
        return find_max_value(array, temp, index-1);
    }   
    else{
        return find_max_value(array, max, index-1);
    }

    
    
    /*
    if (array.empty()){ //base case
        return val;
    }
    
    if (array.front() > val){ //if the front number in the array is greater, mak that the new greatest value
        int temp = array.front();
        array.erase(array.begin()); //erase the first element
        return find_max_value(array, temp);
    }
    else{
        array.erase(array.begin()); //erase the first element
        return find_max_value(array, val);
    }
    */
    

}


int main(){
    std::vector<int> array {10,20,50,40,30,40,9000,1000,40,300};
    int temp2 = find_max_value(array, 0, array.size()-1);
    std::cout << temp2 << std::endl;
    return 0;
}