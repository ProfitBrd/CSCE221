#pragma once

#include <functional>
#include <utility>
#include <vector>

template <class T, class Container = std::vector<T>, class Compare = std::less<T>>
class PriorityQueue {
public:
    using value_compare = Compare;
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

private:
    Container c;
    value_compare comp;

    size_type parent(size_type index) { return (index - 1) / 2; }
    size_type left_child(size_type index) { return 2 * index + 1; }
    size_type right_child(size_type index) { return 2 * (index + 1); }
    bool is_internal(size_t index) { return left_child(index) < c.size(); }
    bool is_leaf(size_t index) { return left_child(index) >= c.size(); }

    //use std move---------------------------------------------------------------------------------------------------------
    /**
     * @brief Recursively (or Iteratively) swap the value at index up the heap until it is in the correct position.
     * 
     * @note This is a max heap, so assume Compare is less, but promote the larger value.
     * 
     * Used by push
     * 
     * O(log(size()))
     * 
     * @param index the current position to swap upwards
     */
    void upheap(size_type index) {
        //TODO
        if (index <= 0){
            return;
        }
        if (comp(c[parent(index)], c[index])){
            //swap
            std::swap(c[parent(index)], c[index]);
            /*T parentValue = std::move(c[parent(index)]); //gets parent's value
            c[parent(index)] = std::move(c[index]); //swaps parents value to new value
            c[index] = std::move(parentValue); //completes swap
            */
            //call recursively
            upheap(parent(index));
        }
        return;
        
        //find formula that moves the index up the heap while swapping values
    }
    
    /**
     * @brief Recursively swap the value at index down the heap until it is in the correct position.
     * 
     * @note This is a max heap, so assume Compare is less, so promote the larger value.
     * 
     * Used by pop
     * 
     * O(log(size()))
     * 
     * @param index the current position to swap downwards
     */
    void downheap(size_type index) {
        // TODO
        if (index >= c.size()){
            return;
        }
        if (is_leaf(index)){ //if the current node has no children, stop
            return;
        }
        else if (right_child(index) >= c.size()){//right child no exist
            if (comp(c[index], c[left_child(index)])){ //check if we need to swap
                
                std::swap(c[left_child(index)], c[index]);
                /*T childValue = c.at(left_child(index)); //gets parent's value
                c.at(left_child(index)) = c.at(index); //swaps parents value to new value
                c.at(index) = childValue; //completes swap
                */
                downheap(left_child(index));//---------------------------------------------------------
            }
            
        }
        else{
            if (comp( c.at(left_child(index)), c.at(right_child(index)) )){
               if (comp(c[index], c[right_child(index)])){
                    std::swap(c[right_child(index)], c[index]);

                    //call recursively
                    downheap(right_child(index));
                } 
                
                
            }
            else{
                if (comp(c[index], c[left_child(index)])){
                    std::swap(c[left_child(index)],c[index]);
                    /*T childValue = c.at(left_child(index)); //gets parent's value
                    c.at(left_child(index)) = c.at(index); //swaps parents value to new value
                    c.at(index) = childValue; //completes swap
                    */
                    downheap(left_child(index));//---------------------------------------------------------
                }
                
            }
        }
        return;
    }

public:
    PriorityQueue() = default;
    PriorityQueue( const PriorityQueue& other ) = default;
    PriorityQueue( PriorityQueue&& other ) = default;
    ~PriorityQueue() = default;
    PriorityQueue& operator=( const PriorityQueue& other ) = default;
    PriorityQueue& operator=( PriorityQueue&& other ) = default;

    /**
     * @brief Return a const reference to the element at the top of the heap.
     * 
     * O(1)
     * 
     * @return const_reference to the element at the top of the heap.
     */
    const_reference top() const { return c.front();}

    /**
     * @brief Return whether the heap is empty. This is the same as whether the underlying container, c, is empty.
     * 
     * O(1)
     * 
     * @return true c is empty
     * @return false c is not empty
     */
    bool empty() const { return c.empty(); }

    /**
     * @brief Return the number of elements in the heap. This is the same as the number of elements in the underlying container, c.
     * 
     * O(1)
     * 
     * @return size_type of the number of elements in the heap
     */
    size_type size() const { return c.size(); }
	
    /**
     * @brief Inserts element and sorts the underlying container, c.
     * 
     * Uses upheap
     * 
     * O(log(size())) 
     * 
     * @param value inserted by copying into c 
     */
    void push( const value_type& value ) {
        // TODO
        c.push_back(value);
        upheap(c.size()-1);

    }

    /**
     * @brief Inserts element and sorts the underlying container, c.
     * 
     * Uses upheap
     * 
     * O(log(size())) 
     * 
     * @param value inserted by moving into c 
     */
	void push( value_type&& value ) {
        // TODO
        c.push_back(std::move(value));
        upheap(c.size()-1);
    }

    /**
     * @brief Removes the top element.
     * 
     * Uses downheap
     * 
     * O(log(size())) 
     * 
     */
    void pop() {
        // TODO
        c.front() = std::move(c.back()); //was getting wrong, had to std::move every time
        c.pop_back();
        downheap(0);
    }
};