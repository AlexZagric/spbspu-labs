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

      node_t(std::string key, T value, node_t *next = nullptr): key_(key), value_(value), next_(next) {}
    };

  public:
    dictionaryList() = default;

    ~dictionaryList()
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

    dictionaryList(const dictionaryList &src);

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

    void insert(const std::string &key, const T &value)
    {
      node_t *newNode = new node_t(key, value);
      insertNode(newNode);
      count_++;
    }

    void erase(const node_t *node)
    {
      if (node == nullptr)
      {
        throw std::invalid_argument();
      }

      deleteNode(node);
      count_--;
    }

    bool find(const std::string &key) const
    {
      return (findNode(key) != nullptr);
    }

  private:
    size_t count_ = 0;
    node_t *head_ = nullptr;
    node_t *tail_ = nullptr;

    void insertNode(node_t *node)
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

    void deleteNode(node_t *node);

    node_t *findNod(const std::string &key)
    {
      node_t *current = head_;

      while (current != nullptr && current->key_ != key)
      {
        current = current->next_;
      }

      return current;
    }
  };
}     // namespace zagrivnyy
#endif
