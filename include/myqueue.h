#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "node.h"

using namespace std;

template<typename T>
class myQueue
{
public:
    myQueue();
    ~myQueue();
    myQueue(const myQueue<T> &other);
    myQueue<T>& operator=(const myQueue<T> &other);
    void enqueue(const T &data);
    T dequeue();
    T frontOfQueue() const;
    myQueue<T>& operator<<(const T &data);
    myQueue<T>& operator>>(T &data);
//    void resize(size_t newSize);
    bool empty() const;
    bool full() const;
//    int capacity() const;
    int size() const;
    void merge(myQueue<T> &one,myQueue<T> &two,myQueue<T> &merged);

    template<typename S>
    friend
    ostream& operator<<(ostream &out, const myQueue<S> &other);

    template<typename S>
    friend
    istream& operator>>(istream &in, myQueue<S> &other);

private:
    node<T> *front, *back;
    size_t mySize;

    void copy(const myQueue<T> &other);
    void deleteAll();
};

template<typename T>
myQueue<T>::myQueue()
{
    mySize = 0;
    front = back = nullptr;
}

template<typename T>
myQueue<T>::~myQueue()
{
    deleteAll();
}

template<typename T>
myQueue<T>::myQueue(const myQueue<T> &other)
{
    copy(other);
}

template<typename T>
myQueue<T>& myQueue<T>::operator=(const myQueue<T> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template<typename T>
void myQueue<T>::enqueue(const T &data)
{
    if(full())
    {
        cout<<"Queue is full"<<endl;
    }
    node<T> *newNode = new node<T>(data);
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
void myQueue<T>::merge(myQueue<T> &one, myQueue<T> &two, myQueue<T> &merged)
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
T myQueue<T>::dequeue()
{
    if(empty())
    {
        cout<<"Empty Queue"<<endl;
    }
    T data = front->data;
    node<T> *toBeDeleted = front;
    front = front->next;
    delete toBeDeleted;
    --mySize;
    return data;
}

template<typename T>
T myQueue<T>::frontOfQueue() const
{
    if(empty())
    {
        cout<<"Empty Queue"<<endl;
        return T();
    }
    return front->data;
}

template<typename T>
myQueue<T>& myQueue<T>::operator<<(const T &data)
{
    enqueue(data);
    return *this;
}

template<typename T>
myQueue<T>& myQueue<T>::operator>>(T &data)
{
    data = dequeue();
    return *this;
}

//template<typename T>
//void myQueue<T>::resize(size_t newSize)
//{
//    node<T> *toBeRemoved;
//        if(newSize < 2)
//        {
//            cout<<"Bad Size"<<endl;
//            return;
//        }
//        myCapacity = newSize;
//        if(!empty())
//            while(mySize > myCapacity)
//            {
//                toBeRemoved = front;
//                front = front->next;
//                delete toBeRemoved;
//                --mySize;
//            }
//}

template<typename T>
bool myQueue<T>::empty() const
{
    return !mySize;
}

template<typename T>
bool myQueue<T>::full() const
{
    //queue will never be full
    return false;
}

template<typename T>
void myQueue<T>::copy(const myQueue<T> &other)
{
    mySize = other.mySize;
    if(!other.empty())
    {
        deleteAll();
        front = new node<T>(*other.front);
        back = front;
        for(node<T> *tempPtr = other.front->next; tempPtr != nullptr; tempPtr = tempPtr->next)
        {
            back->next = new node<T>(*tempPtr);
            back = back->next;
        }
    }
}

template<typename T>
void myQueue<T>::deleteAll()
{
    for(node<T> *toBeDeleted;
        front != nullptr; toBeDeleted = front,
        front = front->next,
        delete toBeDeleted);
    front = back = nullptr;
    mySize = 0;
}

//template<typename T>
//int myQueue<T>::capacity() const
//{
//    return myCapacity;
//}
template<typename T>
int myQueue<T>::size() const
{
    return mySize;
}

template<typename S>
ostream& operator<<(ostream &out, const myQueue<S> &other)
{
    if(&out != &cout)
    {
        out<<"Size: "<<other.size()<<endl;
    }
    for(node<S> *toBePrinted = other.front; toBePrinted != nullptr; toBePrinted = toBePrinted->next)
    {
        out<<*toBePrinted<<" ";
    }
    return out;
}

template<typename S>
istream& operator>>(istream &in, myQueue<S> &other)
{
    if(&in != &cin)
    {
        int size;
        string line;
        getline(in, line);
        stringstream ss;
        ss<<line.substr(line.find(':')+1);
//        ss>>size;
        myQueue<S> temp;
        S data;
        while(in>>data)
            other<<data;
        other = temp;
    }
    return in;
}

#endif // MYQUEUE_H
