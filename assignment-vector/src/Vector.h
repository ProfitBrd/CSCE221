#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef> // size_t
#include <stdexcept> // std::range_error

template <class T>
class Vector {
public:
    class iterator;
private:
    size_t _capacity, _size;
    T* array;

    // You may want to write a function that grows the vector
    void grow(){ // O(1) time because of amortization
        if (_capacity == 0) {
            _capacity = 1;
        } else {
            _capacity *= 2;
        }
        T* new_array = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            new_array[i] = std::move(array[i]);
        }
        //if (array != nullptr){
        delete[] array;
        //}
        array = new_array;
        //new_array = nullptr;
    }

public:
    Vector() noexcept: _capacity(0), _size(0), array(nullptr){} //-------------------------------------------------Capacity needs to be 0???
    Vector(size_t count, const T& value): _capacity(count), _size(count), array(new T[count]){
        for (size_t i = 0; i < count; i++){
            array[i] = value;
        }
    }
    explicit Vector(size_t count): _capacity(count), _size(count), array(new T[count]){
        for (int i = 0; i < count; i++){
            array[i] = T(); //default value for type used
        }
    }
    Vector(const Vector& other): _capacity(other._capacity), _size(other._size), array(new T[other._capacity]){
        for (size_t i = 0; i < other._size; i++){
            array[i] = other.array[i];
        }
    }
    Vector(Vector&& other) noexcept: _capacity(other._capacity), _size(other._size), array(other.array){ //-------------------------------------------------------------No Work
        //this->array = other.array;
        //this->_size = other._size;
        //this->_capacity = other._capacity;
        other.array = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    ~Vector(){
        delete[] array;
    }

    Vector& operator=(const Vector& other){
        if(_capacity != other._capacity){
            if (array != nullptr){
                delete[] array;
            }
            array = new T[other._capacity];
            
        }

        //array = new T[other._capacity];
        for (size_t i = 0; i < other._size; i++){
            array[i] = other.array[i];
        }

        _size = other._size;
        _capacity = other._capacity;

        return *this;
    }

    Vector& operator=(Vector&& other) noexcept{
        if (this == &other) { return *this; } // self assignment
        if (this->array != nullptr){ //doesn't technically need
            delete[] this->array;
        }
        this->array = other.array;
        this->_size = other._size;
        this->_capacity = other._capacity;
        other.array = nullptr;
        return *this;
    }

    iterator begin() noexcept{ // -----------------------------------------------------------------------Need to make iterator class first
        /*if (_size == 0){
            return iterator(nullptr);
        }*/
        //else{
        return iterator(array);
        //}
    }
    iterator end() noexcept{ // -----------------------------------------------------------------------Need to make iterator class first
        return iterator(array + _size);
    }

    [[nodiscard]] bool empty() const noexcept{
        if (_size == 0){
            return true;
        }
        else{
            return false;
        }
    }
    size_t size() const noexcept{return _size;}
    size_t capacity() const noexcept{return _capacity;}

    T& at(size_t pos){
        if (!(pos < size())){
            throw std::out_of_range("Accessing out of bounds!");
        }
        else{
            return array[pos];
        }
    }
    const T& at(size_t pos) const{
        if (!(pos < size())){
            throw std::out_of_range("Accessing out of bounds!");
        }
        else{
            return array[pos];
        }
    }
    T& operator[](size_t pos){return array[pos];}
    const T& operator[](size_t pos) const{return array[pos];}
    T& front(){return this->at(0);}
    const T& front() const{return this->at(0);}
    T& back(){
        if (_size == 0){
            return this->at(0);
        }
        else{
            return this->at(_size - 1);
        }
    }
    const T& back() const{
        if (_size == 0){
            return this->at(0);
        }
        else{
            return this->at(_size - 1);
        }
    }

    void push_back(const T& value){
        while (_size >= _capacity) {
            grow();
        }
        array[_size] = value;
        _size++;
    }
    void push_back(T&& value){ // ---------------------------------------------------------------------------wrong
        while (_size >= _capacity) {
            grow();
        }
        array[_size] = std::move(value);
        _size++;
    }
    void pop_back(){
        _size--;
    };

    iterator insert(iterator pos, const T& value){
        ptrdiff_t insertIndex = pos - begin(); //find the difference in position b/w the given position and begin and get a value

        //grow if size > capacity
        while (_size >= _capacity){
            grow();
        }
        //for i != the position you calculated, move the value to the the next place up
        for (ptrdiff_t i = _size; i > insertIndex; i--){
            array[i] = std::move(array[i - 1]);
        }
        _size++; //size has now increased
        array[insertIndex] = value; //finally, set the positions value to value
        iterator temp(array+insertIndex); //create a new iterator at array's location in case grow was used (hence deleting the place and creating it somewhere else completely)
        return temp;
    }
    iterator insert(iterator pos, T&& value){
        ptrdiff_t insertIndex = pos - begin(); //find the difference in position b/w the given position and begin and get a value

        //grow if size > capacity
        while (_size >= _capacity){
            grow();
        }
        //for i != the position you calculated, move the value to the the next place up
        for (ptrdiff_t i = _size; i > insertIndex; i--){
            array[i] = std::move(array[i - 1]);
        }
        _size++; //size has now increased
        array[insertIndex] = std::move(value); //finally, set the positions value to value
        iterator temp(array+insertIndex); //create a new iterator at array's location in case grow was used (hence deleting the place and creating it somewhere else completely)
        return temp;
    }
    iterator insert(iterator pos, size_t count, const T& value){
        ptrdiff_t insertIndex = pos - begin(); //find the difference in position b/w the given position and begin and get a value

        //grow if size > capacity
        while (_size + count > _capacity){
            grow();
        }
        //for i > the position you calculated, move the value to the the next place up
        for (ptrdiff_t i = _size + count - 1; i > insertIndex + count - 1; i--){
            array[i] = std::move(array[i - count]);
        }
        _size += count; //size has now increased by count
        for (ptrdiff_t i = insertIndex; i < insertIndex + count; i++){
            array[i] = value;
        }
        iterator temp(array+insertIndex); //create a new iterator at array's location in case grow was used (hence deleting the place and creating it somewhere else completely)
        return temp;
    }
    iterator erase(iterator pos){
        ptrdiff_t insertIndex = pos - begin(); //find the difference in position b/w the given position and begin and get a value
        //ptrdiff_t sub = pos - begin();
        
        
        for (ptrdiff_t i = insertIndex; i < _size - 1; i++){
            array[i] = std::move(array[i + 1]);
        }
        _size--; //size has now decreased
        //iterator temp(array + sub); //create a new iterator at array's location in case grow was used (hence deleting the place and creating it somewhere else completely)
        return pos;
    }
    iterator erase(iterator first, iterator last);
    
    class iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;
    private:
        // Add your own data members here
        T* ptr;
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
    public:
        iterator(): ptr(){};
        // Add any constructors that you may need
        iterator(T* inputPointer): ptr(inputPointer){}
        //return private variable pointer
        //const pointer getPtr(){return ptr;}
        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept{
            return *ptr;
        }
        [[nodiscard]] pointer operator->() const noexcept{
            return ptr;
        }

        // Prefix Increment: ++a
        iterator& operator++() noexcept{
            ptr++;
            return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept{
            iterator prev(ptr);
            ptr++;
            return prev;
        }
        // Prefix Decrement: --a
        iterator& operator--() noexcept{
            ptr--;
            return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept{
            iterator prev(ptr);
            ptr--;
            return prev;
        }

        iterator& operator+=(difference_type offset) noexcept{
            ptr = ptr + offset;
            return *this;
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept{
            iterator temp = iterator(ptr);
            temp.ptr += offset;
            return temp;
        }
        
        iterator& operator-=(difference_type offset) noexcept{ //--------------------------------------------------
            ptr = ptr - offset;
            return *this;
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept{//--------------------------------------------
            iterator temp = iterator(ptr);
            temp.ptr -= offset;
            return temp;
        }
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept{
            difference_type x = ptr - rhs.ptr;
            if (x < 0){
                x *= -1;
            }
            return x;
        }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept{ //---------------------------------------------
            return *(ptr + offset); //dereference ptr after skipping forward offset spaces
        }

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept{
            if (ptr == rhs.ptr){
                return true;
            }
            else{
                return false;
            }
        }
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept{
            if (ptr != rhs.ptr){
                return true;
            }
            else{
                return false;
            }
        }
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept{
            if (ptr < rhs.ptr){
                return true;
            }
            else{
                return false;
            }
        }
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept{
            if (ptr > rhs.ptr){
                return true;
            }
            else{
                return false;
            }
        }
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept{
            if (ptr <= rhs.ptr){
                return true;
            }
            else{
                return false;
            }
        }
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept{
            if (ptr >= rhs.ptr){
                return true;
            }
            else{
                return false;
            }
        }
    };



    void clear() noexcept{
        _size = 0;
        delete[] array;

        //create a new string and assign
        array = new T[_capacity];
    }
};

template <class T>
[[nodiscard]] typename Vector<T>::iterator operator+(typename Vector<T>::iterator::difference_type offset, typename Vector<T>::iterator iterator) noexcept{
    return offset+iterator;
}



/*

//default constructor
template <class T>
Vector<T>::Vector() noexcept

//default constructor with amount of provided values
template <class T>
Vector<T>::Vector(size_t count, const T& value)
*/

//default constructor with items count
/*
template <class T>
Vector<T>::Vector(size_t count): _capacity(count), _size(count), array(new T[count]){}
*/
/*
//destructor
template <class T>
Vector<T>::~Vector(){
    delete[] array;
}

//return size
template <class T>
size_t Vector<T>::size() const noexcept{return _size;}

//return capacity
template <class T>
size_t Vector<T>::capacity() const noexcept{return _capacity;}

//explicit constructor with default value MIGHT NEED TO ADD BACK EXPLICIT
template <class T>
Vector<T>::Vector(size_t count)

//copy constructor
template <class T>
Vector<T>::Vector(const Vector& other):_size(other._size), _capacity(other._capacity), array(new T[other._capacity]){
    for (int i = 0; i < other._size; i++){
        array[i] = other.array[i];
    }
}

//move constructor
template <class T>
Vector<T>::Vector(Vector&& other) noexcept{
    _size = other._size;
    _capacity = other._capacity;
    array = other.array;
    other.array = nullptr;
    other._size = 0;
    other._capacity = 0;
}



//grow function
template <class T>
void Vector<T>::grow(){ // O(1) time because of amortization
    T* tempArray = new T[_capacity*2];
    for (int i = 0; i < _capacity; i++){
        tempArray[i] = array[i];
    }

    _capacity = _capacity * 2;
    delete[] array; 
    array = tempArray;
}
*/
/*
//operator= overload function
template <class T>
Vector<T>::Vector& operator=(const Vector& other){
    delete[] array;
    _size = other._size;
    _capacity = other._capacity;
    array = new T[other._capacity];
    for (int i = 0; i < other._size; i++){
        array[i] = other.array[i];
    }
}
*/

/*
//front function ----------------------------------------------------------------------------------What error to throw if function does not hav
template <class T>
T& Vector<T>::front(){return array[0];}

//front function overload
template <class T>
const T& Vector<T>::front() const{return array[0];}

//back function
template <class T>
T& Vector<T>::back(){return array[_size - 1];}

//back function overload
template <class T>
const T& Vector<T>::back() const{return array[_size - 1];}


//.at() function
template <class T>
T& Vector<T>::at(size_t pos){
    
}

//.at() function const overload
template <class T>
const T& Vector<T>::at(size_t pos) const{
    
}


//clear --------------------------------------------------------------------------------------- Ask TA???????
template <class T>
void Vector<T>::clear() noexcept{
    //delete everything inside with a try except and then delete the array and create a new array with size capacity
    for (int i = 0; i < _size; i++){
        delete array[i];
    }
    _size = 0;
}
*/


















#endif