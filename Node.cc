//          Copyright Boston University SESA Group 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <signal.h>

#include <boost/filesystem.hpp>

#include <ebbrt/Context.h>
#include <ebbrt/ContextActivation.h>
#include <ebbrt/GlobalIdMap.h>
#include <ebbrt/NodeAllocator.h>
#include <ebbrt/Runtime.h>

#include <ebbrt-cmdline/CmdLineArgs.h>
#include <ebbrt-filesystem/FileSystem.h>

enum : ebbrt::EbbId {
  kCmdLineArgsId = ebbrt::kFirstStaticUserId,
  kFileSystemId
};

int main(int argc, char **argv) {
  auto bindir = boost::filesystem::system_complete(argv[0]).parent_path() /
                "/bm/node.elf32";
  ebbrt::Runtime runtime;
  ebbrt::Context c(runtime);
  boost::asio::signal_set sig(c.io_service_, SIGINT);
  {
    ebbrt::ContextActivation activation(c);

    // ensure clean quit on ctrl-c
    sig.async_wait([&c](const boost::system::error_code &ec,
                        int signal_number) { c.io_service_.stop(); });
    CmdLineArgs::Create(argc, argv, kCmdLineArgsId)
        .Then([bindir](ebbrt::Future<ebbrt::EbbRef<CmdLineArgs>> f) {
          f.Get();
          // TODO(dschatz): Don't chain these futures, instead when_all them
          FileSystem::PreCreate(kFileSystemId)
              .Then([bindir](ebbrt::Future<void> f) {
                f.Get();
                FileSystem::Create(&FileSystem::CreateRep(kFileSystemId),
                                   kFileSystemId);
                ebbrt::node_allocator->AllocateNode(bindir.string(), 1, 1);
              });
        });
  }
  c.Run();

  return 0;
}
