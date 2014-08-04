//          Copyright Boston University SESA Group 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <cstdlib>
#include <ctime>

#include <ebbrt/Acpi.h>
#include <ebbrt/Debug.h>

#include "../CmdLineArgs.h"
#include "../FileSystem.h"
#include "../StaticEbbIds.h"

ebbrt::EbbRef<FileSystem> node_fs_ebb;

extern "C" int main(int argc, char **argv);

void AppMain() {
  putenv(const_cast<char *>("TZ=EST5EDT4,M3.2.0,M11.1.0"));
#ifndef BM_ONLY
  node_fs_ebb = ebbrt::EbbRef<FileSystem>(kFileSystemId);
  auto cmdlineargs = ebbrt::EbbRef<CmdLineArgs>(kCmdLineArgsId);
  auto cmd_argc = cmdlineargs->argc();
  auto cmd_argv = cmdlineargs->argv();
  auto i = main(cmd_argc, cmd_argv);
#else
  const char *argv[] = { "node" };
  auto i = main(1, const_cast<char **>(argv));
#endif
  ebbrt::kprintf("Return Code: %d\n", i);
  ebbrt::acpi::PowerOff();
}
