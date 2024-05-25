#include <iostream>

#include "BinarySearchTree.hpp"

int main()
{
  zagrivnyy::BinarySearchTree< int > *tree = new zagrivnyy::BinarySearchTree< int >();
  tree->output(std::cout);
  int val = 0;
  while (val != -1)
  {
    std::cin >> val;
    tree->insertKey(val);
  }

  val = 0;

  while (val != -1)
  {
    std::cin >> val;
    tree->deleteKey(val);
    std::cout << '\n';
    tree->output(std::cout);
  }
}
