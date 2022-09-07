#include <cstddef>    // size_t
#include <functional> // std::hash
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"

/* 
----------------------------------------------------------------------------------
NT !!!! IMPORTANT !!!! IMPORTANT !!!! IMPORTANT !!!! IMPORTANT !!!! IMPORTANT ! IM
----------------------------------------------------------------------------------
If you choose to write your code using this file, in order to be able to compile
you will need to rename this file to "UnorderedMap.h" and remove or rename the other 
version of this file.
----------------------------------------------------------------------------------
*/


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

    HashNode* _head;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count) {
        return hash_code % bucket_count;
    }

    public:

    class iterator {
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

        explicit iterator(UnorderedMap * map, HashNode *ptr, size_type bucket) noexcept { /* TODO */ }

    public:
        iterator() { /* TODO */ };
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        ~iterator() = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) = default;
        reference operator*() const { /* TODO */ }
        pointer operator->() const { /* TODO */ }
        iterator &operator++() {
            /* TODO */
        }
        iterator operator++(int) {
            /* TODO */
        }
        bool operator==(const iterator &other) const noexcept {
            /* TODO */
        }
        bool operator!=(const iterator &other) const noexcept {
            /* TODO */
        }
    };

    class local_iterator {
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

            explicit local_iterator(UnorderedMap * map, HashNode *ptr, size_type bucket) noexcept { /* TODO */ }

        public:
            local_iterator() { /* TODO */ };
            local_iterator(const local_iterator &) = default;
            local_iterator(local_iterator &&) = default;
            ~local_iterator() = default;
            local_iterator &operator=(const local_iterator &) = default;
            local_iterator &operator=(local_iterator &&) = default;
            reference operator*() const { /* TODO */ }
            pointer operator->() const { /* TODO */ }
            local_iterator & operator++() {
                // TODO
            }
            local_iterator operator++(int) {
                // TODO
            }
            bool operator==(const local_iterator &other) const noexcept {
                // TODO
            }
            bool operator!=(const local_iterator &other) const noexcept {
                // TODO
            }
    };

private:

    size_type _bucket(size_t code) const { /* TODO */ }
    size_type _bucket(const Key &key) const { /* TODO */ }

    HashNode*& _bucket_begin(size_type bucket) {
        /* TODO */
    }

    // This helper function is intended for insert. It is meant to find the
    // HashNode* of the node containing the key value. If it does not exist in
    // the map, it returns nullptr.
    HashNode* _find_helper(size_type code, size_type bucket, const Key & key) {
        /* TODO */
    }

    // This helper function is for erase. It is meant to find the
    // HashNode* of the node immediately before the one containing the key value. If 
    // it does not exist in the map, it returns nullptr.
    HashNode* _find_prev(size_type code, size_type bucket, const Key & key) {
        /* TODO */
    }

    // This helper function is for erase. Does the same thing as the other 
    // _find_prev.
    HashNode* _find_prev(const Key & key) {
        /* TODO */
    }

    void _move_content(UnorderedMap & src, UnorderedMap & dst){
        /* TODO */
    }

    // This helper function returns the HashNode* of the next node in the
    // map. It is intended to be used in the global iterator increment 
    // operators and erase.
    HashNode* _find_next_global_node(HashNode* node, size_type& bucket) {
        /* TODO */
    }

public:
    explicit UnorderedMap(size_type bucket_count, const Hash & hash = Hash { },
                const key_equal & equal = key_equal { }) {
        /* TODO */
    }

    ~UnorderedMap() {
        /* TODO */
    }

    UnorderedMap(const UnorderedMap & other) {
        /* TODO */
    }

    UnorderedMap(UnorderedMap && other) {
        /* TODO */
    }

    UnorderedMap & operator=(const UnorderedMap & other) {
        /* TODO */
    }

    UnorderedMap & operator=(UnorderedMap && other) {
        /* TODO */
    }

    void clear() noexcept {
        /* TODO */
    }

    size_type size() const noexcept { /* TODO */ }

    bool empty() const noexcept { /* TODO */ }

    size_type bucket_count() const noexcept { /* TODO */ }

    iterator begin() { /* TODO */ }

    iterator end() { /* TODO */ }

    local_iterator begin(size_type n) { /* TODO */ }

    local_iterator end(size_type n) { /* TODO */ }

    size_type bucket_size(size_type n) { /* TODO */ }

    float load_factor() const { /* TODO */ }

    size_type bucket(const Key & key) const { /* TODO */ }

    std::pair<iterator, bool> insert(value_type && value) {
        /* TODO */
    }

    std::pair<iterator, bool> insert(const value_type & value) {
        /* TODO */
    }

    iterator find(const Key & key) {
        /* TODO */
    }

    T& operator[](const Key & key) {
        /* TODO */
    }

    iterator erase(iterator pos) {
        /* TODO */
    }

    size_type erase(const Key & key) {
        /* TODO */
    }

    template<typename KK, typename VV>
    friend void print_map(const UnorderedMap<KK, VV> & map, std::ostream & os);
};

template<typename K, typename V>
void print_map(const UnorderedMap<K, V> & map, std::ostream & os = std::cout) {
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    HashNode const * node = map._head->next;
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
