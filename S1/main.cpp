#include <iostream>

#include "DictionaryList.hpp"

int main()
{
  zagrivnyy::DictionaryList< int > priceList{
    {    "Apple", 15},
    {"Pineapple", 25},
    {   "Banana", 90},
    { "Cucumber",  8},
    {"Pineapple", 85},
    {   "Coffee", 57},
  };

  zagrivnyy::DictionaryList< int > priceList_new{
    {    "Apple", 20},
    {"Pineapple", 60},
    {   "Banana", 88},
    {   "Carrot",  2},
  };

  zagrivnyy::DictionaryList< int > positionsToDelete{
    {     "Cake", 0},
    {"Pineapple", 0},
    {   "Orange", 0},
  };

  priceList.insert("Tea", 13);
  priceList.insert("Cake", 43);
  std::cout << "+++++++++++++ priceList +++++++++++++\n";
  priceList.print(std::cout);
  std::cout << "+++++++++++ priceList_new +++++++++++\n";
  priceList_new.print(std::cout);
  std::cout << "++++++ priceLists after merge (added 'Carrot: 2') ++++++\n";
  priceList_new.merge(priceList);
  priceList_new.print(std::cout);
  std::cout << "--\n";
  priceList.print(std::cout);
  std::cout << "+++++ priceList_new after erase (removed 'Apple') +++++\n";
  priceList_new.erase("Apple");
  priceList_new.erase("Orange");
  priceList_new.print(std::cout);
  std::cout << "++ priceList_new after deleteWords (removed 'Cake' & 'Pineapple')++\n";
  priceList_new.deleteWords(positionsToDelete);
  priceList_new.print(std::cout);

  std::cout << "+++++++++++++ intersectionList +++++++++++++\n";
  zagrivnyy::DictionaryList< char > intersectionList;
  zagrivnyy::DictionaryList< char > listA = {
    {"A", 'a'},
    {"B", 'b'},
    {"C", 'q'},
    {"Z", 'z'}
  };
  zagrivnyy::DictionaryList< char > listB = {
    {"B", 'a'},
    {"Z", 'f'},
    {"Q", 'q'},
  };
  intersectionList = zagrivnyy::getIntersection< char >(listA, listB);
  std::cout << "-- listA --\n";
  listA.print(std::cout);
  std::cout << "-- listB --\n";
  listB.print(std::cout);
  std::cout << "-- intersection --\n";
  intersectionList.print(std::cout);
}
