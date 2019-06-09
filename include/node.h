/****
 * This Node class is the primary container used for the AVL tree implementation. It makes use of
 * parent nodes to enable fast traversal.
 *
 * This implementation has been adapted from Paul Wilkinson's CS008 lectures.
 *
 * @author      Rafael Betita
 * @modified    2019-06-08
 * @namespace   avl
 ****/

#ifndef Node_H
#define Node_H

#include "mylib.h"

namespace avl{

template <typename Key, typename Value>
struct Node {

  /** Data **/
  Key key_;
  Value value_;

  Node* left;
  Node* right;
  Node* parent;
  int balance;

  explicit Node (const Key &k = Key(), const Value &val = Value(), Node<Key,Value>* parent_ = nullptr);
  ~Node();
  Node(const Node<Key, Value> &other);

  Node<Key, Value>& operator=(const Node<Key, Value> &other);
  Node<Key, Value>& operator^=(Node<Key, Value> &other); // Swap function

  /** Helper functions **/
  inline void Clear(); // This function clears all values from a Node
  inline void SetLeft(Node<Key, Value> &other);
  inline void SetRight(Node<Key, Value> &other);
  void Set(const Key& key, const Value &val);
  bool is_leaf() const {return (left == nullptr)&&(right == nullptr);}

  template<typename S, typename T>
  friend
  std::ostream& operator<<(std::ostream& out, const Node<S,T> &n);

  template<typename S, typename T>
  friend
  bool operator>>(std::istream& in, Node<S,T> &n);

 private:
  void copy(const Node<Key,Value> &other);
};

/**
* Default constructor for the Node.
* @tparam Key
* @tparam Value
* @param key
* @param val
* @param parent_
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key &key, const Value &val, Node<Key,Value>* parent_)
    : key_(key),
      value_(val),
      balance(0),
      left(nullptr),
      right(nullptr),
      parent(parent_){}

/**
 * This is the destructor for the node, which clears the data within the node
 * and sets own children to nullptr.
 */
template<typename Key, typename Value>
Node<Key,Value>::~Node() {
  key_ = Key();
  value_ = Value();
  left = right = nullptr;
}

/**
 * Copy Constructor for the Node
 * @tparam Key
 * @tparam Value
 * @param other
 */
template<typename Key, typename Value>
Node<Key,Value>::Node(const Node<Key,Value> &other) {
  copy(other);
}

/**
 * Assignment Operator for the Node
 * @tparam Key
 * @tparam Value
 * @param other
 * @return
 */
template<typename Key, typename Value>
Node<Key,Value> &Node<Key,Value>::operator=(const Node<Key,Value> &other) {
  if (this != &other)
    copy(other);
  return *this;
}

/**
* This function swaps the values of two Nodes (not including the child links)
* @tparam Key
* @tparam Value
* @param other
* @return
*/
template<typename Key, typename Value>
Node<Key,Value> &Node<Key,Value>::operator^=(Node<Key,Value> &other) {
  Key temp_key = key_;
  key_ = other.key_;
  other.key_ = temp_key;

  Value temp_val = value_;
  value_ = other.value_;
  other.value_ = temp_val;

  return *this;
}

template<typename Key, typename Value>
void Node<Key,Value>::Set(const Key &key, const Value &val) {
  key_ = key;
  value_ = val;
}

template <typename Key, typename Value>
void Node<Key,Value>::SetLeft(Node<Key,Value> &other) {
  left = other;
}

template<typename Key, typename Value>
void Node<Key,Value>::SetRight(Node<Key,Value> &other) {
  right = other;
}

/**
 * This function simply clears the data within the node, but does not delete the link to its children.
 */
template<typename Key, typename Value>
void Node<Key,Value>::Clear() {
  key_ = Key();
  value_ = Value();
}

template<typename Key, typename Value>
void Node<Key,Value>::copy(const Node<Key,Value> &other) {
  Set(other.key_, other.value_);
  left = other.left;
  right = other.right;
}

template<typename S, typename T>
std::ostream &operator<<(std::ostream &out, const Node<S,T> &n) {
  if (&n != nullptr)
    out << n.key_ << " (" << n.value_ << ')';

  return out;
}

template<typename S, typename T>
bool operator>>(std::istream &in, Node<S,T> &n) {
// todo, implement properly
  if (&in == &std::cin) {
    std::string line;
    std::cout << "Data: ";
    if (std::cin>>n.data_) { // todo: need some data_ validation
      getline(in,line);
      n.name_ = line.empty() ? "" : line;
      fflush(stdin);
      return true;
    } else
      return false;
  }
  else
//      in >> n.data_ >> junk >> n.count >> junk;
//      std::cout << "test"; // todo

    return false;
}

} // end namespace avl

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
    in>>theNode.data;
    return in;
}
}

#endif // Node_H
