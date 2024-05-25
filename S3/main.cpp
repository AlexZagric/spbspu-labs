#include <iostream>

#include "BinarySearchTree.hpp"

int main()
{
  zagrivnyy::BinarySearchTree< int > *tree = new zagrivnyy::BinarySearchTree< int >();
  std::cout << tree->insertKey(8) << '\n';
  std::cout << tree->insertKey(8) << '\n';
  std::cout << tree->searchKey(8) << '\n';
  std::cout << tree->insertKey(5) << '\n';
  std::cout << tree->insertKey(9) << '\n';
  std::cout << tree->insertKey(2) << '\n';
  std::cout << tree->insertKey(7) << '\n';
  std::cout << tree->insertKey(10) << '\n';
  std::cout << tree->insertKey(16) << '\n';
  std::cout << tree->insertKey(6) << '\n';
  std::cout << tree->searchKey(5) << '\n';
  tree->output(std::cout);
  std::cout << tree->deleteKey(5) << '\n';
  std::cout << tree->searchKey(5) << '\n';
  tree->output(std::cout);
}
