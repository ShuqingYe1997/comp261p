#ifndef __PROJ0_QUEUE_HPP
#define __PROJ0_QUEUE_HPP

#include "runtimeexcept.hpp"
#include "node.hpp"

class QueueEmptyException : public RuntimeException
{
public:
    QueueEmptyException(const std::string & err) : RuntimeException(err) {}
};


template<typename Object>
class LLQueue
{
private:
    // fill in private member data here
    Node<Object>* head;
    Node<Object>* tail;
    size_t length;


public:
    LLQueue();

    // Note:  copy constructors are required.
    // Be sure to do a "deep copy" -- if I
    // make a copy and modify one, it should not affect the other.
    LLQueue(const LLQueue & st);
    LLQueue & operator=(const LLQueue & st);
    ~LLQueue();

    size_t size() const noexcept;
    bool isEmpty() const noexcept;


    // The first front() function returns the front object in such a way it can be modified.
    // Of course, you wouldn't want to do this if you have a const LLQueue, but you do
    // want to be able to do so otherwise.  The second function will be called on
    // a const LLQueue, while others get the first function.

    Object & front();
    const Object & front() const;

    void enqueue(const Object & elem);

// does not return anything.  Just removes.
    void dequeue();

// my functions
    const Node<Object>* getHead() const;
    void clear();
};

// TODO:  Fill in the functions here.
template<typename Object>
LLQueue<Object>::LLQueue() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<typename Object>
LLQueue<Object>::LLQueue(const LLQueue & st) {
    head = nullptr;
    tail = nullptr;
    length = 0;

    const Node<Object>* st_head = st.getHead();
    while (st_head) {
        if (head == nullptr) {
            head = tail = new Node<Object>(st_head->value, st_head -> next);
        }
        else {
            tail->next = new Node<Object>(st_head->value, st_head -> next);
            tail = tail->next;
        }
        st_head = st_head->next;
        length++;
    }
}

template<typename Object>
LLQueue<Object>& LLQueue<Object>::operator=(const LLQueue & st) {
    clear();

    const Node<Object>* st_head = st.getHead();
    while (st_head != nullptr) {
        if (head == nullptr) {
            head = tail = new Node<Object>(st_head->value, st_head -> next);
        }
        else {
            tail->next = new Node<Object>(st_head->value, st_head -> next);
            tail = tail -> next;
        }
        st_head = st_head->next;

        length++;
    }
    return *this;
}

template<typename Object>
LLQueue<Object>::~LLQueue()
{
    clear();
}

template<typename Object>
size_t LLQueue<Object>::size() const noexcept {
    return length;
}

template<typename Object>
bool LLQueue<Object>::isEmpty() const noexcept {
    return length == 0;
}

template<typename Object>
Object& LLQueue<Object>::front() {
    if (isEmpty())
        throw QueueEmptyException("Empty Queue!");
    return head->value;
}

template<typename Object>
const Object & LLQueue<Object>::front() const {
    if (isEmpty())
        throw QueueEmptyException("Empty Queue!");
    return head->value;
}

template<typename Object>
void LLQueue<Object>::enqueue(const Object & elem) {
    if (isEmpty()) {
        head = tail = new Node<Object>(elem);
    }
    else {
        tail->next = new Node<Object>(elem);
        tail = tail->next;
    }
    length++;
}

template<typename Object>
void LLQueue<Object>::dequeue() {
    if (isEmpty()) {
        throw QueueEmptyException("Empty Queue!");
        return;
    }
    else {
        Node<Object>* tmp = head;
        if(head == tail)
            head = tail = nullptr;
        else
            head = head->next;

        delete tmp;
        length--;
    }
}

template<typename Object>
const Node<Object>* LLQueue<Object>::getHead() const{
    return head;
}

template<typename Object>
void LLQueue<Object>::clear() {
    while(!isEmpty()) {
        dequeue();
    }
}


#endif
