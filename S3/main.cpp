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
  std::cout << '\n';
  std::cout << "inorderWalk: ";
  tree->inorderWalk();
  std::cout << '\n';
  std::cout << "walkByLevels: ";
  tree->walkByLevels();
  std::cout << '\n';

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
  zagrivnyy::BinarySearchTree< char > *tree3 = new zagrivnyy::BinarySearchTree< char >();
  tree3->insertKey('f');
  tree3->insertKey('e');
  tree3->insertKey('a');
  tree3->insertKey('c');
  tree3->insertKey('d');
  tree3->insertKey('g');
  tree3->insertKey('b');
  std::cout << std::boolalpha << "isSimilar: " << tree2->isSimilar(*tree3)
            << " isIdentical: " << tree2->isIdentical(*tree3) << "\n";
  tree3->deleteKey('c');
  std::cout << std::boolalpha << "isSimilar: " << tree2->isSimilar(*tree3)
            << " isIdentical: " << tree2->isIdentical(*tree3) << "\n";
}
