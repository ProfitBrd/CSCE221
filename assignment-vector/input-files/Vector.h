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
        int* new_array = new int[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        
        /*if (_capacity == 0){ //--------------------------------------------------------------becuase capacity = 0 for one constructor
            _capacity++;
        }
        T* tempArray = new T[_capacity*2];
        for (int i = 0; i < _size; i++){
            tempArray[i] = array[i];
        }

        _capacity = _capacity * 2;
        delete[] array;
        array = tempArray;*/
    }

public:
    Vector() noexcept: _capacity(0), _size(0), array(new T[1]){} //-------------------------------------------------Capacity needs to be 0???
    Vector(size_t count, const T& value): _capacity(count), _size(count), array(new T[count]){
        for (int i = 0; i < count; i++){
            array[i] = value;
        }
    }
    explicit Vector(size_t count): _capacity(count), _size(count), array(new T[count]){
        for (int i = 0; i < count; i++){
            array[i] = T(); //default value for type used
        }
    }
    Vector(const Vector& other):_size(other._size), _capacity(other._capacity), array(new T[other._capacity]){
        for (int i = 0; i < other._size; i++){
            array[i] = other.array[i];
        }
    }
    Vector(Vector&& other) noexcept{ //-------------------------------------------------------------No Work
        _size = other._size;
        _capacity = other._capacity;
        array = other.array;
        //std::cout << "HELLO" << std::endl;
        other.array = new T[1];
        other._size = 0;
        other._capacity = 1;
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
        for (int i = 0; i < other._size; i++){
            array[i] = other.array[i];
        }

        _size = other._size;
        _capacity = other._capacity;
    }

    Vector& operator=(Vector&& other) noexcept;

    iterator begin() noexcept{ // -----------------------------------------------------------------------Need to make iterator class first
        //return array[0];
    }
    iterator end() noexcept{ // -----------------------------------------------------------------------Need to make iterator class first
        /*if (_size == 0){
            return array[0];
        }
        else{
            return array[_size - 1];
        }*/
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
            throw std::range_error("Accessing out of bounds!");
        }
        else{
            return array[pos];
        }
    }
    const T& at(size_t pos) const{
        if (!(pos < size())){
            throw std::range_error("Accessing out of bounds!");
        }
        else{
            return array[pos];
        }
    }
    T& operator[](size_t pos){return array[pos];}
    const T& operator[](size_t pos) const{return array[pos];}
    T& front(){return array[0];}
    const T& front() const{return array[0];}
    T& back(){
        if (_size == 0){
            return array[0];
        }
        else{
            return array[_size - 1];
        }
    }
    const T& back() const{
        if (_size == 0){
            return array[0];
        }
        else{
            return array[_size - 1];
        }
    }

    void push_back(const T& value){
        while (_size >= _capacity) {
            grow();
        }
        array[_size] = value;
        _size++;
        /*while (_size >= _capacity){
            grow();
        }
        array[_size] = value;
        _size++;
        */
    }
    void push_back(T&& value){
        while (_size >= _capacity) {
            grow();
        }
        array[_size] = value;
        _size++;
    }
    void pop_back(){
        _size--;
    };

    iterator insert(iterator pos, const T& value);
    iterator insert(iterator pos, T&& value);
    iterator insert(iterator pos, size_t count, const T& value);
    iterator erase(iterator pos);
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
        iterator();
        // Add any constructors that you may need
        iterator(T* inputPointer): ptr(inputPointer){}
        // This assignment operator is done for you, please do not add more
        iterator& operator=(const iterator&) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept{
            //return &ptr;
        }
        [[nodiscard]] pointer operator->() const noexcept{
            return ptr;
        }

        // Prefix Increment: ++a
        iterator& operator++() noexcept{
            //return ++(*ptr);
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept{
            //return (*ptr)++;
        }
        // Prefix Decrement: --a
        iterator& operator--() noexcept{
            //return --(*ptr);
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept{
            //return (*ptr)--;
        }

        iterator& operator+=(difference_type offset) noexcept;
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept;
        
        iterator& operator-=(difference_type offset) noexcept;
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept;
        [[nodiscard]] difference_type operator-(const iterator& rhs) const noexcept;

        [[nodiscard]] reference operator[](difference_type offset) const noexcept;

        [[nodiscard]] bool operator==(const iterator& rhs) const noexcept;
        [[nodiscard]] bool operator!=(const iterator& rhs) const noexcept;
        [[nodiscard]] bool operator<(const iterator& rhs) const noexcept;
        [[nodiscard]] bool operator>(const iterator& rhs) const noexcept;
        [[nodiscard]] bool operator<=(const iterator& rhs) const noexcept;
        [[nodiscard]] bool operator>=(const iterator& rhs) const noexcept;
    };



    void clear() noexcept{
        _size = 0;
        delete[] array;

        //create a new string and assign
        array = new T[_capacity];
    }
};

template <class T>
[[nodiscard]] typename Vector<T>::iterator operator+(typename Vector<T>::iterator::difference_type offset, typename Vector<T>::iterator iterator) noexcept;



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