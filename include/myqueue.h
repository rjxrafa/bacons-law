/**
 * This is a Linked List Queue Class
 *
 * The class has been adapted from Paul Wilkinson's CS008 lectures
 *
 * @author      Ara Mico Segismundo & Rafael Betita
 * @modified    2019-06-08
 * @namespace   cs8
 */

#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "node.h"

namespace cs8 {
using namespace std;
template<typename T>
/**
 * Queue implenataion as a linked list so it can take
 * many data without having to resize
 * @brief The Queue class
 */
class Queue
{
public:
    Queue();
    ~Queue();
    Queue(const Queue<T> &other);
    Queue<T>& operator=(const Queue<T> &other);
    void enqueue(const T &data);
    T dequeue();
    T frontOfQueue() const;
    Queue<T>& operator<<(const T &data);
    Queue<T>& operator>>(T &data);
    bool empty() const;
    bool full() const;
    int size() const;
    void merge(Queue<T> &one,Queue<T> &two,Queue<T> &merged);

    template<typename S>
    friend
    ostream& operator<<(ostream &out, const Queue<S> &other);

    template<typename S>
    friend
    istream& operator>>(istream &in, Queue<S> &other);

private:
    Q::node<T> *front, *back;
    size_t mySize;

    void copy(const Queue<T> &other);
    void deleteAll();
};

template<typename T>
/**
 * Constructor of queue
 * @brief Queue<T>::Queue
 */
Queue<T>::Queue()
{
    mySize = 0;
    front = back = nullptr;
}

template<typename T>
/**
 * Queue destructor uses deleteAll
 * @brief Queue<T>::~Queue
 */
Queue<T>::~Queue()
{
    deleteAll();
}

template<typename T>
Queue<T>::Queue(const Queue<T> &other)
{
    copy(other);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<typename T>
/**
 * Enqeues data into the queue
 * if empty both are the data if not back keeps moving
 * @brief Queue<T>::enqueue
 * @param data
 */
void Queue<T>::enqueue(const T &data)
{
    if(full())
    {
        cout<<"Queue is full"<<endl;
    }
    Q::node<T> *newNode = new Q::node<T>(data);
    if(empty())
    {
        front = back = newNode;
    }
    else
    {
        back->next = newNode;
        back = back->next;
    }
    ++mySize;
}

template<typename T>
/**
 * Merges one and two into a new queue
 * data in one and two are deleted
 * @brief Queue<T>::merge
 */
void Queue<T>::merge(Queue<T> &one, Queue<T> &two, Queue<T> &merged)
{
    while(!two.empty() || !one.empty())
        if((!two.empty()) && (two.frontOfQueue() <= one.frontOfQueue()))
        {
            if(!two.empty())
            {
                merged.enqueue(two.frontOfQueue());
                two.dequeue();
            }
        }
        else
        {
            if(!one.empty())
            {
                merged.enqueue(one.frontOfQueue());
                one.dequeue();
            }
        }
}

template<typename T>
/**
 * Removes data in queue and returns what it was
 * @brief Queue<T>::dequeue
 */
T Queue<T>::dequeue()
{
    if(empty())
    {
        cout<<"Empty Queue"<<endl;
    }
    T data = front->data;
    Q::node<T> *toBeDeleted = front;
    front = front->next;
    delete toBeDeleted;
    --mySize;
    return data;
}

template<typename T>
/**
 * @brief Queue<T>::frontOfQueue
 * @return data in front of queue
 */
T Queue<T>::frontOfQueue() const
{
    if(empty())
    {
        cout<<"Empty Queue"<<endl;
        return T();
    }
    return front->data;
}

template<typename T>
Queue<T>& Queue<T>::operator<<(const T &data)
{
    enqueue(data);
    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator>>(T &data)
{
    data = dequeue();
    return *this;
}

template<typename T>
bool Queue<T>::empty() const
{
    return !mySize;
}

template<typename T>
//Queue full returns false because it will never be full
bool Queue<T>::full() const
{
    //queue will never be full
    return false;
}

template<typename T>
void Queue<T>::copy(const Queue<T> &other)
{
    mySize = other.mySize;
    if(!other.empty())
    {
        deleteAll();
        front = new Q::node<T>(*other.front);
        back = front;
        for(Q::node<T> *tempPtr = other.front->next; tempPtr != nullptr; tempPtr = tempPtr->next)
        {
            back->next = new Q::node<T>(*tempPtr);
            back = back->next;
        }
    }
}

template<typename T>
void Queue<T>::deleteAll()
{
    for(Q::node<T> *toBeDeleted;
        front != nullptr; toBeDeleted = front,
        front = front->next,
        delete toBeDeleted);
    front = back = nullptr;
    mySize = 0;
}

template<typename T>
int Queue<T>::size() const
{
    return mySize;
}

template<typename S>
ostream& operator<<(ostream &out, const Queue<S> &other)
{
    if(&out != &cout)
    {
        out<<"Size: "<<other.size()<<endl;
    }
    for(Q::node<S> *toBePrinted = other.front; toBePrinted != nullptr; toBePrinted = toBePrinted->next)
    {
        out<<*toBePrinted<<" ";
    }
    return out;
}

template<typename S>
istream& operator>>(istream &in, Queue<S> &other)
{
    Queue<S> temp;
    S data;
    while(in>>data)
        other<<data;
    other = temp;
    return in;
}
} // namespace

#endif // MYQUEUE_H
