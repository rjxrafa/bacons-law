#ifndef BACONS_LAW_INCLUDE_AVL_H_
#define BACONS_LAW_INCLUDE_AVL_H_

/****
 * This Binary Tree class is based on the Adelson-Velsky and Landis (AVL) self balancing tree.
 *
 * The class has been adapted from Paul Wilkinson's CS008 lectures and
 * Keith Wood's efficient AVL implementation @ bitlush.com.
 *
 * @author      Rafael Betita
 * @modified    2019-06-08
 * @namespace   avl
 ****/

#include "node.h"

namespace avl {

enum class BST_TRAVERSAL{PRE_ORDER, IN_ORDER, POST_ORDER, BACKWARD_IN_ORDER};
enum class BST_ERRORS{EMPTY};

template <typename Key, typename Value>
class BinaryTree
{
 public:
  BinaryTree() : root_(nullptr),
                 traversal_(BST_TRAVERSAL::BACKWARD_IN_ORDER){}
  BinaryTree(const Key &key, const Value &val);
  ~BinaryTree();
  BinaryTree(const BinaryTree<Key,Value> &other);
  BinaryTree<Key,Value> &operator=(const BinaryTree<Key,Value> &other);

  /** Primary AVL tree functions **/
  Node<Key,Value> ExtractSmallest(); // Extraction operation (smallest first) / no rebalance
  bool Delete(const Key &key); // todo: deletion w/rebalance
  void Insert(const Key &key, const Value &val); // AVL-Insert w/ rebalance
  Value& operator[](Key &&key);

  /** Constant members **/
  bool empty() const {return !root_;}
  int height() const {return height(root_);}
  const Node<Key,Value>* root() const {return root_;}

  /** Friend functions **/
  template <typename S, typename T>
  friend
  std::ostream& operator<<(std::ostream& out, const BinaryTree<S,T> &other);

  template <typename S, typename T>
  friend
  std::istream& operator>>(std::istream& in, BinaryTree<S,T> &other);

 private:
  /** Private members **/
  Node<Key,Value> *root_;
  BST_TRAVERSAL traversal_;

  /** Rotations **/
  Node<Key,Value>* RotateLeft(Node<Key,Value> *root);
  Node<Key,Value>* RotateRight(Node<Key,Value> *root);
  Node<Key,Value>* RotateLeftRight(Node<Key,Value> *root);
  Node<Key,Value>* RotateRightLeft(Node<Key,Value> *root);
  void SetBalance(Node<Key,Value> *&root, int &&balance);

  void ClearTree(Node<Key,Value>*& root);
  void CopyTree(const Node<Key,Value>& root);
  void DeleteRightChild(Node<Key,Value>* &child, Node<Key,Value>* &parent);
  Node<Key,Value> DeleteLeftChild(Node<Key,Value>* &child, Node<Key,Value>* &parent);

  unsigned int node_count(Node<Key,Value>* root) const;
  Node<Key,Value>* Find(const Key& key, Node<Key,Value> *root, Node<Key,Value>* &parent, bool &less_than) const;
  Node<Key,Value>* FindSmallest(Node<Key,Value>* root) const;
  void PrintTree(std::ostream &out, Node<Key,Value>* root, size_t &&depth = 0) const;

  
};

/**
 * @brief This function is called when initializing a new tree with a data and count
 * @param key - the key of the data being inserted
 * @param value - the value of the key value pair
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::BinaryTree<Key,Value>::BinaryTree(const Key &key, const Value &val) {
  root_ = new Node<Key,Value>(key, val);
  traversal_ = avl::BST_TRAVERSAL::IN_ORDER;
}

/**
 * @brief This is the copy constructor for the BinaryTree class
 * @param other
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::BinaryTree<Key,Value>::BinaryTree(const BinaryTree<Key,Value> &other) {
  CopyTree(other.root());
  traversal_ = other.traversal();
}

/**
 * @brief This is the default destructor for the BinaryTree class
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::BinaryTree<Key,Value>::~BinaryTree() {
  ClearTree(root_);
}

/**
 * @brief operator = This is the assignment operator for the BinaryTree class
 * @param other
 * @return the address of the newly assigned tree
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::BinaryTree<Key,Value>& avl::BinaryTree<Key,Value>::operator=(const BinaryTree<Key,Value> &other) {
  if (this != &other) {
    ClearTree(root_);
    CopyTree(other.root());
  }
  return this;
}

/**
 * @brief This function will copy a given tree from its root node
 * @param root
 * @modified 2019-06-08
 * @note This implementation assumes that the caller is already empty
 */
template <typename Key, typename Value>
void avl::BinaryTree<Key,Value>::CopyTree(const Node<Key,Value>& root) {

  if (root == nullptr)
    return;

  Insert(root.key_, root.count);
  CopyTree(root.left);
  CopyTree(root.right);
}

/**
 * This function will clear the tree from a given root node and return
 * them to the heap.
 *
 * @modified    2019-05-18
 **/
template <typename Key, typename Value>
void avl::BinaryTree<Key,Value>::ClearTree(Node<Key,Value>*& root) {
  if (root == nullptr)
    return;

  ClearTree(root->left);
  ClearTree(root->right);
  delete root;
  root = nullptr;
}

/**
 * @brief node_count This function will return a total node count for a given root node and its children
 * @param root
 * @return
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
unsigned int avl::BinaryTree<Key,Value>::node_count(Node<Key,Value>* root) const {
  if (root == nullptr)
    return 0;
  else
    return (1 + node_count(root->left) + node_count(root->right));
}

/**
 * @brief This function prints a given tree depending on the method passed
 * @param root
 * @param method
 * @modified 2019-05-25
 */
template <typename Key, typename Value>
void avl::BinaryTree<Key,Value>::PrintTree(std::ostream &out, Node<Key,Value>* root, size_t &&depth) const {

  if (root) {
    if (traversal_ == avl::BST_TRAVERSAL::PRE_ORDER)
      out << std::setw(4*depth) << "" <<  root->key_ << ':' << root->value_ << '\n';

    if (traversal_ == avl::BST_TRAVERSAL::BACKWARD_IN_ORDER)
      PrintTree(out, root->right, depth+1);
    else
      PrintTree(out, root->left, depth+1);

    if (traversal_ == avl::BST_TRAVERSAL::IN_ORDER || traversal_ == avl::BST_TRAVERSAL::BACKWARD_IN_ORDER)
      out << std::setw(4*depth) << "" << root->key_ << ':' << root->value_ << '\n';


    if (traversal_ == avl::BST_TRAVERSAL::BACKWARD_IN_ORDER)
      PrintTree(out, root->left, depth+1);
    else
      PrintTree(out, root->left, depth+1);

    if (traversal_ == avl::BST_TRAVERSAL::POST_ORDER)
      out << std::setw(4*depth) << ""  << root->key_ << ':' << root->value_ << '\n';
  }

}

/**
 * @brief Delete This function deletes a given key from the tree. Adapted from
 * Paul Wilkinson's CS008 lectures.
 *
 * @param data
 * @param count
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
bool avl::BinaryTree<Key,Value>::Delete(const Key &key) {
  // todo implement rebalancing
  bool less_than;
  Node<Key,Value> *parent = nullptr,
      *child = Find(key, root_, parent, less_than);

  if (child) { // if an item was found..
    if (less_than)
      DeleteLeftChild(child, parent);
    else
      DeleteRightChild(child, parent);
    return true;
  } else {
    std::cout << "Key not found";
    return false;
  }
}

/**
 * This function will search for a given data within the avl tree and its parent. If the item is
 * not found, the node returned will be null. This function was adapted from Paul Wilkinson's CS008 lectures.
 *
 * @modified 2019-06-05
 * @tparam T
 * @param data
 * @param root
 * @param parent
 * @param less_than
 * @return
 */
template <typename Key, typename Value>
avl::Node<Key,Value>* avl::BinaryTree<Key,Value>::Find(const Key& key,
                                                       Node<Key,Value> *root,
                                                       Node<Key,Value>* &parent,
                                                       bool &less_than) const {
  parent = root;
  less_than = true;
  bool cont = true;

  while (root && cont) {
    if(key == root->key_) {
      less_than = (root == parent->left);
      cont = false;
    } else if (key < root->key_) {
      parent = root;
      root = root->left;
    } else if (key > root->key_) {
      parent = root;
      root = root->right;
    }
  }
  return root; // returns null if not found
}

template <typename S, typename T>
std::ostream& operator<<(std::ostream& out, const avl::BinaryTree<S,T> &other) {
  other.PrintTree(out, other.root_);
  return out;
}

template <typename S, typename T>
std::istream& operator>>(std::istream& in, avl::BinaryTree<S,T> &other) {
  avl::Node<S,T> temp;
  while (in >> temp) {
    other.Insert(temp.key_, temp.value_);
  }
  return in;
}

/**
 * @brief FindSmallest This will return the smallest node for a given root
 * @param root
 * @return
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::Node<Key,Value>* avl::BinaryTree<Key,Value>::FindSmallest(Node<Key,Value>* root) const {
  for ( ; root->left != nullptr; root = root->left);
  return root;
}

/**
 * @brief This function has been adapted from Paul Wilkinson's CS008 lectures.
 * @param child
 * @param parent
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::Node<Key,Value> avl::BinaryTree<Key,Value>::DeleteLeftChild(Node<Key,Value>* &child,
                                                                 Node<Key,Value>* &parent) {
  if (child->right) {  // if the child to be deleted has a right child, we need to relink it
    parent->left = child->right;
    FindSmallest(child->right)->left = child->left;
  } else  // if child has no right child, then we proceed to replace the node to be deleted with its left child
    parent->left = child->left;

  Node<Key,Value> temp = *child; // this will give a copy of child
  delete child;
  return temp;
}

/**
 * @brief This function has been adapted from Paul Wilkinson's CS008 lectures.
 * @param child
 * @param parent
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
void avl::BinaryTree<Key,Value>::DeleteRightChild(Node<Key,Value>* &child, Node<Key,Value>* &parent) {
  if (parent == root_) { // special case: when deleting the root's right child
    if (root_->right) {
      root_ = root_->right;
      FindSmallest(root_)->left = parent->left;
    } else {
      root_ = root_->left;
    }
    delete parent;

  } else {
    if (child->right) {
      parent->right = child->right;
      FindSmallest(child->right)->left = child->left;
    }// if child has a right, we need to relink
    else
      parent->right = child->left;
    delete child;
  }
}

/**
 * @brief This function rotates a given node and its right child (and any subtrees)
 * @param root
 * @return
 * @modified 2019-06-08
 */

/** Example, where x is the root
 *        W                  X
 *      /  \               /  \
 *     A    X            W    C
 *         / \          / \
 *        B   C       A   B
 *
 */
template <typename Key, typename Value>
avl::Node<Key,Value>* avl::BinaryTree<Key,Value>::RotateLeft(Node<Key,Value> *root) { // RR case
  Node<Key,Value> *right = root->right;
  Node<Key,Value> *rightLeft = right->left;
  Node<Key,Value> *parent = root->parent;

  right->parent = parent;
  right->left = root;
  root->right = rightLeft;
  root->parent = right;

  if (rightLeft)
    rightLeft->parent = root;

  if (root == root_)
    root_ = right;
  else if (parent->right == root)
    parent->right = right;
  else
    parent->left = right;

  ++right->balance;
  root->balance = -right->balance;

  return right;
}

/**
 * @brief This function rotates a given node and its left child (and any subtrees)
 * @param root
 * @return
 * @modified 2019-06-08
 */

/** Where X is the root
 *        X                W
 *       / \              / \
 *     W   C            A    X
 *    / \                   / \
 *   A  B                  B  C
 */

template <typename Key, typename Value>
avl::Node<Key,Value>* avl::BinaryTree<Key,Value>::RotateRight(Node<Key,Value> *root) { // LL case

  Node<Key,Value> *left = root->left;
  Node<Key,Value> *leftRight = left->right;
  Node<Key,Value> *parent = root->parent;

  left->parent = parent;
  left->right = root;
  root->left = leftRight;
  root->parent = left;

  if (leftRight != nullptr)
    leftRight->parent = root;

  if (root == root_)
    root_ = left;
  else if (parent->left == root)
    parent->left = left;
  else
    parent->right = left;

  --left->balance;
  root->balance = -left->balance;

  return left;
}

/**
 * This function is the primary rebalance function for the AVL implementation. Adapted from Mike Wood's AVL
 * C# efficient avl tree implementation

 * @tparam Key
 * @tparam Value
 * @param root
 * @param balance
 * @modified 2019-06-08
 */
template<typename Key, typename Value>
void avl::BinaryTree<Key,Value>::SetBalance(Node<Key,Value> *&root, int &&balance) {
  while (root) {
    balance = root->balance += balance;

    if (balance == 0)
      return;
    else if (balance == 2) {
      if (root->left->balance == 1)
        RotateRight(root);
      else
        RotateLeftRight(root);

      return;
    } else if (balance == -2) {
      if (root->right->balance == -1)
        RotateLeft(root);
      else
        RotateRightLeft(root);

      return;
    }

    Node<Key,Value> *parent = root->parent;

    if (parent)
      balance = (parent->left == root) ? 1 : -1;

    root = parent;


  }
}

/**
 * @brief This function rotates a given node and its children twice (RL case)
 * @param root
 * @return
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::Node<Key,Value>* avl::BinaryTree<Key,Value>::RotateRightLeft(Node<Key,Value> *root) { // also known as left right case
  Node<Key,Value> *right = root->right;
  Node<Key,Value> *rightLeft = right->left;
  Node<Key,Value> *parent = root-> parent;
  Node<Key,Value> *rightLeftLeft = rightLeft->left;
  Node<Key,Value> *rightLeftRight = rightLeft->right;

  rightLeft->parent = parent;
  root->right = rightLeftLeft;
  right->left = rightLeftRight;
  rightLeft->right = right;
  rightLeft->left = root;
  right->parent = rightLeft;
  root->parent = rightLeft;

  if (rightLeftLeft)
    rightLeftLeft->parent = root;

  if (rightLeftRight)
    rightLeftRight->parent = right;

  if (root == root_)
    root_ = rightLeft;
  else if (parent->right == root)
    parent->right = rightLeft;
  else
    parent->left = rightLeft;

  if (rightLeft->balance == 1) {
    root->balance = 0;
    right->balance = -1;
  } else if (rightLeft->balance == 0) {
    root->balance = 0;
    right->balance = 0;
  } else {
    root->balance = 1;
    right->balance = 0;
  }

  rightLeft->balance = 0;

  return rightLeft;
}

/**
 * @brief This function rotates a given node and its children twice (LR case)
 * @param root
 * @return
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
avl::Node<Key,Value>* avl::BinaryTree<Key,Value>::RotateLeftRight(Node<Key,Value> *root) { // also known as right left case

  Node<Key,Value> *left = root->left;
  Node<Key,Value> *leftRight = left->right;
  Node<Key,Value> *parent = root-> parent;
  Node<Key,Value> *leftRightRight = leftRight->right;
  Node<Key,Value> *leftRightLeft = leftRight->left;

  leftRight->parent = parent;
  root->left = leftRightRight;
  left->right = leftRightLeft;
  leftRight->left = left;
  leftRight->right = root;
  left->parent = leftRight;
  root->parent = leftRight;

  if (leftRightRight)
    leftRightRight->parent = root;

  if (leftRightLeft)
    leftRightLeft->parent = left;

  if (root == root_)
    root_ = leftRight;
  else if (parent->left == root)
    parent->left = leftRight;
  else
    parent->right = leftRight;

  if (leftRight->balance == -1) {
    root->balance = 0;
    left->balance = 1;
  } else if (leftRight->balance == 0) {
    root->balance = 0;
    left->balance = 0;
  } else {
    root->balance = -1;
    left->balance = 0;
  }

  leftRight->balance = 0;

  return leftRight;
}

template <typename Key, typename Value>
avl::Node<Key,Value> avl::BinaryTree<Key,Value>::ExtractSmallest() {

  if (root_ == nullptr)
    throw BST_ERRORS::EMPTY;

  Node<Key,Value> *parent, *min = root_;

  // This finds the lowest element in the tree, as well as its parent
  for ( ; min->left != nullptr; min = min->left) {
    parent = min;
  };

  Node <Key,Value> temp = *min;
  if (min == root_) {
    root_ = root_->right;
    delete min;
    return temp;
  } else {
    return DeleteLeftChild(min, parent);
  }
}

/**
 * This function is the insertion function for the AVL implementation. Adapted from Mike Wood's AVL
 * C# efficient AVL tree implementation
 *
 * @tparam Key
 * @tparam Value
 * @param key
 * @param val
 * @modified 2019-06-08
 */
template <typename Key, typename Value>
void avl::BinaryTree<Key,Value>::Insert(const Key &key, const Value &val) {
  if (root_ == nullptr)
  { // todo add node stack implementation
    root_ = new Node<Key,Value>(key, val, nullptr);
  } else {
    Node<Key,Value> *temp = root_;

    while (temp != nullptr) {
      if (temp->key_ == key) {
        return;
      }
      else if (temp->key_ > key) {
        if (!temp->left) { // if left child doesn't exist, add new node
          temp->left = new Node<Key,Value>(key, val, temp);
          SetBalance(temp, 1);
          return;
        }
        else
          temp = temp->left;
      } else if (temp->key_ < key) {
        if (!temp->right) {
          temp->right = new Node<Key,Value>(key, val, temp);
          SetBalance (temp, -1);
          return;
        } else
          temp = temp->right;
      }

    }

  }
}

/**
 * This function overloads the at operator in order to access a given key's value.
 * If not found, the item is inserted and the reference to that item is returned.
 *
 * @tparam Key
 * @tparam Value
 * @param key
 * @return
 *
 * @todo https://en.cppreference.com/w/cpp/container/map/operator_at Add move semantic functionality
 * @todo Get rid of extraneous variables in Find
 */
template<typename Key, typename Value>
Value& BinaryTree<Key,Value>::operator[](Key &&key) {
  Node<Key,Value> *parent = nullptr;
  Node<Key,Value> *find = nullptr;
  bool less_than; //todo get rid of?
  find = Find(key, root_, parent, less_than);

//  if (!find) {
//    Insert(key, valu);
//    find = Find(key, root_, parent, true);
//  }

  return (find->key_);
}

} // end namespace avl


#endif //BACONS_LAW_INCLUDE_AVL_H_
