#ifndef __PROJECT_TWO_RBTREE_HPP
#define __PROJECT_TWO_RBTREE_HPP

#include "runtimeexcept.hpp"
#include <string>
#include <vector>

class ElementNotFoundException : public RuntimeException
{
public:
    ElementNotFoundException(const std::string & err) : RuntimeException(err) {}
};

enum Color { RED, BLACK };

template<typename Key, typename Value>
class Node {
private:
    Key key;
    Value value;
    Color color;
    Node<Key, Value> *left, *right, *parent;

public:
    Node<Key, Value>() {
        color = RED;
        left = right = parent = nullptr;
    }
    Node<Key, Value>(const Key & k, const Value & v) {
        key  = k;
        value = v;
        color = RED;
        left = right = parent = nullptr;
    }

    Key getKey() {
        return key;
    }
    void setKey(const Key & k) {
        key = k;
    }
    Value& getValue() {
        return value;
    }
    void setValue(const Value & v) {
        value = v;
    }
    Color getColor() {
        return color;
    }
    void setColor(Color c) {
        color = c;
    }
    Node<Key, Value> * getLeft() {
        return left;
    }
    void setLeft(Node<Key, Value> * l) {
        left = l;
    }
    Node<Key, Value> * getRight() {
        return right;
    }
    void setRight(Node<Key, Value> * r) {
        right = r;
    }
    Node<Key, Value> * getParent() {
        return parent;
    }
    void setParent(Node<Key, Value> * p) {
        parent = p;
    }
};

template<typename Key, typename Value>
class MyRBTree
{
private:
    // fill in private member data here
    // If you need to declare private functions, do so here too.
    size_t _size;
    Node<Key, Value> *root;
    Node<Key, Value>* findNode(Node<Key, Value>* node, const Key & k) const;
    void rotateLeft(Node<Key, Value> *);
    void rotateRight(Node<Key, Value> *);
    Color getColor(Node<Key, Value> *);
    void setColor(Node<Key, Value> *&, Color);
    void recolor(Node<Key, Value> *);
    void swapColor(Node<Key, Value> * node1, Node<Key, Value> * node2);
    Node<Key, Value>* insertRBT(Node<Key, Value> *, Node<Key, Value> *);
    void inOrderRBT(Node<Key, Value> *, std::vector<Key>&) const;
    void preOrderRBT(Node<Key, Value> *, std::vector<Key>&) const;
    void postOrderRBT(Node<Key, Value> *, std::vector<Key>&) const;
    void searchInRangeRBT(Node<Key, Value> *, const Key & k1, const Key & k2, std::vector<Key>&) const;
    void deleteRBT(Node<Key, Value> *);


public:
    MyRBTree();

    // In general, a copy constructor and assignment operator
    // are good things to have.
    // For this quarter, I am not requiring these.


    // The destructor is, however, required.
    ~MyRBTree()
    {
        deleteRBT(root);
    }

    // size() returns the number of distinct keys in the tree.
    size_t size() const noexcept;

    // isEmpty() returns true if and only if the tree has no values in it.
    bool isEmpty() const noexcept;

    // contains() returns true if and only if there
    //  is a (key, value) pair in the tree
    //	that has the given key as its key.
    bool contains(const Key & k) const;

    // find returns the value associated with the given key
    // If !contains(k), this will throw an ElementNotFoundException
    // There needs to be a version for const and non-const trees.
    Value & find(const Key & k);
    const Value & find(const Key & k) const;

    // Inserts the given key-value pair into
    // the tree and performs the Red-Black re-balance
    // operation, as described in lecture.
    // If the key already exists in the tree,
    // you may do as you please (no test cases in
    // the grading script will deal with this situation)
    void insert(const Key & k, const Value & v);

    // returns all keys in the tree that are between k1 and k2, inclusive.
    // You must return these *in order*.
    // Your running time should be O(log n + s), where s is the number of elements returned.
    std::vector<Key> reportAllInRange(const Key & k1, const Key & k2) const;


    // in general, a "remove" function would be here.
    // You would need it for line segment intersection,
    // but in Spring 2021, we aren't requiring it.

    // The following three functions all return
    // the set of keys in the tree as a standard vector.
    // Each returns them in a different order.
    std::vector<Key> inOrder() const;
    std::vector<Key> preOrder() const;
    std::vector<Key> postOrder() const;
};


// Many functions below are stubbed;  you should fix them.

template<typename Key, typename Value>
MyRBTree<Key,Value>::MyRBTree()
{
    _size = 0;
    root = nullptr;
}

template<typename Key, typename Value>
size_t MyRBTree<Key, Value>::size() const noexcept
{
    return _size;
}

template<typename Key, typename Value>
bool MyRBTree<Key, Value>::isEmpty() const noexcept
{
    return size() == 0;
}

template<typename Key, typename Value>
bool MyRBTree<Key, Value>::contains(const Key &k) const
{
    Node<Key, Value>* node = findNode(root, k);
    return node != nullptr;
}

// needs to throw an ElementNotFoundException if it isn't there.
template<typename Key, typename Value>
Value & MyRBTree<Key, Value>::find(const Key & k)
{
    // NOTE:  do not catch this within this function!
    //		If you need to throw, throw it.
    Node<Key, Value>* node = findNode(root, k);
    if (node == nullptr)
        throw ElementNotFoundException("Key not found!");
    else {
        return node->getValue();
    }
}

template<typename Key, typename Value>
const Value & MyRBTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value>* node = findNode(root, k);
    if (node == nullptr)
        throw ElementNotFoundException("Key not found!");
    else
        return node->getValue();
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::insert(const Key & k, const Value & v)
{
    if (contains(k))
        return;

    Node<Key, Value> *node = new Node<Key, Value>(k, v);
    root = insertRBT(root, node);
    recolor(node);
    _size++;
}


template<typename Key, typename Value>
std::vector<Key> MyRBTree<Key, Value>::reportAllInRange(const Key & k1, const Key & k2) const
{
    std::vector<Key> res;
    searchInRangeRBT(root, k1, k2, res);
    return res;
}

template<typename Key, typename Value>
std::vector<Key> MyRBTree<Key, Value>::inOrder() const
{
    std::vector<Key> res;
    inOrderRBT(root, res);

    return res;
}


template<typename Key, typename Value>
std::vector<Key> MyRBTree<Key, Value>::preOrder() const
{
    std::vector<Key> res;
    preOrderRBT(root, res);

    return res;
}


template<typename Key, typename Value>
std::vector<Key> MyRBTree<Key, Value>::postOrder() const
{
    std::vector<Key> res;
    postOrderRBT(root, res);

    return res;
}


/////////////////////////////////////////////////////////////////////
/////////////         private functions               ///////////////
/////////////////////////////////////////////////////////////////////

template<typename Key, typename Value>
Node<Key, Value>* MyRBTree<Key, Value>::findNode(Node<Key, Value>* node, const Key & k) const{
    if (node == nullptr)
        return nullptr;
    if (k > node->getKey()) {
        return findNode(node->getRight(), k);
    }
    else if (k < node->getKey()) {
        return findNode(node->getLeft(), k);
    }
    else
        return node;
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::rotateLeft(Node<Key, Value> * node) {
    Node<Key, Value> *right_child = node->getRight();
    node->setRight(right_child->getLeft());

    if (node->getRight() != nullptr)
        node->getRight()->setParent(node);

    right_child->setParent(node->getParent());

    if (node->getParent() == nullptr)
        root = right_child;
    else if (node == node->getParent()->getLeft())
        node->getParent()->setLeft(right_child);
    else
        node->getParent()->setRight(right_child);

    right_child->setLeft(node);
    node->setParent(right_child);
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::rotateRight(Node<Key, Value> * node) {
    Node<Key, Value> *left_child = node->getLeft();
    node->setLeft(left_child->getRight());

    if (node->getLeft() != nullptr)
        node->getLeft()->setParent(node);

    left_child->setParent(node->getParent());

    if (node->getParent() == nullptr)
        root = left_child;
    else if (node == node->getParent()->getLeft())
        node->getParent()->setLeft(left_child);
    else
        node->getParent()->setRight(left_child);

    left_child->setRight(node);
    node->setParent(left_child);
}

template<typename Key, typename Value>
Color MyRBTree<Key, Value>::getColor(Node<Key, Value> * node) {
    if (node == nullptr)
        return BLACK;

    return node->getColor();
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::setColor(Node<Key, Value> *& node, Color color) {
    if (node == nullptr)
        return;

    node->setColor(color);
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::recolor(Node<Key, Value> * node) {
    Node<Key, Value> *parent = nullptr;
    Node<Key, Value> *grandparent = nullptr;
    while (node != root && node->getColor() == RED && node->getParent()->getColor() == RED) {
        parent = node->getParent();
        grandparent = parent->getParent();
        if (parent == grandparent->getLeft()) {
            Node<Key, Value> *uncle = grandparent->getRight();
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            } else {
                if (node == parent->getRight()) {
                    rotateLeft(parent);
                    node = parent;
                    parent = node->getParent();
                }
                rotateRight(grandparent);
                swapColor(parent, grandparent);
                node = parent;
            }
        } else {
            Node<Key, Value> *uncle = grandparent->getLeft();
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                node = grandparent;
            } else {
                if (node == parent->getLeft()) {
                    rotateRight(parent);
                    node = parent;
                    parent = node->getParent();
                }
                rotateLeft(grandparent);
                swapColor(parent, grandparent);
                node = parent;
            }
        }
    }
    root->setColor(BLACK);
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::swapColor(Node<Key, Value> * node1, Node<Key, Value> * node2) {
    Color tmp = node1->getColor();
    node1->setColor(node2->getColor());
    node2->setColor(tmp);
}

template<typename Key, typename Value>
Node<Key, Value>* MyRBTree<Key, Value>::insertRBT(Node<Key, Value> *sub_root, Node<Key, Value> * node) {
    if (sub_root == nullptr)
        return node;

    if (node->getKey() < sub_root->getKey()) {
        sub_root->setLeft(insertRBT(sub_root->getLeft(), node));
        sub_root->getLeft()->setParent(sub_root);
    } else if (node->getKey() > sub_root->getKey()) {
        sub_root->setRight(insertRBT(sub_root->getRight(), node));
        sub_root->getRight()->setParent(sub_root);
    }
    return sub_root;
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::inOrderRBT(Node<Key, Value> * node, std::vector<Key>& res) const {
    if (node == nullptr)
        return;
    inOrderRBT(node->getLeft(), res);
    res.push_back(node->getKey());
    inOrderRBT(node->getRight(), res);
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::preOrderRBT(Node<Key, Value> * node, std::vector<Key>& res) const {
    if (node == nullptr)
        return;
    res.push_back(node->getKey());
    preOrderRBT(node->getLeft(), res);
    preOrderRBT(node->getRight(), res);
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::postOrderRBT(Node<Key, Value> * node, std::vector<Key>& res) const {
    if (node == nullptr)
        return;

    postOrderRBT(node->getLeft(), res);
    postOrderRBT(node->getRight(), res);
    res.push_back(node->getKey());
}

template<typename Key, typename Value>
void MyRBTree<Key, Value>::searchInRangeRBT(Node<Key, Value> * node, const Key & k1, const Key & k2, std::vector<Key>& res) const {
    if (node == nullptr)
        return;
    if (k1 < node->getKey())
        searchInRangeRBT(node->getLeft(), k1, k2, res);

    if (k1 <= node->getKey() && k2 >= node->getKey())
        res.push_back(node->getKey());

    if (k2 > node->getKey())
        searchInRangeRBT(node->getRight(), k1, k2, res);
}


template<typename Key, typename Value>
void MyRBTree<Key, Value>::deleteRBT(Node<Key, Value> * node) {
    if (node == nullptr)
        return;

    deleteRBT(node->getLeft());
    deleteRBT(node->getRight());
    delete node;
}



#endif