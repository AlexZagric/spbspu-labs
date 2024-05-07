#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <iostream>

namespace zagrivnyy
{
  template< class T >
  class BinarySearchTree
  {
  private:
    struct node_t
    {
      T key_;
      node_t *left_;
      node_t *right_;

      node_t(T key, node_t *left = nullptr, node_t *right = nullptr):
        key_(key),
        left_(left),
        right_(right)
      {
      }
    };

  public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &) = delete;
    BinarySearchTree(BinarySearchTree &&src) noexcept;
    virtual ~BinarySearchTree();

    BinarySearchTree &operator=(const BinarySearchTree &) = delete;
    BinarySearchTree &operator=(BinarySearchTree &&src) noexcept;

    bool searchKey(const T &key) const;
    bool insertKey(const T &key);
    bool deleteKey(const T &key);

    void output(std::ostream &out) const;

    int size() const;
    int height() const;

    void inorderWalkIterative() const;
    void inorderWalk() const;
    void walkByLevels() const;

    bool isSimilar(const BinarySearchTree &other) const;
    bool isIdentical(const BinarySearchTree &other) const;

  private:
    node_t *root_;

    node_t *findNode(const T &key) const;

    void output(std::ostream &out, node_t *root) const;

    int getSize(const node_t *node) const;
    int getHeight(const node_t *node) const;

    void inorderWalk(node_t *node) const;
  };

  template< class T >
  BinarySearchTree< T >::BinarySearchTree()
  {
    root_ = nullptr;
  }

  template< class T >
  BinarySearchTree< T >::BinarySearchTree(BinarySearchTree &&src) noexcept
  {
    root_ = std::move(src.root_);
  }

  template< class T >
  BinarySearchTree< T >::~BinarySearchTree()
  {
    // TODO: make destructor
  }

  template< class T >
  BinarySearchTree< T > &BinarySearchTree< T >::operator=(BinarySearchTree &&src) noexcept
  {
    root_ = std::move(src.root_);
    return *this;
  }

  template< class T >
  bool BinarySearchTree< T >::searchKey(const T &key) const
  {
    node_t *current = root_;

    while (current)
    {
      if (key < current->key_)
      {
        current = current->left_;
      }
      else if (key > current->key_)
      {
        current = current->right_;
      }
      else
      {
        break;
      }
    }

    return current != nullptr;
  }

  template< class T >
  bool BinarySearchTree< T >::insertKey(const T &key)
  {
    node_t *curent = findNode(key);

    if (curent)
    {
      return false;
    }

    // TODO: Complete insert keys
  }
}
#endif
