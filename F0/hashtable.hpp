#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <string>
#include <utility>
#include <vector>

#define INITIAL_SIZE 10

namespace zagrivnyy
{
  template< class T >
  struct node_t
  {
    std::string key;
    T value;
    node_t *next;
  };

  template< class T >
  class hash_table
  {
  public:
    hash_table(size_t size = INITIAL_SIZE);
    ~hash_table();

    void insert(std::pair< std::string, T > item);
    bool erase(std::string key);
    void clear();
    size_t hash_function(std::string key) const;
    T &at(const std::string &keyWord) const;

    class iterator;

    iterator begin() const
    {
      return iterator(this->arr_[0]);
    }

    iterator end() const
    {
      return nullptr;
    }

    iterator find(const std::string &keyWord);

  private:
    size_t base_size_;
    node_t< T > **arr_;
    size_t count_;
    size_t *bucket_size_;

    bool empty(const size_t key);
  };

  template< class T >
  class hash_table< T >::iterator: public std::iterator< std::forward_iterator_tag, T >, public hash_table< T >
  {
  public:
    iterator(node_t< T > *otherIt = nullptr);
    iterator(const iterator &otherIt) = default;
    ~iterator() = default;

    iterator &operator=(const iterator &other);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;
    bool operator<(const iterator &other) const;
    bool operator>(const iterator &other) const;
    bool operator<=(const iterator &other) const;
    bool operator>=(const iterator &other) const;
    iterator operator+(size_t incr);
    iterator operator+=(size_t incr);
    iterator &operator++();
    iterator operator++(int);
    T &operator[](size_t incr);
    std::pair< std::string, T > operator*();
    const std::pair< std::string, T > &operator*() const;
    std::pair< std::string, T > *operator->() const;

  private:
    node_t< T > *head;
    std::pair< std::string, T > junk;
  };

}

template< class T >
inline zagrivnyy::hash_table< T >::hash_table(size_t size)
{
  this->base_size_ = size;
  this->arr_ = new node_t< T > *[this->base_size_];
  for (size_t i = 0; i < this->base_size_; ++i)
  {
    this->arr_[i] = nullptr;
    this->bucket_size_[i] = 0;
  }
  this->count_ = 0;
}

template< class T >
void zagrivnyy::hash_table< T >::insert(std::pair< std::string, T > item)
{
  try
  {
    size_t key = this->hash_function(item.first);

    node_t< T > *node = new node_t< T >;
    node->key = item.first;
    node->value = item.second;
    node->next = nullptr;

    if (this->empty(key))
    {
      this->arr_[key] = node;
    }
    else
    {
      node_t< T > *tmpNode = this->arr_[key];
      while (tmpNode->next != nullptr)
      {
        tmpNode = tmpNode->next;
      }
      tmpNode->next = node;
    }

    ++this->bucket_size_[key];
    ++this->count_;
  }
  catch (std::bad_alloc &)
  {
    throw std::overflow_error("Hash table is full");
  }
}

template< class T >
bool zagrivnyy::hash_table< T >::erase(std::string keyWord)
{
  bool erased = false;
  node_t< T > *tmpNode;
  size_t key = this->hash_function(keyWord);

  if (!this->empty(key))
  {
    if (this->arr_[key]->key == keyWord)
    {
      tmpNode = this->arr_[key];
      this->arr_[key] = this->arr_[key]->next;
      delete tmpNode;
      --this->count_;
      --this->bucket_size_[key];
      erased = true;
    }
    else
    {
      for (tmpNode = this->arr_[key]; tmpNode->next != nullptr; tmpNode = tmpNode->next)
      {
        if (tmpNode->next->key == keyWord)
        {
          node_t< T > *nodeToDelete = tmpNode->next;
          tmpNode->next = nodeToDelete->next;
          delete nodeToDelete;
          --this->count_;
          --this->bucket_size_[key];
          erased = true;
          break;
        }
      }
    }
  }

  return erased;
}

template< class T >
void zagrivnyy::hash_table< T >::clear()
{
  this->count_ = 0;
  for (size_t i = 0; i < this->base_size_; ++i)
  {
    while (!this->empty(i))
    {
      node_t< T > *tmp = this->arr_[i];
      this->arr_[i] = tmp->next;
      delete tmp;
    }
    this->bucket_size_[i] = 0;
  }
}

template< class T >
size_t zagrivnyy::hash_table< T >::hash_function(std::string key) const
{
  long h = 19937;

  for (unsigned i = 0; i < key.length(); ++i)
  {
    h = (h << 6) ^ (h >> 26) ^ key[i];
  }

  return abs(h % this->base_size_);
}

template< class T >
T &zagrivnyy::hash_table< T >::at(const std::string &keyWord) const
{
  auto it = this->find(keyWord);
  if (it == this->end())
  {
    throw std::out_of_range("Element not found");
  }

  return it->second;
}

template< class T >
typename zagrivnyy::hash_table< T >::iterator zagrivnyy::hash_table< T >::find(const std::string &keyWord)
{
  for (auto el : this->begin())
  {
    if (el.first == keyWord)
    {
      return this->begin();
    }
  }
  return nullptr;
}

template< class T >
bool zagrivnyy::hash_table< T >::empty(const size_t key)
{
  if (key < this->base_size_)
  {
    return this->arr_[key] == nullptr;
  }
  return true;
}

template< class T >
inline zagrivnyy::hash_table< T >::iterator::iterator(node_t< T > *otherIt)
{
  this->head = otherIt;
}

template< class T >
typename zagrivnyy::hash_table< T >::iterator &zagrivnyy::hash_table< T >::iterator::operator=(const iterator &other)
{
  this->head = other.head;
  return (*this);
}

template< class T >
bool zagrivnyy::hash_table< T >::iterator::operator==(const iterator &other) const
{
  return this->head == other.head;
}

template< class T >
bool zagrivnyy::hash_table< T >::iterator::operator!=(const iterator &other) const
{
  return this->head != other.head;
}

template< class T >
bool zagrivnyy::hash_table< T >::iterator::operator<(const iterator &other) const
{
  return this->head < other.head;
}

template< class T >
bool zagrivnyy::hash_table< T >::iterator::operator>(const iterator &other) const
{
  return other.head < this->head;
}

template< class T >
bool zagrivnyy::hash_table< T >::iterator::operator>=(const iterator &other) const
{
  return (!(this->head < other.head));
}

template< class T >
typename zagrivnyy::hash_table< T >::iterator zagrivnyy::hash_table< T >::iterator::operator+(size_t incr)
{
  node_t< T > *tmp = this->head;
  for (size_t i = 0; i < incr && tmp != nullptr; ++i)
  {
    tmp = tmp->next;
  }
  return tmp;
}

template< class T >
typename zagrivnyy::hash_table< T >::iterator zagrivnyy::hash_table< T >::iterator::operator+=(size_t incr)
{
  for (size_t i = 0; i < incr && this->head != nullptr; ++i)
  {
    this->head = this->head->next;
  }
  return this->head;
}

template< class T >
std::pair< std::string, T > *zagrivnyy::hash_table< T >::iterator::operator->() const
{
  return (&**this);
}

template< class T >
std::pair< std::string, T > zagrivnyy::hash_table< T >::iterator::operator*()
{
  if (this->head == nullptr)
  {
    return this->junk;
  }
  std::pair< std::string, T > &pair{this->head->key, this->head->value};
  return pair;
}

template< class T >
const std::pair< std::string, T > &zagrivnyy::hash_table< T >::iterator::operator*() const
{
  if (this->head == nullptr)
  {
    return this->junk;
  }
  return std::pair< std::string, T >{this->head->key, this->head->value};
}

template< class T >
T &zagrivnyy::hash_table< T >::iterator::operator[](size_t incr)
{
  if (this->head == nullptr || (*this + incr) == nullptr)
  {
    return this->junk;
  }
  return (*(*this + incr));
}

template< class T >
typename zagrivnyy::hash_table< T >::iterator zagrivnyy::hash_table< T >::iterator::operator++(int)
{
  node_t< T > *tmp = this->head;
  this->operator++();
  return tmp;
}

template< class T >
typename zagrivnyy::hash_table< T >::iterator &zagrivnyy::hash_table< T >::iterator::operator++()
{
  if (this->head != nullptr)
  {
    this->head = this->head->next;
  }
  return (*this);
}

template< class T >
bool zagrivnyy::hash_table< T >::iterator::operator<=(const iterator &other) const
{
  return (!(other.head < this->head));
}

#endif
