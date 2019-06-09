/**
 * This is a multimap implementation using the AVL tree as the base tree.
 * @author  Rafael Betita
 * @modified 2019-06-08
 */

#ifndef BACONS_LAW_INCLUDE_MULTIMAP_H_
#define BACONS_LAW_INCLUDE_MULTIMAP_H_

#include "mylib.h"

namespace cs008 {
template <typename Key, typename Value>
class Multimap {

  struct MultiPair {
    Key key_;
    std::vector<Value> values_;

    friend
    bool operator==(const MultiPair &lhs, const MultiPair &rhs) {
      return lhs.key_ == rhs.key_;
    }

    friend
    bool operator<(const MultiPair &lhs, const MultiPair &rhs) {
      return lhs.key_ < rhs.key_;
    }

    friend
    bool operator>(const MultiPair &lhs, const MultiPair &rhs) {
      return lhs.key_ > rhs.key_;
    }

    MultiPair& operator=(const MultiPair &other) {
      key_ = other.key_;
      if (other.values_.empty()) { // Used for destructor
        this->values_.clear();
      } else {
        values_.push_back(other.values_[0]);
      }

      return *this;
    }

    MultiPair& operator+=(const Value &val) {
      this->values_.push_back(val);
    }

    friend
    std::ostream& operator << (std::ostream &out, const MultiPair &other) {
      out << '[' << other.key_ << "]: {";
      bool first = true;
      for (auto &value : other.values_) {
        if (!first) {
          out << ", ";
        }
        first = false;
        out << value;
      }
      out << "}";
      return out;
    }
  };

 public:
  Multimap() = default;
  ~Multimap() = default;
  Multimap(const Multimap<Key,Value> &other);
  Multimap<Key,Value>& operator=(const Multimap<Key,Value> &other);

  void Insert(const Key& key, const Value &val);
  bool Remove(const Key& key, const Value &val);
  int Count(const Key& key);

  Value& operator[](const Key& key);

  template <typename S, typename T>
  friend
  std::ostream& operator<<(std::ostream &out, Multimap<S,T> &other) {
    out << other.map_;
    return out;
  }

 private:
  avl::BinaryTree<MultiPair> map_;
  void copy(const Multimap<Key,Value> &other);

};

template<typename Key, typename Value>
Multimap<Key, Value>::Multimap(const Multimap<Key, Value> &other) {
  copy(other);
}

template<typename Key, typename Value>
Multimap<Key,Value> &Multimap<Key, Value>::operator=(const Multimap<Key, Value> &other) {
  if (this != &other)
    copy(other);
  return *this;
}

template<typename Key, typename Value>
void Multimap<Key, Value>::Insert(const Key &key, const Value &val) {
  MultiPair temp;
  temp.key_ = key;
  temp.values_.push_back(val);
  map_.Insert(temp);
}

template<typename Key, typename Value>
bool Multimap<Key, Value>::Remove(const Key &key, const Value &val) {
  // todo
}

template<typename Key, typename Value>
Value &Multimap<Key, Value>::operator[](const Key &key) {
  return map_.operator[](key).values_;
}

template<typename Key, typename Value>
void Multimap<Key, Value>::copy(const Multimap<Key, Value> &other) {
//  map_ = other.map_;
//  todo
}
template<typename Key, typename Value>
int Multimap<Key, Value>::Count(const Key &key) {
  MultiPair temp;
  temp.key_ = key;
  return map_.count(temp);
}

} // end namespace cs008

#endif //BACONS_LAW_INCLUDE_MULTIMAP_H_
