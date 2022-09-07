#pragma once

#include <functional> // std::less
#include <iostream>
#include <queue>   // std::queue
#include <utility> // std::pair

template <typename K, typename V, typename Comparator = std::less<K>>
class BinarySearchTree
{
public:
    using key_type = K;
    using value_type = V;
    using key_compare = Comparator;
    using pair = std::pair<key_type, value_type>;
    using pointer = pair *;
    using const_pointer = const pair *;
    using reference = pair &;
    using const_reference = const pair &;
    using difference_type = ptrdiff_t;
    using size_type = size_t;

private:
    struct BinaryNode
    {
        pair element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const_reference theElement, BinaryNode *lt, BinaryNode *rt)
            : element{theElement}, left{lt}, right{rt} {}

        BinaryNode(pair &&theElement, BinaryNode *lt, BinaryNode *rt)
            : element{std::move(theElement)}, left{lt}, right{rt} {}
    };

    using node = BinaryNode;
    using node_ptr = node *;
    using const_node_ptr = const node *;

    node_ptr _root;
    size_type _size;
    key_compare comp;

public:
    BinarySearchTree() : _root(nullptr), _size(0) {}
    BinarySearchTree(const BinarySearchTree &rhs) : _root(nullptr)
    {
        // TODO
        // just using clone function
        _root = clone(rhs._root);
        _size = rhs._size;
    }
    BinarySearchTree(BinarySearchTree &&rhs) : _root(nullptr)
    {
        // TODO
        if (rhs._root == nullptr)
        {
            _root = nullptr;
            _size = 0;
        }
        else
        {
            _root = rhs._root;
            _size = rhs._size;
            rhs._root = nullptr;
            rhs._size = 0;
        }
    }
    ~BinarySearchTree()
    {
        // TODO
        clear();
    }

    const_reference min() const { return min(_root)->element; }
    const_reference max() const { return max(_root)->element; }
    const_reference root() const
    {
        return _root->element;
    }
    bool contains(const key_type &x) const { return contains(x, _root); }
    value_type &find(const key_type &key) { return find(key, _root)->element.second; }
    const value_type &find(const key_type &key) const { return find(key, _root)->element.second; }
    bool empty() const
    {
        // TODO
        if (_size == 0)
        {
            return true;
        }
        return false;
    }
    size_type size() const
    {
        // TODO
        return _size;
    }

    void clear()
    {
        clear(_root);
        _size = 0;
    }
    void insert(const_reference x) { insert(x, _root); }
    void insert(pair &&x) { insert(std::move(x), _root); }
    void erase(const key_type &x) { erase(x, _root); }

    BinarySearchTree &operator=(const BinarySearchTree &rhs)
    {
        if (this != &rhs)
        {
            clear();
            _root = clone(rhs._root);
            _size = rhs._size;
        }
        return *this;
    }
    BinarySearchTree &operator=(BinarySearchTree &&rhs)
    {
        if (this != &rhs)
        {
            clear();

            _root = rhs._root;
            _size = rhs._size;
            rhs._root = nullptr;
            rhs._size = 0;
        }
        return *this;
    }

private:
    void insert(const_reference x, node_ptr &t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{x, nullptr, nullptr};
            _size++;
        }
        else if (comp(x.first, t->element.first))
            insert(x, t->left);
        else if (comp(t->element.first, x.first))
            insert(x, t->right);
        else
            t->element.second = x.second; // Replace the second value if the first element (key) is equal
    }
    void insert(pair &&x, node_ptr &t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
            _size++;
        }
        else if (comp(x.first, t->element.first))
            insert(std::move(x), t->left);
        else if (comp(t->element.first, x.first))
            insert(std::move(x), t->right);
        else
            t->element.second = std::move(x.second); // Replace the second value if the first element (key) is equal
    }

    void erase(const key_type &x, node_ptr &t)
    {
        // TODO -- Bonus
        if (t == nullptr)
            return; // Item not found; do nothing
        if (comp(x, t->element.first)) //if the element is less than the key value we are on go left
            erase(x, t->left);
        else if (comp(t->element.first, x)) //if element is greater than key value we are on go right
            erase(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) //if it has two chilren, find minimum value from right side and replace current node with the node, then delete the node you used to replace
        {
            t->element = min(t->right)->element;
            erase(t->element.first, t->right);
        }
        else //set new value to node we want to delete, t either equals its left node if its not nullptr, otherwise right node. Delete old node and decrease size. Base case when parent only has one child
        {
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
            oldNode = nullptr;
            _size--;
        }
    }

    const_node_ptr min(const_node_ptr t) const
    {
        // done recursively
        if (t == nullptr)
        {
            return nullptr;
        }
        if (t->left == nullptr)
        {
            return t;
        }
        return min(t->left);
    }
    const_node_ptr max(const_node_ptr t) const
    {
        // done nonrecursively
        if (t != nullptr)
            while (t->right != nullptr)
            {
                t = t->right;
            }
        return t;
    }

    bool contains(const key_type &x, const_node_ptr t) const
    {
        if (t == nullptr)
            return false;
        else if (comp(x, t->element.first))
            return contains(x, t->left);
        else if (comp(t->element.first, x))
            return contains(x, t->right);
        else
            return true; // Match
    }
    node_ptr find(const key_type &key, node_ptr t)
    {
        if (t == nullptr)
            return nullptr;
        else if (comp(key, t->element.first))
            return find(key, t->left);
        else if (comp(t->element.first, key))
            return find(key, t->right);
        else
            return t; // Match
    }
    const_node_ptr find(const key_type &key, const_node_ptr t) const
    {
        if (t == nullptr)
            return nullptr;
        else if (comp(key, t->element.first))
            return find(key, t->left);
        else if (comp(t->element.first, key))
            return find(key, t->right);
        else
            return t; // Match
    }

    void clear(node_ptr &t)
    {
        if (t != nullptr)
        {
            clear(t->left);
            clear(t->right);
            delete t;
        }
        t = nullptr;
    }

    node_ptr clone(const_node_ptr t) const
    { // preorder, build trees from top down
        if (t == nullptr)
        {
            return nullptr;
        }
        else
        {
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
        }
    }

public:
    template <typename KK, typename VV, typename CC>
    friend void printLevelByLevel(const BinarySearchTree<KK, VV, CC> &bst, std::ostream &out);

    template <typename KK, typename VV, typename CC>
    friend std::ostream &printNode(std::ostream &o, const typename BinarySearchTree<KK, VV, CC>::node &bn);

    template <typename KK, typename VV, typename CC>
    friend void printTree(const BinarySearchTree<KK, VV, CC> &bst, std::ostream &out);

    template <typename KK, typename VV, typename CC>
    friend void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream &out, unsigned depth);

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr node,
        std::ostream &out,
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev);

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        const BinarySearchTree<KK, VV, CC> &bst,
        std::ostream &out);
};

template <typename KK, typename VV, typename CC>
std::ostream &printNode(std::ostream &o, const typename BinarySearchTree<KK, VV, CC>::node &bn)
{
    return o << '(' << bn.element.first << ", " << bn.element.second << ')';
}

template <typename KK, typename VV, typename CC>
void printLevelByLevel(const BinarySearchTree<KK, VV, CC> &bst, std::ostream &out = std::cout)
{
    using node = typename BinarySearchTree<KK, VV, CC>::node;
    using node_ptr = typename BinarySearchTree<KK, VV, CC>::node_ptr;
    using const_node_ptr = typename BinarySearchTree<KK, VV, CC>::const_node_ptr;

    // TODO -- Guide in Instructions
    std::queue<node_ptr> searchQueue;
    int depth = 0;
    int count = 0;
    bool nonNullChild = false;
    
    if (bst._root == nullptr){
        return;
    }
    searchQueue.push(bst._root); //push the root to start off

    while (!searchQueue.empty())
    {
        node_ptr temp = searchQueue.front(); //temp is pointing at first item every iteration
        searchQueue.pop(); //pop the item we are looking at
        if (temp == nullptr) //if value is nullptr push two more nullptr nodes and print out null
        {
            searchQueue.push(nullptr);
            searchQueue.push(nullptr);
            out << "null "; //------------------------------------------------------------------------------
        }
        else //else push left and right values (it's ok if they are nullptrs), checking if the whole row is nullptr with bool value
        {
            searchQueue.push(temp->left);
            searchQueue.push(temp->right);
            if (temp->right != nullptr || temp->left != nullptr)
            {
                nonNullChild = true;
            }
            printNode<KK, VV, CC>(out, *temp);
            // printNode<KK, VV, CC>(*temp->right); //dereference
            // printNode<KK, VV, CC>(*temp->left);
        }
        ++count;

        if (count == (1 << depth))
        {
            count = 0;
            if (!nonNullChild)
            {
                break;
            }
            nonNullChild = false;
            ++depth;
        }
        

        // check if at last node of level

        // if point to nullptr, push nullptr to queue twice
    }
}

template <typename KK, typename VV, typename CC>
void printTree(const BinarySearchTree<KK, VV, CC> &bst, std::ostream &out = std::cout) { printTree<KK, VV, CC>(bst._root, out); }

template <typename KK, typename VV, typename CC>
void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream &out, unsigned depth = 0)
{
    if (t != nullptr)
    {
        printTree<KK, VV, CC>(t->right, out, depth + 1);
        for (unsigned i = 0; i < depth; ++i)
            out << '\t';
        printNode<KK, VV, CC>(out, *t) << '\n';
        printTree<KK, VV, CC>(t->left, out, depth + 1);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr node,
    std::ostream &out,
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev = nullptr)
{
    if (node)
    {
        std::hash<KK> khash{};

        out << "\t"
               "node_"
            << (uint32_t)khash(node->element.first)
            << "[label=\"" << node->element.first
            << " [" << node->element.second << "]\"];" << std::endl;

        if (prev)
            out << "\tnode_" << (uint32_t)khash(prev->element.first) << " -> ";
        else
            out << "\t";

        out << "node_" << (uint32_t)khash(node->element.first) << ";" << std::endl;

        vizTree<KK, VV, CC>(node->left, out, node);
        vizTree<KK, VV, CC>(node->right, out, node);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    const BinarySearchTree<KK, VV, CC> &bst,
    std::ostream &out = std::cout)
{
    out << "digraph Tree {" << std::endl;
    vizTree<KK, VV, CC>(bst._root, out);
    out << "}" << std::endl;
}
