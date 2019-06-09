/**
 * This is a map implementation using the AVL tree as the base tree.
 * @author  Rafael Betita
 * @modified 2019-06-08
 * @namespace cs8
 */

#ifndef BACONS_LAW_INCLUDE_MAP_H_
#define BACONS_LAW_INCLUDE_MAP_H_

#include "avl.h"

namespace cs8{

/**
 * This map implementation uses the
 * @tparam Key
 * @tparam Value
 */
template <typename Key, typename Value>
class Map {

  struct Pair {
    Key key_;
    Value value_;

    // These operators are required because in the AVL class,
    // they are comparing the templated data node. If we make this
    // {Pair} the template data for the avl, we can take advantage
    // of overloaded operators to do the comparing for the keys.

    friend
    bool operator==(const Pair &lhs, const Pair &rhs) {
      return lhs.key_ == rhs.key_;
    }

    friend
    bool operator<(const Pair &lhs, const Pair &rhs) {
      return lhs.key_ < rhs.key_;
    }

    friend
    bool operator>(const Pair &lhs, const Pair &rhs) {
      return lhs.key_ > rhs.key_;
    }

    Pair& operator=(const Pair &other) {
      key_ = other.key_;
      value_ = other.value_;
      return *this;
    }

    Pair & operator-=(const Pair &other) {
      // Do nothing, the count should handle any deletions. An overload is necessary however.
      return *this;
    }

    friend
    std::ostream& operator <<(std::ostream &out, const Pair &other) {
      out << other.key_ << ':' << other.value_;
      return out;
    }

  };

 public:
  Map() = default;
  ~Map() = default;
  Map(const Map& other);
  Map& operator=(const Map<Key,Value> &other);

  void Insert(const Key &key, const Value &value);
  bool Remove(const Key &&key);
  int Count(const Key &key);

  Value& operator[](const Key& key);

  template <typename S, typename T>
  friend
  std::ostream& operator<<(std::ostream &out, Map<S,T> &other) {
    out << other.map_;
    return out;
  }

 private:
  avl::BinaryTree<Pair> map_;
  void copy(const Map<Key,Value> &other);

};

template<typename Key, typename Value>
Map<Key,Value>::Map(const Map<Key,Value> &other) {
  copy(other);
}

template<typename Key, typename Value>
Map<Key,Value> &Map<Key, Value>::operator=(const Map<Key,Value> &other) {
  if (this != &other)
    copy(other);
  return *this;
}

template<typename Key, typename Value>
void Map<Key,Value>::Insert(const Key &key, const Value &value) {
  Pair temp;

  temp.key_ = key;
  temp.value_ = value;

  map_.Insert(temp);
}

template<typename Key, typename Value>
bool Map<Key,Value>::Remove(const Key &&key) {
  Pair temp;
  temp.key_ = key;

  return map_.Delete(temp);
}

template<typename Key, typename Value>
Value& Map<Key,Value>::operator[](const Key &key) {

  Pair temp;
  temp.key_ = key;

  return map_.operator[](temp).value_;
}

template<typename Key, typename Value>
void Map<Key,Value>::copy(const Map<Key,Value> &other) {
  map_ = other.map_;
}

template<typename Key, typename Value>
int Map<Key, Value>::Count(const Key &key) {

  Pair temp;
  temp.key_ = key;

  return map_.count(temp);
}

} //end cs8 namespace

#endif //BACONS_LAW_INCLUDE_MAP_H_
