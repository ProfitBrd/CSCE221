#include "hw1p2.h"
#include <vector>
#include <iostream>

using namespace std;

int main(){
    vector<int> h;
    for (int i = 1; i < 2048; i++){
        h.push_back(i);
    }

   
    int num_comp = 0;
    int x = Binary_Search<int>(h, 2047, num_comp);


    cout << "FOUND NUMBER Index:   " << x << endl;
    cout << "NUM_COMP:   " << num_comp << endl;


}

/*
3)
i. num_comp = 5
ii. num_comp = 5
iii. num_comp = 5
My conclusion is that the binary search does not stop until it has narrowed the list down to one item, making it
incredibly inefficient

(c)
1 comparison - 1 items
2 comparisons - 2 items
3 comparisons - 4 items
4 comparisons - 8 items
5 comparisons - 16 items
...
12 comparisons - 2048 items


(d)

(e) The inverse of the formula (if n is the number of comparisons) is 2^(n-1) because the function starts at 1 comparison whereas 2^n 
would start at 0 comparisons. In order to fix this, we have to subtract one from the vector size before setting it to be the power of 2.
The correct function log>2<(x)+1 which is just the reverse of the above function.

(f) We can modify our formula by just adding the floor function to the outside of the equation we found because in the size of the vector,
the number only increases when the size of the vector increases by a factor of 2, so everything in between those numbers should be reduced
to the highest power of two before it on the number line.

(g) I do think the number of comparisons would be the same, because double and string can still be converted to numerical values, and as long
as a list has numerical values binary search can be used on it effectively. Strings and Doubles are essentially more complicated ints in terms
of converting them to a usable form for binary search, but once they are converted to numerical form binary search wouldn't take any extra operations
to find things than a vector of ints.

(h) Big O asymptotic notation for the binary search algorithm is O(log(n)) because the binary search cuts the list avaliable to search in half,
meaning that log is the appropriate equation to use as it is reverse exponent.





*/