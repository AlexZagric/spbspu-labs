#ifndef WRONGSTACKSIZE_HPP
#define WRONGSTACKSIZE_HPP
#include <exception>

namespace zagrivnyy
{
  class WrongStackSize: public std::exception
  {
  public:
    WrongStackSize():
      reason("Wrong Stack Size")
    {
    }

    const char *what() const noexcept override
    {
      return reason;
    };

  private:
    const char *reason;
  };
}     // namespace zagrivnyy
#endif
