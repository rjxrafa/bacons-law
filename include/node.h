#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

template <typename Data>
struct node
{
    node(Data d = Data());
    ~node();
    node(const node<Data> &other);
    node<Data>& operator=(const node<Data> &other);

    Data data;
    node<Data> *next;

    template<typename D>
    friend
    ostream& operator<<(ostream &out, const node<D> &theNode);

    template<typename D>
    friend
    istream& operator>>(istream &in, node<D> &theNode);

private:
    void copy(const node<Data> &other);
};

template<typename Data>
node<Data>::node(Data d)
{
    data = d;
    next = nullptr;
}

template<typename Data>
node<Data>::~node()
{
    data = Data();
    next = nullptr;
}

template<typename Data>
node<Data>::node(const node<Data> &other)
{
    copy(other);
}

template<typename Data>
node<Data>& node<Data>::operator=(const node<Data> &other)
{
    if(this != &other)
        copy(other);
    return *this;
}

template <typename Data>
void node<Data>::copy(const node<Data> &other)
{
    data = other.data;
    next = nullptr;
}

template<typename D>
ostream& operator<<(ostream &out, const node<D> &theNode)
{
    out<<theNode.data;
    return out;
}

template<typename D>
istream& operator>>(istream &in, node<D> &theNode)
{
    cout<<"Data: ";
    in>>theNode.data;
}
#endif // NODE_H
