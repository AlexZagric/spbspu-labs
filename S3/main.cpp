#include <iostream>

#include "BinarySearchTree.hpp"

int main()
{
  zagrivnyy::BinarySearchTree< int > *tree = new zagrivnyy::BinarySearchTree< int >();
  std::cout << tree->insertKey(11) << '\n';
  std::cout << tree->insertKey(11) << '\n';
  std::cout << tree->searchKey(11) << '\n';
}
