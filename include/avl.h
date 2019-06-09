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

template <typename T>
class BinaryTree
{
 public:
  BinaryTree() : root_(nullptr),
                 traversal_(BST_TRAVERSAL::BACKWARD_IN_ORDER){}
  BinaryTree(const T &data, const unsigned int &count);
  ~BinaryTree();
  BinaryTree(const BinaryTree<T> &other);
  BinaryTree<T> &operator=(const BinaryTree<T> &other);

  /** Primary AVL tree functions **/
  BinaryTree<T>& operator<<(const T & data); // Insert operation
  Node<T> ExtractSmallest(); // Extraction operation (smallest first) / no rebalance
  bool Delete(const T &data, const unsigned int &count = 1); // todo: deletion w/rebalance
  void Insert(const T &value); // AVL-Insert w/ rebalance
  T& operator[](T &key);

  /** Constant members **/
  int count(T &data) const;
  bool empty() const {return !root_;}
  int height() const {return height(root_);}
  const Node<T>* root() const {return root_;}

  /** Friend functions **/
  template <typename S>
  friend
  std::ostream& operator<<(std::ostream& out, const BinaryTree<S> &other);

  template <typename S>
  friend
  std::istream& operator>>(std::istream& in, BinaryTree<S> &other);

 private:
  /** Private members **/
  Node<T> *root_;
  BST_TRAVERSAL traversal_;

  /** Rotations **/
  Node<T>* RotateLeft(Node<T> *root);
  Node<T>* RotateRight(Node<T> *root);
  Node<T>* RotateLeftRight(Node<T> *root);
  Node<T>* RotateRightLeft(Node<T> *root);
  void SetBalance(Node<T> *&root, int &&balance);

  void ClearTree(Node<T>*& root);
  void CopyTree(const Node<T> *&&root);
  void DeleteRightChild(Node<T>* &child, Node<T>* &parent);
  Node<T> DeleteLeftChild(Node<T>* &child, Node<T>* &parent);

  unsigned int data_count(Node<T>* root) const;
  unsigned int node_count(Node<T>* root) const;
  Node<T>* Find(const T& data, Node<T> *root, Node<T>* &parent, bool &less_than) const;
  Node<T>* FindSmallest(Node<T>* root) const;
  void PrintTree(std::ostream &out, Node<T>* root, size_t &&depth = 0) const;

//  todo: Unimplemented
//  void CreateNodes();
//  void ResizeNodeStack();

};

/**
 * @brief This function is called when initializing a new tree with a data and count
 * @param data the data being inserted
 * @param count the count of the data
 * @modified 2019-05-18
 */
template <typename T>
avl::BinaryTree<T>::BinaryTree(const T &data, const unsigned int &count) {
  root_ = new Node<T>(data, count);
  traversal_ = avl::BST_TRAVERSAL::IN_ORDER;
}

/**
 * @brief This is the copy constructor for the BinaryTree class
 * @param other
 * @modified 2019-05-18
 */
template <typename T>
avl::BinaryTree<T>::BinaryTree(const BinaryTree<T> &other) {
  CopyTree(other.root());
  traversal_ = other.traversal();
}

/**
 * @brief This is the default destructor for the BinaryTree class
 * @modified 2019-05-18
 */
template <typename T>
avl::BinaryTree<T>::~BinaryTree() {
  ClearTree(root_);
}

/**
 * @brief operator = This is the assignment operator for the BinaryTree class
 * @param other
 * @return the address of the newly assigned tree
 * @modified 2019-05-18
 */
template <typename T>
avl::BinaryTree<T>& avl::BinaryTree<T>::operator=(const BinaryTree<T> &other) {
  if (this != &other) {
    ClearTree(root_);
    CopyTree(other.root());
  }
  return *this;
}

/**
 * @brief operator << This function utilizes the Insert functionality of the BinaryTree class
 * @param data
 * @return
 * @modified 2019-05-18
 */
template <typename T>
avl::BinaryTree<T>& avl::BinaryTree<T>::operator<<(const T & data) {
  Insert(data);
  return *this;
}

/**
 * @brief This function will copy a given tree from its root node
 * @param root
 * @modified 2019-05-18
 * @note This implementation assumes that the caller is already empty
 */
template <typename T>
void avl::BinaryTree<T>::CopyTree(const Node<T>*&&root) {

  if (root == nullptr)
    return;

  Insert(root->data);
  CopyTree(root->left);
  CopyTree(root->right);
}

/**
 * This function will clear the tree from a given root node and return
 * them to the heap.
 *
 * @modified    2019-05-18
 **/
template <typename T>
void avl::BinaryTree<T>::ClearTree(Node<T>*& root) {
  if (root == nullptr)
    return;

  ClearTree(root->left);
  ClearTree(root->right);
  delete root;
  root = nullptr;
}

/**
 * @brief data_count This function will return a total data count for a given root node and its children
 * @param root
 * @return
 * @modified 2019-05-18
 */
template <typename T>
unsigned int avl::BinaryTree<T>::data_count(Node<T>* root) const {
  if (root == nullptr)
    return 0;
  else
    return (root->count + data_count(root->left) + data_count(root->right));
}

/**
 * @brief node_count This function will return a total node count for a given root node and its children
 * @param root
 * @return
 * @modified 2019-05-18
 */
template <typename T>
unsigned int avl::BinaryTree<T>::node_count(Node<T>* root) const {
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
template <typename T>
void avl::BinaryTree<T>::PrintTree(std::ostream &out, Node<T>* root, size_t &&depth) const {

  if (root) {
    if (traversal_ == avl::BST_TRAVERSAL::PRE_ORDER)
      out << std::setw(4*depth) << "" <<  root->data << '[' << root->count << ']' << '\n';

    if (traversal_ == avl::BST_TRAVERSAL::BACKWARD_IN_ORDER)
      PrintTree(out, root->right, depth+1);
    else
      PrintTree(out, root->left, depth+1);

    if (traversal_ == avl::BST_TRAVERSAL::IN_ORDER || traversal_ == avl::BST_TRAVERSAL::BACKWARD_IN_ORDER)
      out << std::setw(4*depth) << "" << root->data << '[' << root->count << ']' << '\n';


    if (traversal_ == avl::BST_TRAVERSAL::BACKWARD_IN_ORDER)
      PrintTree(out, root->left, depth+1);
    else
      PrintTree(out, root->left, depth+1);

    if (traversal_ == avl::BST_TRAVERSAL::POST_ORDER)
      out << std::setw(4*depth) << ""  <<root->data << '[' << root->count << ']' << '\n';
  }

}

/**
 * @brief Delete This function deletes N count occurences from the Binary Tree.
 * Adapted from Paul Wilkinson's CS008 lectures.
 *
 * @param data
 * @param count
 * @modified 2019-06-09
 */
template <typename T>
bool avl::BinaryTree<T>::Delete(const T &data, const unsigned int &count) {
  bool less_than;
  Node<T> *parent = nullptr,
      *child = Find(data, root_, parent, less_than);

  if (child) { // if an item was found..
    child->data -= data; // this triggers any overloaded -= operators
    if ((child->count -= count) < 1) {
      if (less_than)
        DeleteLeftChild(child, parent);
      else
        DeleteRightChild(child, parent);
    }
    return true;
  } else {
    printf("No such item to delete!\n");
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
template <typename T>
avl::Node<T>* avl::BinaryTree<T>::Find(const T& data, Node<T> *root, Node<T>* &parent, bool &less_than) const {

  parent = root;
  less_than = true;
  bool cont = true;

  while (root && cont) {
    if(data == root->data) {
      less_than = (root == parent->left);
      cont = false;
    } else if (data < root->data) {
      parent = root;
      root = root->left;
    } else if (data > root->data) {
      parent = root;
      root = root->right;
    }
  }
  return root; // returns null if not found
}

template <typename S>
std::ostream& operator<<(std::ostream& out, const avl::BinaryTree<S> &other) {
  other.PrintTree(out, other.root_);
  return out;
}

template <typename S>
std::istream& operator>>(std::istream& in, avl::BinaryTree<S> &other) {
  avl::Node<S> temp;
  while (in >> temp) {
    other.Insert(temp.data);
  }
  return in;
}

/**
 * @brief FindSmallest This will return the smallest node for a given root
 * @param root
 * @return
 * @modified 2019-05-18
 */
template <typename T>
avl::Node<T>* avl::BinaryTree<T>::FindSmallest(Node<T>* root) const {
  for ( ; root->left != nullptr; root = root->left);
  return root;
}

/**
 * @brief This function has been adapted from Paul Wilkinson's CS008 lectures.
 * @param child
 * @param parent
 * @modified 2019-05-18
 */
template <typename T>
avl::Node<T> avl::BinaryTree<T>::DeleteLeftChild(Node<T>* &child, Node<T>* &parent) {
  if (child->right) {  // if the child to be deleted has a right child, we need to relink it
    parent->left = child->right;
    FindSmallest(child->right)->left = child->left;
  } else  // if child has no right child, then we proceed to replace the node to be deleted with its left child
    parent->left = child->left;

  Node<T> temp = *child; // this will give a copy of child
  delete child;
  return temp;
}

/**
 * @brief This function has been adapted from Paul Wilkinson's CS008 lectures.
 * @param child
 * @param parent
 * @modified 2019-05-18
 */
template <typename T>
void avl::BinaryTree<T>::DeleteRightChild(Node<T>* &child, Node<T>* &parent) {
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
 * @modified 2019-05-19
 */

/** Example, where x is the root
 *        W                  X
 *      /  \               /  \
 *     A    X            W    C
 *         / \          / \
 *        B   C       A   B
 *
 */
template <typename T>
avl::Node<T>* avl::BinaryTree<T>::RotateLeft(Node<T> *root) { // RR case
  Node<T> *right = root->right;
  Node<T> *rightLeft = right->left;
  Node<T> *parent = root->parent;

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
 * @modified 2019-05-19
 */

/** Where X is the root
 *        X                W
 *       / \              / \
 *     W   C            A    X
 *    / \                   / \
 *   A  B                  B  C
 */

template <typename T>
avl::Node<T>* avl::BinaryTree<T>::RotateRight(Node<T> *root) { // LL case

  Node<T> *left = root->left;
  Node<T> *leftRight = left->right;
  Node<T> *parent = root->parent;

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
 *
 * @tparam T
 * @param root
 * @param balance
 */
template<typename T>
void avl::BinaryTree<T>::SetBalance(Node<T> *&root, int &&balance) {
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

    Node<T> *parent = root->parent;

    if (parent)
      balance = (parent->left == root) ? 1 : -1;

    root = parent;


  }
}

/**
 * @brief This function rotates a given node and its children twice (RL case)
 * @param root
 * @return
 * @modified 2019-05-19
 */
template <typename T>
avl::Node<T>* avl::BinaryTree<T>::RotateRightLeft(Node<T> *root) { // also known as left right case
  Node<T> *right = root->right;
  Node<T> *rightLeft = right->left;
  Node<T> *parent = root-> parent;
  Node<T> *rightLeftLeft = rightLeft->left;
  Node<T> *rightLeftRight = rightLeft->right;

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
 * @modified 2019-05-19
 */
template <typename T>
avl::Node<T>* avl::BinaryTree<T>::RotateLeftRight(Node<T> *root) { // also known as right left case

  Node<T> *left = root->left;
  Node<T> *leftRight = left->right;
  Node<T> *parent = root-> parent;
  Node<T> *leftRightRight = leftRight->right;
  Node<T> *leftRightLeft = leftRight->left;

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

template <typename T>
avl::Node<T> avl::BinaryTree<T>::ExtractSmallest() {

  if (root_ == nullptr)
    throw BST_ERRORS::EMPTY;

  Node<T> *parent, *min = root_;

  // This finds the lowest element in the tree, as well as its parent
  for ( ; min->left != nullptr; min = min->left) {
    parent = min;
  };

  Node <T> temp = *min;
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
 * @tparam T
 * @param value
 * @modified 2019-06-08
 */
template <typename T>
void avl::BinaryTree<T>::Insert(const T &value) {
  if (root_ == nullptr)
  { // todo add node stack implementation
    root_ = new Node<T>(value, 1, nullptr);
  } else {
    Node<T> *temp = root_;

    while (temp != nullptr) {
      if (temp->data == value) {
        temp->data = value; // This will trigger an overloaded assignment operator
        ++temp->count;
        return;
      }
      else if (temp->data > value) {
        if (!temp->left) { // if left child doesn't exist, add new node
          temp->left = new Node<T>(value, 1, temp);
          SetBalance(temp, 1);
          return;
        }
        else
          temp = temp->left;
      } else if (temp->data < value) {
        if (!temp->right) {
          temp->right = new Node<T>(value, 1, temp);
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
 * @tparam T
 * @param key
 * @return
 *
 * @todo https://en.cppreference.com/w/cpp/container/map/operator_at Add move semantic functionality
 * @todo Get rid of extraneous variables in Find
 */
template<typename T>
T& BinaryTree<T>::operator[](T &key) {
  Node<T> *parent = nullptr;
  Node<T> *find = nullptr;
  bool less_than; //todo get rid of?
  find = Find(key, root_, parent, less_than);

//  if (!find) {
//    Insert(key);
//    find = Find(key, root_, parent, true);
//  }

  return (find->data);
}

template<typename T>
int BinaryTree<T>::count(T &data) const {
  bool less = false;
  Node<T> *parent_ptr = nullptr,
          *ptr = Find(data,root_, parent_ptr, less);

  return (ptr) ? (ptr->count) : 0;
}

} // end namespace avl


#endif //BACONS_LAW_INCLUDE_AVL_H_