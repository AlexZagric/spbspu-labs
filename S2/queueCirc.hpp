#ifndef QUEUECIRC_HPP
#define QUEUECIRC_HPP
#include <iostream>

#include "queue.hpp"
#include "queueExceptions.hpp"

namespace zagrivnyy
{
  template< class T >
  class QueueCirc: public Queue< T >
  {
  public:
    QueueCirc(const int size = 100);
    ~QueueCirc() override;

    void enQueue(const T &e) override;
    T deQueue() override;
    bool isEmpty() override;

    friend std::ostream &operator<<(std::ostream &out, const QueueCirc &src)
    {
      int i = 0;
      for (i = src.front_; i != src.rear_; i = (i + 1) % src.size_)
      {
        out << i << " " << src.array_[i] << '\n';
      }
      out << i << " " << src.array_[i] << '\n';

      return out;
    };

  private:
    T *array_ = nullptr;
    int front_ = -1;
    int rear_ = -1;
    int size_ = 0;
  };

  template< class T >
  QueueCirc< T >::QueueCirc(const int size)
  {
    try
    {
      array_ = new T[size_ = size];
    }
    catch (...)
    {
      throw WrongQueueSize();
    }

    front_ = -1;
    rear_ = -1;
  }

  template< class T >
  QueueCirc< T >::~QueueCirc()
  {
    delete[] array_;
  }

  template< class T >
  void QueueCirc< T >::enQueue(const T &e)
  {
    if (front_ == (rear_ + 1) % size_)
    {
      throw QueueOverflow();
    }

    if (front_ == -1)
    {
      front_ = 0;
    }
    rear_ = (rear_ + 1) % size_;
    array_[rear_] = e;
  }

  template< class T >
  T QueueCirc< T >::deQueue()
  {
    if (isEmpty())
    {
      throw QueueUnderflow();
    }

    int el = array_[front_];
    if (front_ == rear_)
    {
      front_ = -1;
      rear_ = -1;
    }
    else
    {
      front_ = (front_ + 1) % size_;
    }

    return el;
  }

  template< class T >
  bool QueueCirc< T >::isEmpty()
  {
    return front_ == -1;
  }
}
#endif
