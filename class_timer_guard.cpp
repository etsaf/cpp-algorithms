// can be used to find how much time parts of the code take to execute

#include <iostream>
#include <chrono>
#include <string>
#include <string_view>

class TimerGuard {
private:
    using chrono_ = std::chrono::high_resolution_clock;
    std::chrono::time_point<chrono_> start;
    std::string Message;
    std::ostream& Out;

public:
    TimerGuard(std::string_view message = "", std::ostream& out = std::cout)
    : start(chrono_::now())
    , Message(message)
    , Out(out) {}

    ~TimerGuard() {
        std::chrono::duration<double> diff = chrono_::now() - start;
        Out << Message << " " << diff.count() << '\n';
    }
};


/* Works somewhat like this:
#include "some_long_stuff.h"

#include <iostream>
#include <chrono>

void SomeFunc() {
  {
    TimerGuard timer("FirstLongFunction elapsed: ", std::cerr);
    FirstLongFunction();
  }

  {
    TimerGuard timer("SecondLongFunction elapsed: ", std::cerr);
    SecondLongFunction();
  }

  {
    TimerGuard timer("ThirdLongFunction elapsed: ", std::cerr);
    ThirdLongFunction();
  }
}

int main() {
  SomeFunc();
  return 0;
}
*/