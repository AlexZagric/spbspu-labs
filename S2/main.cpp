#include <iomanip>
#include <iostream>
#include <string>

#include "stackArray.hpp"

bool checkBalanceBrackets(const std::string &text, const int maxDeep);

int main()
{
  std::string input = "";
  int maxDeep = 0;
  std::cout << "Enter max deep of brackets & text to check: ";
  std::cin >> maxDeep >> input;

  std::cout << std::boolalpha << checkBalanceBrackets(input, maxDeep);

  return 0;
}

bool checkBalanceBrackets(const std::string &text, const int maxDeep)
{
  zagrivnyy::StackArray< char > stack;
  for (const char c : text)
  {
    if (stack.size() == maxDeep)
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

    return stack.isEmpty();
  }
}
