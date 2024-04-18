#ifndef STACKUNDERFLOW_HPP
#define STACKUNDERFLOW_HPP
#include <exception>

namespace zagrivnyy
{
  class StackUnderflow: public std::exception
  {
  public:
    StackUnderflow():
      reason("Stack Underflow")
    {
    }

    const char *what() const noexcept override
    {
      return reason;
    };

  private:
    const char *reason;
  };
}
#endif
