/**
 * @file DictionaryList.hpp
 * @brief Шаблон односвязного упорядоченного списка (словаря)
 * @version 0.1
 * @date Февраль 2024 г.
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DICTIONARY_LIST_HPP
#define DICTIONARY_LIST_HPP
#include <cstring>
#include <iostream>

namespace zagrivnyy
{
  /**
   * @brief Односвязный упорядоченный список
   *
   * Словарь хранит ключ и значение. Ключи не могут повторяться и хранятся строго в лексикографическом порядке. Значения
   * задаются пользовательским типом.
   *
   * @tparam T Тип хранимого значения в словаре
   */
  template< class T >
  class DictionaryList
  {
  private:
    /**
     * @brief Нода словаря
     *
     * Хранит в себе ключ, значение и ссылку на следующую ноду. Ключ и значение не могут быть пустыми.
     */
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

      friend std::ostream &operator<<(std::ostream &os, const node_t &src)
      {
        return os << src.key_ << ": " << src.value_;
      }
    };

  public:
    DictionaryList() = default;
    DictionaryList(std::initializer_list< node_t > l);
    ~DictionaryList();
    DictionaryList(const DictionaryList &src) = delete;
    DictionaryList(DictionaryList &&src);

    /**
     * @brief Возвращает размер словаря
     *
     * @return size_t Количество элементов в словаре
     */
    size_t size() const
    {
      return count_;
    }

    /**
     * @brief Возвращает первую ноду словаря
     *
     * @return node_t* Указатель на первый элемент словаря
     */
    node_t *start() const
    {
      return head_;
    }

    /**
     * @brief Возвращает последнюю ноду словаря
     *
     * @return node_t* Указатель на последний элемент словаря
     */
    node_t *end() const
    {
      return tail_;
    }

    /**
     * @brief Добавить ключ и значение в словарь
     *
     * Создает новую ноду используя переданные ключ и значение. Вызывает метод insertNode() для добавления созданной
     * ноды.
     *
     * @see DictionaryList::insertNode
     *
     * @param[in] key Ключ словаря, должен быть уникальным значением
     * @param[in] value Значение сопоставляемое ключу
     */
    void insert(const std::string &key, const T &value);

    /**
     * @brief Объединение переданного словаря с исходным
     *
     * @param src Словарь для объединения
     */
    void merge(DictionaryList &src);

    /**
     * @brief Удаление слов которые присутствуют в переданном словаре
     *
     * @param src Словарь слов для удаления
     */
    void deleteWords(DictionaryList &src);

    typedef node_t Node;     // Необходимо для работы friend функции
    template< T >
    friend DictionaryList< T > getIntersection(const DictionaryList< T > &first, const DictionaryList< T > &second);

    /**
     * @brief Удалить переданную ноду из словаря
     *
     * @throw std::invalid_argument В случае если передан нулевой указатель
     * @param[in] node Указатель на нужную ноду
     */
    void erase(const std::string &key);

    /**
     * @brief Поиск ноды по ключу
     *
     * @param key Ключ по которому осуществляется поиск
     * @return node_t* Указатель на найденную ноду
     */
    node_t *find(const std::string &key) const
    {
      node_t *current = head_;

      while (current && current->key_ != key)
      {
        current = current->next_;
      }

      return current;
    }

    /**
     * @brief Вывод слов из словаря в переданный поток вывода
     *
     * @param os Поток вывода
     */
    void print(std::ostream &os) const;

    DictionaryList &operator=(const DictionaryList &src) = delete;
    DictionaryList &operator=(DictionaryList &&src);

  private:
    size_t count_ = 0;           ///< Количество элементов в словаре
    node_t *head_ = nullptr;     ///< Указатель на первый элемент словаря
    node_t *tail_ = nullptr;     ///< Указатель на последний элемент словаря

    /**
     * @brief Вставляет ноду в список
     *
     * Добавляет ноду в нужное место учитывая лексикографическй порядок
     *
     * @note Если ключ уже используется, то ничего не произойдет
     *
     * @param[in] node Добавляемая нода
     */
    void insertNode(node_t *node);

    /**
     * @brief Удаляет ноду из словаря
     *
     * @param[in] node Удаляемая нода
     */
    void deleteNode(node_t *node);
  };

  template< class T >
  inline DictionaryList< T >::DictionaryList(std::initializer_list< node_t > l)
  {
    for (node_t node : l)
    {
      node_t *newNode = new node_t(node.key_, node.value_);
      insertNode(newNode);
    }
  }

  template< class T >
  inline DictionaryList< T >::~DictionaryList()
  {
    node_t *current = nullptr;
    node_t *next = head_;

    while (next)
    {
      current = next;
      next = next->next_;
      delete current;
    }
  }

  template< class T >
  inline DictionaryList< T >::DictionaryList(DictionaryList &&src)
  {
    head_ = src.head_;
    tail_ = src.tail_;
    count_ = src.count_;

    src.tail_ = nullptr;
    src.head_ = nullptr;
    src.count_ = 0;
  }

  template< class T >
  void DictionaryList< T >::insert(const std::string &key, const T &value)
  {
    node_t *newNode = new node_t(key, value);
    insertNode(newNode);
  }

  template< class T >
  void DictionaryList< T >::merge(DictionaryList &src)
  {
    node_t *current = nullptr;
    node_t *next = src.head_;
    while (next)
    {
      current = next;
      next = next->next_;

      insertNode(current);
    }

    src.head_ = nullptr;
    src.tail_ = nullptr;
  }

  template< class T >
  void DictionaryList< T >::deleteWords(DictionaryList &src)
  {
    node_t *current = nullptr;
    node_t *next = src.head_;

    while (next)
    {
      current = next;
      next = next->next_;

      erase(current->key_);
    }
  }

  template< class T >
  DictionaryList< T > getIntersection(const DictionaryList< T > &first, const DictionaryList< T > &second)
  {
    DictionaryList< T > newDict;

    typename DictionaryList< T >::Node *current = nullptr;
    typename DictionaryList< T >::Node *next = first.start();

    while (next)
    {
      current = next;
      next = next->next_;

      if (second.find(current->key_))
      {
        newDict.insert(current->key_, current->value_);
      }
    }

    return newDict;
  }

  template< class T >
  void DictionaryList< T >::erase(const std::string &key)
  {
    node_t *node = find(key);
    if (node == nullptr)
    {
      return;
    }

    deleteNode(node);
  }

  template< class T >
  inline void DictionaryList< T >::print(std::ostream &os) const
  {
    node_t *next = head_;
    node_t *current = nullptr;

    while (next)
    {
      current = next;
      next = next->next_;
      os << *current << "\n";
    }
  }

  template< class T >
  DictionaryList< T > &DictionaryList< T >::operator=(DictionaryList &&src)
  {
    head_ = src.head_;
    tail_ = src.tail_;
    count_ = src.count_;

    src.tail_ = nullptr;
    src.head_ = nullptr;
    src.count_ = 0;
    return *this;
  }

  template< class T >
  void DictionaryList< T >::insertNode(node_t *node)
  {
    if (head_ == nullptr)
    {
      head_ = node;
      tail_ = node;
      ++count_;
      return;
    }

    node_t *current = head_;
    node_t *previous = nullptr;

    while (current && current->key_ <= node->key_)
    {
      if (current->key_ == node->key_)
      {
        return;
      }

      previous = current;
      current = current->next_;
    }

    if (current == nullptr)
    {
      previous->next_ = node;
      tail_ = node;
      ++count_;
    }
    else if (previous)
    {
      node->next_ = previous->next_;
      previous->next_ = node;
      ++count_;
    }
    else
    {
      node->next_ = head_;
      head_ = node;
      ++count_;
    }
  }

  template< class T >
  void DictionaryList< T >::deleteNode(node_t *node)
  {
    node_t *current = head_;
    node_t *previous = nullptr;

    while (node && current)
    {
      if (node == head_)
      {
        head_ = node->next_;
        delete node;
        --count_;
      }
      else if (current == node)
      {
        previous->next_ = node->next_;
        delete node;
        --count_;
      }
      previous = current;
      current = current->next_;
    }
  }
}
#endif
