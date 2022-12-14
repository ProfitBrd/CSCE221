#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {
    private:
    struct Node {
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() { node = nullptr; };
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            // TODO
            return node->data;
        }
        pointer operator->() const {
            // TODO
            return &(node->data);
        }

        // Prefix Increment: ++a
        basic_iterator& operator++() {
            // TODO
            //node = node->next
            node = (*node).next;
            return *this;
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            // TODO
            basic_iterator prev(*this);
            node = (*node).next;
            return prev;
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
            // TODO
            node = (*node).prev;
            return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            // TODO
            basic_iterator prev(*this);
            node = (*node).prev;
            return prev;
        }

        bool operator==(const basic_iterator& other) const noexcept {
            // TODO
            if (other.node == node) {return true;}
            return false;
        }
        bool operator!=(const basic_iterator& other) const noexcept {
            // TODO
            if (other.node == node) {return false;}
            return true;
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() : head(), tail(), _size(0){
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
    }
    List( size_type count, const T& value ) : head(), tail(), _size(0){
        head.next = &tail;
        tail.prev = &head;
        // TODO - Don't forget the list initialier
        //iterator pos (&tail);
        for (int i = 0; i < count; ++i){
            Node* newNode = new Node(value, tail.prev, &tail);
            tail.prev->next = newNode;
            tail.prev = newNode;
            _size++;
        }

    }
    explicit List( size_type count ):  head(), tail(), _size(0) {
        head.next = &tail;
        tail.prev = &head;
        for (int i = 0; i < count; ++i){
            Node* newNode = new Node(T(), tail.prev, &tail);
            tail.prev->next = newNode;
            tail.prev = newNode;
            _size++;
        }
    }
    List( const List& other ) : head(), tail(), _size(0){
        head.next = &tail;
        tail.prev = &head;
        _size = other.size();
        iterator otherTraversal (other.head.next);
        for (int i = 0; i < other.size(); i++){
            Node* newNode = new Node(otherTraversal.node->data, tail.prev, &tail);
            tail.prev->next = newNode;
            tail.prev = newNode;
            ++otherTraversal;
        }
    }
    List( List&& other ) : head(), tail(), _size(other.size()){
        // TODO - Don't forget the list initialier
        head.next = &tail;
        tail.prev = &head;
        if (_size != 0){ //checks if list is empty
            head.next = other.head.next;
            tail.prev = other.tail.prev;

            head.next->prev = &head;
            tail.prev->next = &tail;


            other.head.next = &other.tail;
            other.tail.prev = &other.head;
            other._size = 0;
        }
    }
    ~List() {
        // TODO
        clear();
    }
    List& operator=( const List& other ) {
        if (this != &other){
            clear();
            head.next = &tail;
            tail.prev = &head;
            _size = other.size();
            iterator otherTraversal (other.head.next);
            for (int i = 0; i < other.size(); i++){
                Node* newNode = new Node(otherTraversal.node->data, tail.prev, &tail);
                tail.prev->next = newNode;
                tail.prev = newNode;
                ++otherTraversal;
            }
        }
        return *this;
    }
    List& operator=( List&& other ) noexcept {
        // TODO
        if (this != &other){
            clear();
            head.next = &tail;
            tail.prev = &head;
            _size = other.size();
            if (_size != 0){
                head.next = other.head.next;
                tail.prev = other.tail.prev;

                head.next->prev = &head;
                tail.prev->next = &tail;


                other.head.next = &other.tail;
                other.tail.prev = &other.head;
                other._size = 0;
            }
        }
        return *this;
    }

    reference front() {
        // TODO
        return (head.next)->data;
    }
    const_reference front() const {
        // TODO
        return (head.next)->data;
    }
	
    reference back() {
        // TODO
        return (tail.prev)->data;
    }
    const_reference back() const {
        // TODO
        return (tail.prev)->data;
    }
	
    iterator begin() noexcept {
        // TODO
        return iterator(head.next);
    }
    const_iterator begin() const noexcept {
        // TODO
        return const_iterator(head.next);
        //return bruh;
    }
    const_iterator cbegin() const noexcept {
        return const_iterator(head.next);
        //return bruh;
    }

    iterator end() noexcept {
        // TODO
        return iterator(&tail);
    }
    const_iterator end() const noexcept {
        return const_iterator(&tail);
        //return bruh;
    }
    const_iterator cend() const noexcept {
        // TODO
        return const_iterator(&tail);
        //return bruh;
    }

    bool empty() const noexcept {
        // TODO
        if (size() == 0){
            return true;
        }
        return false;
    }

    size_type size() const noexcept {
        // TODO
        return _size;
    }

    void clear() noexcept {
        // TODO
        while (size() > 0){
            pop_back();
        }
        //head.next = &tail;
        //tail.prev = &head;
    }

    iterator insert( const_iterator pos, const T& value ) {
        Node* newNode = new Node(value, pos.node->prev, pos.node);
        pos.node->prev->next = newNode;
        pos.node->prev = newNode;
        iterator temp {pos.node->prev};
        _size++;
        return temp;
    }
    iterator insert( const_iterator pos, T&& value ) {
        // TODO
        Node* newNode = new Node(std::move(value), pos.node->prev, pos.node);
        pos.node->prev->next = newNode;
        pos.node->prev = newNode;
        iterator temp {pos.node->prev};
        _size++;
        return temp;
        /*
        Node* newNode = new Node(std::move(value), pos.node->prev, pos.node);
        pos.node->prev->next = newNode;
        pos.node->prev = newNode;
        iterator temp {pos.node->prev};
        _size++;
        return temp;
        */
    }

    iterator erase( const_iterator pos ) {
        pos.node->next->prev = pos.node->prev; //next's previous arrow now points to the prev of the current node
        pos.node->prev->next = pos.node->next;
        iterator temp {pos.node->next};
        //temp--;
        delete pos.node;
        _size--;
        return temp;
        /*
        pos.node->next->prev = pos.node->prev;
        iterator retval{pos.node->prev->next = pos.node->next};
        delete pos.node;
        --_size;
        return retval;
        */

    }

    void push_back( const T& value ) { //-----------------------------------------------------------------------------------
        // TODO
        iterator pos {&tail};
        insert(pos, value);
    }
    void push_back( T&& value ) {
        // TODO
        iterator pos {&tail};
        insert(pos, std::move(value));
    }

    void pop_back() {
        iterator temp{tail.prev};
        erase(temp);
    }
	
    void push_front( const T& value ) {
        // TODO
        iterator temp{head.next};
        insert(temp, value);
    }
	void push_front( T&& value ) {
        // TODO
        // TODO
        iterator temp{head.next};
        insert(temp, std::move(value));
    }

    void pop_front() {
        // TODO
        iterator temp{head.next};
        erase(temp);
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}