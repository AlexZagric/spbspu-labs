#ifndef DICTIONARY_LIST_HPP
#define DICTIONARY_LIST_HPP
#include <cstring>
#include <iostream>

namespace zagrivnyy
{
  template< class T >
  class dictionaryList
  {
  private:
    struct node_t
    {
      std::string key_ = "";
      T value_;
      node_t *next_ = nullptr;

      node_t(std::string key, T value, node_t *next = nullptr):
        key_(key),
        value_(value),
        next_(next)
      {
      }
    };

  public:
    dictionaryList() = default;
    ~dictionaryList();
    dictionaryList(const dictionaryList &src) = delete;

    size_t count()
    {
      return count_;
    }

    node_t *start() const
    {
      return head_;
    }

    node_t *end() const
    {
      return tail_;
    }

    void insert(const std::string &key, const T &value);
    void erase(const node_t *node);
    bool find(const std::string &key) const;

  private:
    size_t count_ = 0;
    node_t *head_ = nullptr;
    node_t *tail_ = nullptr;

    void insertNode(node_t *node);
    void deleteNode(node_t *node);
    node_t *findNode(const std::string &key);
  };

  template< class T >
  dictionaryList< T >::~dictionaryList()
  {
    node_t *current = nullptr;
    node_t *next = head_;

    while (next != nullptr)
    {
      current = next;
      next = next->next_;
      delete current;
    }
  }

  template< class T >
  void dictionaryList< T >::insert(const std::string &key, const T &value)
  {
    node_t *newNode = new node_t(key, value);
    insertNode(newNode);
    count_++;
  }

  template< class T >
  void dictionaryList< T >::erase(const node_t *node)
  {
    if (node == nullptr)
    {
      throw std::invalid_argument();
    }

    deleteNode(node);
    count_--;
  }

  template< class T >
  bool dictionaryList< T >::find(const std::string &key) const
  {
    return (findNode(key) != nullptr);
  }

  template< class T >
  void dictionaryList< T >::insertNode(node_t *node)
  {
    if (head_ == nullptr)
    {
      head_ = node;
      tail_ = node;
      return;
    }

    node_t *current = head_;

    while (current != nullptr)
    {
      if (current->key_ > node->key_)
      {
        if (current->next_ != nullptr)
        {
          node->next_ = current->next_;
          current->next_ = node;
        }
        else
        {
          current->next_ = node;
          tail_ = node;
        }
        break;
      }

      current = current->next_;
    }
  }

  template< class T >
  void dictionaryList< T >::deleteNode(node_t *node)
  {
    node_t *current = head_;
    node_t *previous = nullptr;

    do
    {
      if (node == head_)
      {
        delete node;
      }
      else if (current == node)
      {
        previous->next_ = node->next_;
        delete node;
      }
      previous = current;
      current = current->next_;
    } while (current != node);
  }

  template< class T >
  typename dictionaryList< T >::node_t dictionaryList< T >::*findNode(const std::string &key)
  {
    typename dictionaryList< T >::node_t *current = dictionaryList< T >::head_;

    while (current != nullptr && current->key_ != key)
    {
      current = current->next_;
    }

    return current;
  }
}     // namespace zagrivnyy
#endif
