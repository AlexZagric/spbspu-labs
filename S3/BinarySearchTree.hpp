#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP
#include <iostream>
#include <queue>
#include <stack>
#include <string>

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

      node_t &operator=(node_t &&src) noexcept
      {
        this->key_ = std::move(src.key_);
        this->left_ = std::move(src.left_);
        this->right_ = std::move(src.right_);

        return *this;
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

    node_t *findNode(const T &key) const
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
      return current;
    };

    void output(std::ostream &out, node_t *node, const std::string &prefix_r = "", const std::string &prefix_c = "",
      const std::string &prefix_l = "") const;

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
    return findNode(key) != nullptr;
  }

  template< class T >
  bool BinarySearchTree< T >::insertKey(const T &key)
  {
    if (!root_)
    {
      root_ = new node_t(key);
      return true;
    }

    node_t *current = root_;
    while (current)
    {
      if (current->key_ < key)
      {
        if (!(current->right_))
        {
          current->right_ = new node_t(key);
          return true;
        }
        current = current->right_;
      }
      else if (current->key_ > key)
      {
        if (!(current->left_))
        {
          current->left_ = new node_t(key);
          return true;
        }
        current = current->left_;
      }
      else
      {
        return false;
      }
    }
    return false;
  }

  template< class T >
  bool BinarySearchTree< T >::deleteKey(const T &key)
  {
    node_t *node = findNode(key);

    if (!node)
    {
      return false;
    }

    if (!(node->right_) && !(node->left_))
    {
      delete node;
      root_ = nullptr;
      return true;
    }

    if (!(node->right_))
    {
      *node = std::move(*node->left_);
    }
    else
    {
      node_t *child = node->right_;
      if (!(child->left_))
      {
        child->left_ = node->left_;
        *node = std::move(*child);
      }
      else
      {
        node_t *min = child->left_;
        node_t *prev = child;
        while (min->left_)
        {
          prev = min;
          min = min->left_;
        }

        node->key_ = min->key_;

        if (min->right_)
        {
          *min = std::move(*min->right_);
        }
        else
        {
          prev->left_ = nullptr;
          delete min;
        }
      }
    }

    return true;
  }

  template< class T >
  void BinarySearchTree< T >::output(std::ostream &out) const
  {
    return output(out, root_);
  }

  template< class T >
  int BinarySearchTree< T >::size() const
  {
    return getSize(this->root_);
  }

  template< class T >
  inline int BinarySearchTree< T >::height() const
  {
    return getHeight(this->root_);
  }

  template< class T >
  inline void BinarySearchTree< T >::inorderWalkIterative() const
  {
    if (this->root_)
    {
      std::stack< node_t * > s;
      node_t *current = this->root_;

      while (!s.empty() || current != nullptr)
      {
        if (current != nullptr)
        {
          s.push(current);
          current = current->left_;
        }
        else
        {
          current = s.top();
          s.pop();
          std::cout << current->key_ << " ";
          current = current->right_;
        }
      }
    }
    else
    {
      std::cout << "tree is empty\n";
    }
  }

  template< class T >
  inline void BinarySearchTree< T >::inorderWalk() const
  {
    inorderWalk(this->root_);
  }

  template< class T >
  inline void BinarySearchTree< T >::walkByLevels() const
  {
    if (this->root_)
    {
      std::queue< node_t * > q;
      node_t *temp = nullptr;

      q.push(this->root_);

      while (!q.empty())
      {
        temp = q.front();
        q.pop();
        std::cout << temp->key_ << " ";

        if (temp->left_)
        {
          q.push(temp->left_);
        }
        if (temp->right_)
        {
          q.push(temp->right_);
        }
      }
    }
    else
    {
      std::cout << "tree is empty\n";
    }
  }

  template< class T >
  void BinarySearchTree< T >::output(std::ostream &out, node_t *node, const std::string &prefix_r,
    const std::string &prefix_c, const std::string &prefix_l) const
  {
    if (!node)
    {
      return;
    }

    if (node->right_)
    {
      output(out, node->right_, prefix_r + "   ", prefix_r + "|--", prefix_r + "|  ");
    }

    out << prefix_c << node->key_ << '\n';

    if (node->left_)
    {
      output(out, node->left_, prefix_l + "|  ", prefix_l + "|--", prefix_l + "   ");
    }
  }

  template< class T >
  int BinarySearchTree< T >::getSize(const node_t *node) const
  {
    if (!node)
    {
      return 0;
    }

    return (1 + getSize(node->left_) + getSize(node->right_));
  }

  template< class T >
  inline int BinarySearchTree< T >::getHeight(const node_t *node) const
  {
    if (!node)
    {
      return 0;
    }

    return (1 + std::max(getHeight(node->left_), getHeight(node->right_)));
  }

  template< class T >
  inline void BinarySearchTree< T >::inorderWalk(node_t *node) const
  {
    if (node)
    {
      inorderWalk(node->left_);
      std::cout << node->key_ << " ";
      inorderWalk(node->right_);
    }
  }
}
#endif
