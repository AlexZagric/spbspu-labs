#ifndef DICTIONARY_LIST_HPP
#define DICTIONARY_LIST_HPP
#include <iostream>

namespace zagrivnyy
{
  template< class T >
  class dictionaryList
  {
  public:
    dictionaryList() = default;
    ~dictionaryList();
    dictionaryList(const dictionaryList &src);

    size_t count()
    {
      return count_;
    }

    node_t headItem() const;

    void insert(const std::string &key, const T &value)
    {
      node_t *newNode = new node_t(key, value);
      insertNode(newNode);
    };

    void pop(const std::string &key);
    T get(const std::string &key) const;

  private:
    struct node_t
    {
      std::string key_ = "";
      T value_;
      node_t *next_ = nullptr;

      node_t(std::string key, T value, node_t *next = nullptr): key_(key), value_(value), next_(next) {}
    };

    size_t count_ = 0;
    node_t *head_ = nullptr;
    node_t *tail_ = nullptr;

    void insertNode(node_t *head);
    void deleteNode(node_t *node);
    node_t *searchNode(const std::string &key);
  }
}     // namespace zagrivnyy
#endif
