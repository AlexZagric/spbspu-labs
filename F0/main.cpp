#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Node
{
  std::vector< std::string > keys;     // ключи
  std::vector< Node * > children;      // ссылки на дочерние узлы
  bool isLeaf;
  std::map< std::string, std::set< int > > lines;     // список строк для каждого слова

  Node(bool leaf):
    isLeaf(leaf)
  {
  }
};

// Функция для добавления ключа в узел
void addKey(Node *node, const std::string &key, int lineNumber)
{
  node->lines[key].insert(lineNumber);
  if (find(node->keys.begin(), node->keys.end(), key) == node->keys.end())
  {
    node->keys.push_back(key);
    sort(node->keys.begin(), node->keys.end());
  }
}

// Функция для поиска узла для вставки
Node *findNode(Node *root, const std::string &key)
{
  if (root->isLeaf)
  {
    return root;
  }
  for (size_t i = 0; i < root->keys.size(); ++i)
  {
    if (key < root->keys[i])
    {
      return findNode(root->children[i], key);
    }
  }
  return findNode(root->children.back(), key);
}

// Функция для вставки ключа в дерево
void insert(Node *&root, const std::string &key, int lineNumber)
{
  Node *node = findNode(root, key);
  addKey(node, key, lineNumber);
}

// Функция для поиска ключа в дереве и возврата номеров строк
std::set< int > search(Node *root, const std::string &key)
{
  if (root == nullptr)
  {
    return {};
  }
  for (const auto &k : root->keys)
  {
    if (k == key)
    {
      return root->lines[key];
    }
  }
  for (auto child : root->children)
  {
    auto result = search(child, key);
    if (!result.empty())
    {
      return result;
    }
  }
  return {};
}

// Функция для удаления ключа из дерева
void deleteKey(Node *&root, const std::string &key)
{
  if (root == nullptr)
  {
    return;
  }
  auto it = find(root->keys.begin(), root->keys.end(), key);
  if (it != root->keys.end())
  {
    root->keys.erase(it);
    root->lines.erase(key);
    if (root->keys.empty() && root->children.empty())
    {
      delete root;
      root = nullptr;
    }
  }
  else
  {
    for (auto &child : root->children)
    {
      deleteKey(child, key);
    }
  }
}

// Функция для рекурсивного сбора всех ключей из дерева
void collectKeys(Node *node, std::map< std::string, std::set< int > > &sortedWords)
{
  if (node == nullptr)
  {
    return;
  }
  for (const auto &key : node->keys)
  {
    sortedWords[key].insert(node->lines[key].begin(), node->lines[key].end());
  }
  for (auto child : node->children)
  {
    collectKeys(child, sortedWords);
  }
}

// Функция для печати словаря в алфавитном порядке
void printAlphabetical(Node *root)
{
  std::map< std::string, std::set< int > > sortedWords;
  collectKeys(root, sortedWords);
  for (const auto &entry : sortedWords)
  {
    std::cout << entry.first << ": ";
    for (const auto &line : entry.second)
    {
      std::cout << line << " ";
    }
    std::cout << std::endl;
  }
}

// Функция для преобразования строки в нижний регистр
std::string toLowerCase(const std::string &str)
{
  std::string lowerStr;
  for (char c : str)
  {
    lowerStr += tolower(c);
  }
  return lowerStr;
}

// Функция для проверки, содержит ли слово только буквы
bool containsOnlyLetters(const std::string &word)
{
  for (char c : word)
  {
    if (!isalpha(c))
    {
      return false;
    }
  }
  return true;
}

// Функция для удаления знаков препинания из строки
std::string removePunctuation(const std::string &str)
{
  std::string result;
  for (char c : str)
  {
    if (!ispunct(c))
    {
      result += c;
    }
  }
  return result;
}

int main()
{
  // Инициализация корня дерева
  Node *root = new Node(true);
  setlocale(LC_ALL, "Russian");

  // Чтение текста из файла
  std::ifstream inputFile("text.txt");
  if (!inputFile.is_open())
  {
    std::cerr << "Ошибка открытия файла." << std::endl;
    return 1;
  }

  std::string line;
  int lineNumber = 1;

  // Считывание строк и добавление слов в дерево
  while (getline(inputFile, line))
  {
    std::cout << lineNumber << ": " << line << std::endl;
    std::stringstream ss(removePunctuation(line));     // Удаляем знаки препинания перед обработкой
    std::string word;
    while (ss >> word)
    {
      // Преобразуем слово в нижний регистр и удаляем точку в конце перед вставкой
      std::string processedWord = toLowerCase(word);
      bool validWord = containsOnlyLetters(processedWord);

      if (validWord)
      {
        insert(root, processedWord, lineNumber);
      }
      else
      {
        std::cout << "Слово '" << word << "' содержит недопустимые символы и было пропущено." << std::endl;
      }
    }
    lineNumber++;
  }

  inputFile.close();

  // Печать таблицы перекрестных ссылок в алфавитном порядке
  std::cout << "\nТаблица перекрестных ссылок:" << std::endl;
  printAlphabetical(root);

  // Примеры использования операций INSERT, SEARCH, DELETE, PRINT
  std::cout << "\nОперации со словарем:" << std::endl;

  std::string command;
  while (true)
  {
    std::cout << "Введите команду (INSERT, SEARCH, DELETE, PRINT, EXIT): ";
    std::cin >> command;

    if (command == "INSERT")
    {
      std::string word;
      int lineNum;
      while (true)
      {
        std::cout << "Введите слово: ";
        std::cin >> word;
        bool validWord = containsOnlyLetters(word);

        if (validWord)
        {
          break;
        }
        else
        {
          std::cout << "Ошибка: введите слово корректно." << std::endl;
        }
      }
      std::cout << "Введите номер строки: ";
      std::cin >> lineNum;
      insert(root, toLowerCase(removePunctuation(word)), lineNum);
      std::cout << "Слово '" << word << "' добавлено на строку " << lineNum << "." << std::endl;
    }
    else if (command == "SEARCH")
    {
      std::string word;
      std::cout << "Введите слово для поиска: ";
      std::cin >> word;
      auto lines = search(root, toLowerCase(removePunctuation(word)));
      if (!lines.empty())
      {
        std::cout << "Слово '" << word << "' найдено в строках: ";
        for (const auto &line : lines)
        {
          std::cout << line << " ";
        }
        std::cout << std::endl;
      }
      else
      {
        std::cout << "Слово '" << word << "' не найдено в дереве." << std::endl;
      }
    }
    else if (command == "DELETE")
    {
      std::string word;
      while (true)
      {
        std::cout << "Введите слово для удаления: ";
        std::cin >> word;
        bool validWord = true;
        for (char c : word)
        {
          if (!isalpha(c))
          {
            validWord = false;
            break;
          }
        }
        if (validWord)
        {
          break;
        }
        else
        {
          std::cout << "Ошибка: введите слово корректно." << std::endl;
        }
      }
      deleteKey(root, toLowerCase(removePunctuation(word)));
      std::cout << "Слово '" << word << "' удалено из дерева." << std::endl;
    }
    else if (command == "PRINT")
    {
      std::cout << "\nТекущий словарь в алфавитном порядке:" << std::endl;
      printAlphabetical(root);
    }
    else if (command == "EXIT")
    {
      break;
    }
    else
    {
      std::cout << "Неизвестная команда." << std::endl;
    }
  }

  return 0;
}
