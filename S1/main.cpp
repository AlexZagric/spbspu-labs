#include <iostream>

#include "dictionaryList.hpp"

int main()
{
  zagrivnyy::dictionaryList< int > priceList {
    {    "Apple", 15},
    {"Pineapple", 25},
    {   "Banana", 90},
    { "Cucumber",  8},
    {"Pineapple", 25},
  };

  priceList.print(std::cout);
}
