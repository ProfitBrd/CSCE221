#include <cstddef>    // size_t
#include <functional> // std::hash
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"

template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap {
    public:

    using key_type = Key;
    using mapped_type = T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    private:

    struct HashNode {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type & val, HashNode * next = nullptr) : next { next }, val { val } { }
        HashNode(value_type && val, HashNode * next = nullptr) : next { next }, val { std::move(val) } { }
    };

    HashNode **_buckets;
    size_type _size;
    size_type _bucket_count;

    HashNode _head;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count) {
        return hash_code % bucket_count;
    }

    public:

    class iterator {/*TODO -- Check*/
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const key_type, mapped_type>;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        HashNode * _node;

        explicit iterator(HashNode *ptr) noexcept : _node(ptr) {}

    public:
        iterator() : _node(nullptr) {};
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        ~iterator() = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) = default;
        reference operator*() const { return this->_node->val; }
        pointer operator->() const { return &this->_node->val; }
        iterator &operator++() {
            _node = _node->next;
            return *this;
        }
        iterator operator++(int) {
            iterator prev(_node);
            _node = _node->next;
            return prev;
        }
        bool operator==(const iterator &other) const noexcept {
            return (_node == other._node);
        }
        bool operator!=(const iterator &other) const noexcept {
            return (_node != other._node);
        }
    };

    class local_iterator { /*TODO -- Check*/
        public:
            using iterator_category = std::forward_iterator_tag;
            using value_type = std::pair<const key_type, mapped_type>;
            using difference_type = ptrdiff_t;
            using pointer = value_type *;
            using reference = value_type &;

        private:
            friend class UnorderedMap<Key, T, Hash, key_equal>;
            using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

            UnorderedMap * _map;
            HashNode * _node;
            size_type _bucket;

            explicit local_iterator(UnorderedMap * map, HashNode *ptr, size_type bucket) noexcept : _map(map), _node(ptr), _bucket(bucket) {}

        public:
            local_iterator(): _node(nullptr) {};
            local_iterator(const local_iterator &) = default;
            local_iterator(local_iterator &&) = default;
            ~local_iterator() = default;
            local_iterator &operator=(const local_iterator &) = default;
            local_iterator &operator=(local_iterator &&) = default;
            reference operator*() const { return this->_node->val; }
            pointer operator->() const { return &this->_node->val; }
            local_iterator & operator++() {
                if (_node->next == nullptr){
                    _node = nullptr;
                }
                else if( _map->bucket(_node->val.first) != _map->bucket(_node->next->val.first) ){//_node->next != nullptr && _bucket != _map->bucket(_node->next->val.first) ){
                    _node = nullptr;
                }
                else{
                    _node = _node->next;
                }
                return *this;

            }
            local_iterator operator++(int) {
                local_iterator prev(_map, _node, _bucket);
                ++(*this);
                return prev;
            }
            bool operator==(const local_iterator &other) const noexcept {
                return (_node == other._node);
            }
            bool operator!=(const local_iterator &other) const noexcept {
                return (_node != other._node);
            }
    };

private:

    size_type _bucket(size_t code) const { 
        return _range_hash(code,_bucket_count);
    }
    size_type _bucket(const Key &key) const { return _bucket(_hash(key)); }

    void _insert_before(size_type bucket, HashNode *node) {
        /* TODO */
        auto postionInPointerArray = bucket; //bucket returns index of the bucket
        HashNode* &currentPointer = _buckets[postionInPointerArray]; //has to be pointer reference so we can change it effectively
        /*if (_head.next == nullptr){
            //change head next
            _head.next = node;

            //change bucket pointer from nullptr to the node we just inserted
            currentPointer = &(_head);
        }*/
        if (currentPointer == nullptr){ //if equals nullptr, bucket doesn't exist so have to insert at front -- used to be positionInPointerArray
            //find the hash value of the bucket we are about to usurp
            
            
            //insert the node at beginning of linked list
            if (_head.next){
                size_t BucketPointerChangeKey = _bucket(_head.next->val.first);
                _buckets[BucketPointerChangeKey] = node;
                node->next = _head.next;
            }
            //node->next = _head.next;
            _head.next = node;
            
            //change bucket pointer from nullptr to the node we just inserted
            currentPointer = &(_head);

            //the node we just inserted is the new head of the bucket that had the actual head as its head
            //_buckets[BucketPointerChangeKey] = node;
        }
        else{
            //insert the node after currentPointer
            node->next = currentPointer->next;
            currentPointer->next = node;
        }
        ++_size;

    }

    HashNode*& _bucket_begin(size_type bucket) {
        /* TODO */
        auto postionInPointerArray = bucket; //bucket returns index of the bucket
        HashNode* &currentPointer = _buckets[postionInPointerArray]; //has to be pointer reference so we can change it effectively
        if (currentPointer == nullptr){
            return currentPointer;
        }
        else{
            return currentPointer->next; //has to have data because size of at least 1
        }


    }

    HashNode* _find_prev(size_type code, size_type bucket, const Key & key) {
        HashNode* currentPointer = _buckets[bucket]; //has to be pointer reference so we can change it effectively
        if(currentPointer == nullptr){
            return currentPointer;
        }
        HashNode* nextPointer = currentPointer->next;
        while (nextPointer != nullptr){ 
                if( _equal (key, nextPointer->val.first) ){
                return currentPointer;
            }
            if ( _bucket(key) != bucket ){ //if going outside bucket, return null because not found *was giving error here*
                return nullptr;
            }
            currentPointer = currentPointer->next;
            nextPointer = nextPointer->next;
        }
        return nullptr;
    }

    HashNode* _find_prev(const Key & key) {
        /* TODO */
        auto keyHash = _hash(key);
        auto bucket = _bucket(keyHash);
        auto postionInPointerArray = bucket; //bucket returns index of the bucket
        return _find_prev(keyHash, bucket, key);
    }

    void _erase_after(HashNode * prev) {
        HashNode* pos = prev->next;
        auto indexOfCurrentBucket = _bucket(pos->val.first); //hash the key of the next hashnode after given node (prev)

        //deletes current node
        prev->next = prev->next->next; //prev->next has to exist, even if nullptr
        delete pos;
        _size--;

        size_type indexOfNextBucket;

        if(prev->next != nullptr){
            
            indexOfNextBucket = _bucket(prev->next->val.first); //get the key of the new "next" node in the series aka the node after the deleted one

            if (_buckets[indexOfNextBucket] == pos){ //if we just deleted the sentinel node for the bucket after, make prev the new sentinel
                _buckets[indexOfNextBucket] = prev;
            }
        }
        if(indexOfNextBucket != indexOfCurrentBucket && _buckets[indexOfCurrentBucket] == prev){ //if the bucket we deleted and the next bucket in the list are not the same, and we deleted the sentinel node if the previous if statement
            _buckets[indexOfCurrentBucket] = nullptr; //then the bucket index we of the node we just deleted has no more items
        }
        
    }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { },
                const key_equal & equal = key_equal { }) {
        /* TODO */
        _bucket_count = next_greater_prime(bucket_count);
        _hash = hash;
        _equal = equal;
        _size = 0;
        _head.next = nullptr;
        _buckets = new HashNode * [_bucket_count]();//() needed to make everything nullptr by default
    }

    ~UnorderedMap() {
        /* TODO */
        clear();
        delete[] _buckets;
    }

    UnorderedMap(const UnorderedMap & other): _head() {
        _equal = other._equal;
        _hash = other._hash;
        _bucket_count = other._bucket_count;
        _size = 0;

        _buckets = new HashNode * [_bucket_count]();
        auto iter = other._head.next; //starting at value after head

        while(iter != nullptr){ //going to end of linked list
            //copying elements over from the other list
            insert(iter->val);
            iter = iter->next;
        }
    }

    UnorderedMap(UnorderedMap && other): _head(){ 
        _hash = other._hash;
        _bucket_count = other._bucket_count;
        _size = other._size;
        _equal = other._equal;

        _head.next = other._head.next;
        _buckets = other._buckets;

        if (_head.next){
            _buckets[_bucket(other._head.next->val.first)] = &_head;
        }
        
        //make all the values of the other UnorderedMap into default
        other._size = 0;
        other._equal = key_equal();
        other._hash = Hash();
        other._buckets =  new HashNode* [other._bucket_count]();
        other._head.next = nullptr;

    }

    UnorderedMap & operator=(const UnorderedMap & other) {
        //delete all previous values of current to replace with others
        if (this == &other){ //if they are the same don't do any work
            return *this;
        }
        if (this != nullptr){ //if this object exists at all, clear it in preparation for the reassignment
            clear();
            delete _buckets;
        }
        //just do the constructor operations
        _equal = other._equal;
        _hash = other._hash;
        _bucket_count = other._bucket_count;
        _size = 0;

        _buckets = new HashNode * [_bucket_count]();
        auto iter = other._head.next; //starting at value after head

        while(iter != nullptr){ //going to end of linked list
            //copying elements over from the other list
            insert(iter->val);
            iter = iter->next;
        }
        
    }

    UnorderedMap & operator=(UnorderedMap && other) {
        /* TODO */
        if (this == &other){ //if they are the same don't do any work
            return *this;
        }
        if (this != nullptr){ //if this object exists at all, clear it in preparation for the reassignment
            clear();
            delete _buckets;
        }
        
        //just do the move constructor
        _hash = other._hash;
        _bucket_count = other._bucket_count;
        _size = other._size;
        _equal = other._equal;

        _head.next = other._head.next;
        _buckets = other._buckets;

        if (_head.next){
            _buckets[_bucket(other._head.next->val.first)] = &_head;
        }
        
        //make all the values of the other UnorderedMap into default
        other._size = 0;
        other._equal = key_equal();
        other._hash = Hash();
        other._buckets =  new HashNode* [other._bucket_count]();
        other._head.next = nullptr;

    }

    void clear() noexcept {
        /* TODO */
        while (_size != 0){ //erases linked list
            erase(begin());
        }
    }

    size_type size() const noexcept { return this->_size; }

    bool empty() const noexcept { return (this->_size == 0); }

    size_type bucket_count() const noexcept { return _bucket_count; }

    iterator begin() { return iterator(_head.next); }

    iterator end() { return iterator(nullptr); }

    local_iterator begin(size_type n) { 
        local_iterator what(this, _bucket_begin(n),n);
        return what;
    }

    local_iterator end(size_type n) { 
        local_iterator what(this, nullptr,n);
        return what;
     }

    size_type bucket_size(size_type n) { /* TODO  make a thing to traverse a linked list and count the nodes --------------------------------------------------------------------------------*/
        //same as std::distance
        local_iterator temp = begin(n); //create local iterator in the bucket and then iterate by using ++ function until its nullptr
        size_type size = 0;
        while (temp != end(n)){
            ++temp;
            ++size;
        }
        return size;
    }

    float load_factor() const { 
        return (static_cast <float>(this->_size))/(this->_bucket_count);
     }

    size_type bucket(const Key & key) const { return _bucket(key); }

    std::pair<iterator, bool> insert(value_type && value) {
        auto temp = _find_prev(value.first);
        if (temp != nullptr){ //if the key already exists (can only be one key per array)
            return std::pair<iterator,bool> (iterator{temp->next}, false);
        }
        else{
            auto keyHash = _hash(value.first);
            auto bucket = _bucket(keyHash);

            HashNode* insert = new HashNode(std::move(value));

            _insert_before(bucket, insert);
            return std::pair<iterator,bool> (iterator{insert}, true);
        }
        
    }

    std::pair<iterator, bool> insert(const value_type & value) {
        auto temp = _find_prev(value.first);
        if (temp != nullptr){ //if the key already exists (can only be one key per array)
            return std::pair<iterator,bool> (iterator{temp->next}, false);
        }
        else{
            auto keyHash = _hash(value.first);
            auto bucket = _bucket(keyHash);

            HashNode* insert = new HashNode(value);
            _insert_before(bucket, insert);
            return std::pair<iterator,bool> (iterator{insert}, true);
        }
    }

    iterator find(const Key & key) {
        /* TODO */
        auto postionInPointerArray = _bucket(bucket); //bucket returns index of the bucket
        HashNode* &currentPointer = _buckets[postionInPointerArray]; //has to be pointer reference so we can change it effectively
    }

    T& operator[](const Key & key) {
        HashNode* value = _find_prev(key);
        if (value == nullptr){
            value_type obj = std::make_pair(key, mapped_type{});
            iterator locator = insert(obj).first;
            return locator->second;
        }
        else{
            return value->next->val.second;
        }
    }

    iterator erase(iterator pos) {
        /* TODO */
        HashNode* temp = _find_prev(pos->first); //takes a key, the value has to exist in the 
        _erase_after(temp);
        return iterator(temp->next);
    }

    size_type erase(const Key & key) {
        /* TODO */
        HashNode* temp = _find_prev(key); //takes a key
        if (temp == nullptr){ //if the value does not exist return 0
            return 0;
        }
        else{ //if the value exists erase it and return 1
            _erase_after(temp);
            return 1;
        }
        
    }

    template<typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> & map, std::ostream & os);
};

template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout) {
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    HashNode const * node = map._head.next;
    os << "List: ";
    do {
        if(node) {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
        } else {
            os << "(nullptr)";
            break;
        }

        node = node->next;
    } while(true);
    os << std::endl;

    for(size_type bucket = 0; bucket < map.bucket_count(); bucket++) {
        os << bucket << ": ";

        HashNode const * node = map._buckets[bucket];

        if(!node) {
            os << "(nullptr)";
        } else {
            while((node = node->next) && map.bucket(node->val.first) == bucket) {
                os << "(" << node->val.first << ", " << node->val.second << ") ";
            }
        }
        os << std::endl;
    }
}