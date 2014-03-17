//          Copyright Boston University SESA Group 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <ctime>

#include <ebbrt/Debug.h>

extern "C" int main(int argc, char **argv);

void AppMain() {
  putenv(const_cast<char *>("TZ=EST5EDT4,M3.2.0,M11.1.0"));
  const char *argv[] = { "node" };
  auto i = main(1, const_cast<char **>(argv));
  ebbrt::kprintf("Return Code: %d\n", i);
}
