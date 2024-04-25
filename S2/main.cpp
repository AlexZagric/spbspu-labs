#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include "stackArray.hpp"

bool checkBalanceBrackets(const std::string &text, const int maxDeep);

int main()
{
  std::string input = "";
  int maxDeep = 0;

  while (!std::cin.eof())
  {
    std::cout << "Enter max deep of brackets & text to check: ";
    std::cin >> maxDeep >> input;

    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      continue;
    }

    try
    {
      std::cout << std::boolalpha << checkBalanceBrackets(input, maxDeep) << '\n';
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  return 0;
}

bool checkBalanceBrackets(const std::string &text, const int maxDeep)
{
  zagrivnyy::StackArray< char > stack;
  for (const char c : text)
  {
    if (stack.size() > maxDeep)
    {
      return false;
    }

    switch (c)
    {
    case '[':
      stack.push(']');
      break;
    case '(':
      stack.push(')');
      break;
    case '{':
      stack.push('}');
      break;

    case ']':
    case ')':
    case '}':
      if (stack.isEmpty() || stack.pop() != c)
      {
        return false;
      }
      break;
    }
  }
  return stack.isEmpty();
}
