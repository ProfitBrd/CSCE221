#pragma once

#include <functional> // std::less
#include <iterator>

// This is C++ magic which will allows our function
// to default to using a < b if the comparator arg
// is unspecified. It uses defines std::less<T>
// for the iterator's value_type.
//
// For example: if you have a vector<float>, the 
// iterator's value type will be float. std::less 
// will select the < for sorting floats as the 
// default comparator.

namespace sort {
	template<typename RandomIter>
	using less_for_iter = std::less<typename std::iterator_traits<RandomIter>::value_type>;

	/* Efficiently swap two items - use this to implement your sorts */
	template<typename T>
	void swap(T & a, T & b) noexcept { 
		T temp = std::move(a);
		a = std::move(b);
		b = std::move(temp);
	 }

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void bubble(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		// Random access iterators have the same traits you defined in the Vector class
		// For instance, difference_type represents an iterator difference
		// You may delete the types you don't use to remove the compiler warnings
		using _it             = std::iterator_traits<RandomIter>;
		using difference_type = typename _it::difference_type;
		using value_type      = typename _it::value_type;
		using reference       = typename _it::reference;
		using pointer         = typename _it::pointer;

		// COMPLETE

		for (difference_type i = (begin - begin) + 1; i < end - begin; i++) { //(int k = 1; k < n; k++) k is counting up, n is the end
		bool cont = false;
			for (RandomIter j = begin; j < end - i; j++){  //j searches the part of the list we haven't covered
				if ( comp(*(j+1), *(j)) ) {
					swap( *(j+1), *(j)); // swap A[j] and A[j+1]
					cont = true;
				}
			}
			if (!cont) break; // stop sorting
		}
	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void insertion(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) {
		for (int k = (begin - begin) + 1; k < (end - begin); k++){ //int k = 1; k < n; k++  
			RandomIter j = begin + k; //new iterator at the place we are trying to put into the ordered part
			//int tmp = *(j); //temp is the value at the place we are testing
			for( ; j > begin && comp(*j, *(j-1)); j--) //checks the element before, if its less than the element we are on it swaps it
				swap(*(j), *(j-1));
			}

	}

	template<typename RandomIter, typename Comparator = less_for_iter<RandomIter>>
	void selection(RandomIter begin, RandomIter end, Comparator comp = Comparator{}) { 
		for (int k = begin-begin; k < (end-begin)-1; k++)
		{
			RandomIter currentPlace = k + begin;
			RandomIter index = k + begin;
			//int index = k;
			for (int i = k+1; i < (end-begin); i++){
				if (comp (*(begin + i), *(index))){//(A[i] < A[index]){
					index = i + begin;
				}
			}
			swap(*(index), *(currentPlace));
			/*
			int tmp = A[k]; // swap A[k] and A[index]
			A[k] = A[index];
			A[index] = tmp;
			*/
		}

	 }
}
