#include <iostream>

#include "DictionaryList.hpp"

int main()
{
  zagrivnyy::DictionaryList< int > priceList {
    {    "Apple", 15},
    {"Pineapple", 25},
    {   "Banana", 90},
    { "Cucumber",  8},
    {"Pineapple", 85},
    {   "Coffee", 57},
    {     "Cake", 43},
    {      "Tea", 13},
  };

  zagrivnyy::DictionaryList< int > priceList_new {
    {    "Apple", 20},
    {"Pineapple", 60},
    {   "Banana", 88},
    {   "Carrot",  2},
  };

  zagrivnyy::DictionaryList< int > positionsToDelete {
    {     "Cake", 0},
    {"Pineapple", 0},
    {   "Orange", 0}
  };

  std::cout << "+++++++++++++ priceList +++++++++++++\n";
  priceList.print(std::cout);
  std::cout << "+++++++++++ priceList_new +++++++++++\n";
  priceList_new.print(std::cout);
  std::cout << "++++++ priceLists after merge ++++++\n";
  priceList_new.merge(priceList);
  priceList_new.print(std::cout);
  std::cout << "--\n";
  priceList.print(std::cout);
  std::cout << "+++++ priceList_new after erase +++++\n";
  priceList_new.erase("Apple");
  priceList_new.erase("Orange");
  priceList_new.print(std::cout);
  std::cout << "++ priceList_new after deleteWords ++\n";
  priceList_new.deleteWords(positionsToDelete);
  priceList_new.print(std::cout);

  // zagrivnyy::DictionaryList< int > intersectionList;
  // intersectionList = zagrivnyy::getIntersection< int >(priceList, priceList_new);
}
