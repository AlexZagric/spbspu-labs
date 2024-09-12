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

  std::cout << "inorderWalkIterative: ";
  tree->inorderWalkIterative();

  val = 0;

  while (val != -1)
  {
    std::cin >> val;
    tree->deleteKey(val);
    std::cout << '\n';
    tree->output(std::cout);
  }

  zagrivnyy::BinarySearchTree< char > *tree2 = new zagrivnyy::BinarySearchTree< char >();
  tree2->insertKey('f');
  tree2->insertKey('e');
  tree2->insertKey('a');
  tree2->insertKey('c');
  tree2->insertKey('d');
  tree2->insertKey('g');
  tree2->insertKey('b');
  tree2->output(std::cout);
  std::cout << "size: " << tree2->size() << " height: " << tree2->height() << "\n\n";
}
