/**
 * This is a map implementation using the AVL tree as the base tree.
 */

#ifndef BACONS_LAW_INCLUDE_MAP_H_
#define BACONS_LAW_INCLUDE_MAP_H_

#include "avl.h"

namespace cs008{

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
  Map& operator=(const Map &other);

  void Insert(const Key &key, const Value &value);
  bool Remove(const Key &key);

  Value& operator[](const Key& key);

  template <typename S, typename T>
  friend
  std::ostream& operator<<(std::ostream &out, Map<S,T> &other) {
    out << other.map_;
    return out;
  }

 private:
  avl::BinaryTree<Pair> map_;
  void copy(Map &other);

};

template<typename Key, typename Value>
Map<Key, Value>::Map(const Map &other) {
  if (this != &other)
    copy(other);
  return *this;
}

template<typename Key, typename Value>
Map<Key,Value> &Map<Key, Value>::operator=(const Map &other) {
  copy(other);
  return this;
}

template<typename Key, typename Value>
void Map<Key, Value>::Insert(const Key &key, const Value &value) {
  Pair temp;

  temp.key_ = key;
  temp.value_ = value;

  map_.Insert(temp);
}

template<typename Key, typename Value>
bool Map<Key, Value>::Remove(const Key &key) {
  Pair temp;
  temp.key_ = key;

  return map_.Delete(temp);
}

template<typename Key, typename Value>
Value& Map<Key, Value>::operator[](const Key &key) {

  Pair temp;
  temp.key_ = key;

  return map_.operator[](temp).value_;
}

template<typename Key, typename Value>
void Map<Key, Value>::copy(Map &other) {
//todo
}

}

#endif //BACONS_LAW_INCLUDE_MAP_H_