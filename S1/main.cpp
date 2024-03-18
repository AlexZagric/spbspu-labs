#include <iostream>

#include "DictionaryList.hpp"

int main()
{
  zagrivnyy::DictionaryList< int > priceList {
    {    "Apple", 15},
    {"Pineapple", 25},
    {   "Banana", 90},
    { "Cucumber",  8},
    {"Pineapple", 25},
  };

  zagrivnyy::DictionaryList< int > priceList_new {
    {    "Apple", 20},
    {"Pineapple", 60},
    {   "Banana", 88},
    {   "Carrot",  2},
  };

  priceList.print(std::cout);
  std::cout << "++++++++++++++\n";
  priceList_new.print(std::cout);
  priceList_new.merge(priceList);
  std::cout << "++++++++++++++\n";
  priceList_new.print(std::cout);
}
