/****
 * This Node class is the primary container used for the AVL tree implementation. It makes use of
 * parent nodes to enable fast traversal.
 *
 * This implementation has been adapted from Paul Wilkinson's CS008 lectures.
 *
 * @author      Rafael Betita
 * @modified    05-25-2019
 * @namespace   bst
 ****/

#ifndef Node_H
#define Node_H

#include "mylib.h"

namespace avl{

template <typename T>
struct Node {

  /** Data **/
  T data;
  int count;

  Node* left;
  Node* right;
  Node* parent;
  int balance;

  explicit Node (const T &data = T(), const unsigned int &c = 1, Node<T>* parent_ = nullptr);
  ~Node();
  Node(const Node<T> &other);

  Node<T>& operator=(const Node<T> &other);
  Node<T>& operator^=(Node<T> &other); // Swap function
  Node<T>& operator-=(const unsigned int &c);
  Node<T>& operator+=(const unsigned int &c);

  /** Helper functions **/
  inline bool empty() const;
  inline void Clear(); // This function clears all values from a Node
  inline void SetLeft(Node<T> &other);
  inline void SetRight(Node<T> &other);
  void Set(const T& d, const unsigned int &c);
  bool is_leaf() const {return (left == nullptr)&&(right == nullptr);}
  bool operator==(T const& rhs) const { return this->data == rhs;}

  /** Node-Node comparison operators **/
  template<typename S>
  friend
  bool operator<(const Node<S> &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator<=(const Node<S> &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator>(const Node<S> &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator>=(const Node<S> &x, const Node<S> &y);

  // This will check for data match
  template<typename S>
  friend
  bool operator==(const Node<S> &x, const Node<S> &y);

  // This will check for exact match (data & count)
  template<typename S>
  friend
  bool operator&=(const Node<S> &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator!=(const Node<S> &x, const Node<S> &y);

  /** Data-Node comparison operators **/
  template<typename S>
  friend
  bool operator<(const S &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator<=(const S &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator>(const S &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator>=(const S &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator==(const S &x, const Node<S> &y);

  template<typename S>
  friend
  bool operator!=(const S &x, const Node<S> &y);

  /** Node-Data comparison operators **/
  template<typename S>
  friend
  bool operator<(const Node<S> &x, const S &y);

  template<typename S>
  friend
  bool operator<=(const Node<S> &x, const S &y);

  template<typename S>
  friend
  bool operator>(const Node<S> &x, const S &y);

  template<typename S>
  friend
  bool operator>=(const Node<S> &x, const S &y);

  template<typename S>
  friend
  bool operator==(const Node<S> &x, const S &y);

  template<typename S>
  friend
  bool operator!=(const Node<S> &x, const S &y);

  template<typename S>
  friend
  std::ostream& operator<<(std::ostream& out, const Node<S> &n);

  template<typename S>
  friend
  bool operator>>(std::istream& in, Node<S> &n);

 private:
  void copy(const Node<T> &other);
};


/**
 * @brief Default constructor for the Node
 * @param d the data
 * @param c the count of the data
 */
template<typename T>
Node<T>::Node(const T &d, const unsigned int &c, Node<T>* parent_)
    : data(d),
      count(c),
      balance(0),
      left(nullptr),
      right(nullptr),
      parent(parent_){}

/**
 * This is the destructor for the node, which clears the data within the node and sets own children to
 * nullptr.
 */
template<typename T>
Node<T>::~Node() {
  data = T();
  count = 0;
  left = right = nullptr;
}

template<typename T>
Node<T>::Node(const Node<T> &other) {
  copy(other);
}

template<typename T>
Node<T> &Node<T>::operator=(const Node<T> &other) {
  if (this != &other)
    copy(other);
  return *this;
}

/**
 * This function swaps the values of two Nodes (not including the child links)
 * @tparam T
 * @param other
 * @return
 */
template<typename T>
Node<T> &Node<T>::operator^=(Node<T> &other) {
  T temp = data;
  data = other.data;
  other.data = temp;

  // XOR Swap for ints
  other.count ^= count ^= other.count ^= count;

  return *this;
}

template<typename T>
Node<T> &Node<T>::operator-=(const unsigned int &c) {
// if c is greater than current count, then set count to 0, otherwise, subtract c from count
  count = (c>=count) ? 0 : count - c;
  return *this;
}

template<typename T>
Node<T> &Node<T>::operator+=(const unsigned int &c) {
  count += c;
  return *this;
}

template<typename T>
bool Node<T>::empty() const {
  return count == 0;
}

template<typename T>
void Node<T>::Set(const T &d, const unsigned int &c) {
  data = d;
  count = c;
}

template <typename T>
void Node<T>::SetLeft(Node<T> &other) {
  left = other;
}

template<typename T>
void Node<T>::SetRight(Node<T> &other) {
  right = other;
}

/**
 * This function simply clears the data within the node, but does not delete the link to its children.
 */
template<typename T>
void Node<T>::Clear() {
  data = T();
  count = 0;
}

template<typename T>
void Node<T>::copy(const Node<T> &other) {
  Set(other.data, other.count);
  left = other.left;
  right = other.right;
}

/** Node-Node comparison operators **/

template<typename S>
bool operator<(const Node<S> &x, const Node<S> &y) {
  return x.data < y.data;
}

template<typename S>
bool operator<=(const Node<S> &x, const Node<S> &y) {
  return x.data <= y.data;
}

template<typename S>
bool operator>(const Node<S> &x, const Node<S> &y) {
  return x.data > y.data;
}

template<typename S>
bool operator>=(const Node<S> &x, const Node<S> &y) {
  return x.data >= y.data;
}

template<typename S>
bool operator==(const Node<S> &x, const Node<S> &y) {
  return x.data == y.data;
}

template<typename S>
bool operator&=(const Node<S> &x, const Node<S> &y) {
  return (x.data == y.data) && (x.count == y.count);
}

template<typename S>
bool operator!=(const Node<S> &x, const Node<S> &y) {
  return x.data != y.data;
}

/** Data-Node comparison operators **/

template<typename S>
bool operator<(const S &x, const Node<S> &y) {
  return x < y.data;
}

template<typename S>
bool operator<=(const S &x, const Node<S> &y) {
  return x <= y.data;
}

template<typename S>
bool operator>(const S &x, const Node<S> &y) {
  return x > y.data;
}

template<typename S>
bool operator>=(const S &x, const Node<S> &y) {
  return x >= y.data;
}

template<typename S>
bool operator==(const S &x, const Node<S> &y) {
  return x == y.data;
}

template<typename S>
bool operator!=(const S &x, const Node<S> &y) {
  return x != y.data;
}

/** Node-data comparison operators **/

template<typename S>
bool operator<(const Node<S> &x, const S &y) {
  return x.data < y;
}

template<typename S>
bool operator<=(const Node<S> &x, const S &y) {
  return x.data <= y;
}

template<typename S>
bool operator>(const Node<S> &x, const S &y) {
  return x.data > y;
}

template<typename S>
bool operator>=(const Node<S> &x, const S &y) {
  return x.data >= y;
}

template<typename S>
bool operator==(const Node<S> &x, const S &y) {
  return x.data == y;
}

template<typename S>
bool operator!=(const Node<S> &x, const S &y) {
  return x.data != y;
}

template<typename S>
std::ostream &operator<<(std::ostream &out, const Node<S> &n) {
  if (&n != nullptr)
    out << n.data << " (" << n.count << ')';

  return out;
}

template<typename S>
bool operator>>(std::istream &in, Node<S> &n) {
//    char junk;
  if (&in == &std::cin) {
    std::string line;
    std::cout << "Data: ";
    if (std::cin>>n.data) { // todo: need some data validation
      getline(in,line);
      n.count = line.empty() ? 1 : stoi(line);
      fflush(stdin);
      return true;
    } else
      return false;
  }
  else
//        in >> n.data >> junk >> n.count >> junk;
    //  std::cout << "test"; // todo

    return false;
}

} // end namespace avl

/**
 * @brief   The CompareNodes struct
 * @author  Ara Mico Segismundo
 *
 * Instructions to tell a priority queue stl how to compare nodes
 */
struct CompareNodes {
  bool operator()(const avl::Node<std::string>& x, const avl::Node<std::string>& y) {
    return x.count < y.count;
  }
};

namespace Q {
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

} // end namespace Q

#endif // Node_H