#include <vector>
#include <iostream>

using namespace std;

bool twoElementsOn(vector<int>temp){
    int odds = 0;
    for (int i = 0; i < temp.size(); i++){
        //check for two odd numbers
        if (temp.at(i) % 2 == 1){
            odds++;
        }
        if (odds >= 2){
            return true;
        }
    }
    
    return false;
}

bool twoElementsOn2(vector<int>temp){
    for (int i = 0; i < temp.size() - 1; i++){
        for (int j = i + 1; j < temp.size(); j++){
            if ( (temp.at(i) * temp.at(j)) % 2 == 1){
                return true;
            }
        }
    }
    return false;
}


int main(){
    //O(1)
    vector<int> temp = {3, 3, 2, 4, 6, 8};
    cout << twoElementsOn(temp) << "  " << twoElementsOn2(temp) << endl;
    

    
    
    //cout << evens << endl;
}


/*
 _size = 0;
        _bucket_count = next_greater_prime(bucket_count);
        _hash = hash;
        _equal = equal;
        _buckets = new HashNode * [_bucket_count];

        
Running Time Functions:
O(n) algorithm: f(n) = 5n because there are 5 operations inside the loop: %, ==, and >= are 1 function each
while ++ is functionally +=1 so it is two operations. All operations are done the amount of times the
loop is run.
O(n^2) algorithm: f(n) = 3((n-1)^2) because there are 3 operations inside the nested loop (*,%,and==) and
each of the loops are run (n-1) times.


1) What I consider an operation is Data interchanges (swaps), Comparisons (<, >, <=, >=, ==, !=),
Arithmetic Operations (+, *, -, /, pow, sqrt, etc.), but more specifically to each operation:
a) The operations for the O(n) algorithm are calling modulus, checking if that result is
equal to one, and then adding one to odds if the result is true.
b) The operations for the O(n^2) algorithm are calling modulus and cheking if the result is
equal to one.


2)
a)The best case for the O(n) algorithm is O(1) because the it checks every loop if the odds variable
is greater than or equal to 2, so if the first 2 numbers are odd it doesn't matter how long the list is,
the function will return true. The worst case for the O(n) algorithm is O(n) becuase the formula would
have to search the whole list for two odd numbers.
b) The best case for the O(n^2) algorithm is O(1) because if the first two numbers multiply to an odd number,
it doesn't matter how long a list is it will return true and stop the functions operation. The worst case for
the O(n^2) function is O(n^2) because the function will needs to multiply every number with every other number
in order to see if any of them multiply to an odd number, and to do that it will need to go through the whole
list for every number on that list.

3)
a)
The best case would be acheived by making the odd numbers the first two items on the list, the worst case would
be achieved by having only two odd numbers on the list making one of them the last item on the list
Best case example for the O(n) algorithm is:  vector<int> temp = {3, 3, 2, 4, 6, 8, 10};
Worst case example for the O(n) algorithm is: vector<int> temp = {3, 2, 4, 6, 8, 10, 3};

b)
The best case would be acheived by making the odd numbers the first two items on the list, the worst case would
be achieved by having only two odd numbers on the list making them both the last two items on the list.
Best case example for the O(n^2) algorithm is: vector<int> temp = {5, 5, 2, 4, 6, 8, 10};
Worst case example for the O(n^2) algorithm is: vector<int> temp = {2, 2, 2, 4, 6, 8, 5, 5};


4(n) + 2 because it has to run 4 operation in the loop (++ is actually +=)
n times and 2 operations outside the loop, the assignmnt and comparison operations. The worst
case for the O(n) operations is 4(n) + 2 for the same reasons, the loop would not stop if there
was already more than two odds in the loop
b) 






Question 3
**All of these answers were made with the assumption both bounds on any loop are inclusive**
a) Running Time Function: 2(n-1) + 1   Big O analysis: O(n)
b) Running Time Function: 2( [floor] (n-2)/2 [floor]) + 1      Big O analysis: O(n)
c) Running Time Function: 2(n(2(i-1))) + 1 Big O analysis: O(n^2)
d)
*/