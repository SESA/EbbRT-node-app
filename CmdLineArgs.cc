//          Copyright Boston University SESA Group 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "CmdLineArgs.h"
#include "CmdLineArgs.capnp.h"

#include <capnp/serialize.h>

#include <ebbrt/GlobalIdMap.h>
#include <ebbrt/LocalIdMap.h>

CmdLineArgs::CmdLineArgs(std::vector<std::string> args)
    : args_(std::move(args)), argv_(args_.size()) {
  // copy the char* from each string into argv
  std::transform(
      args_.begin(), args_.end(), argv_.begin(),
      [](const std::string &s) { return const_cast<char *>(s.data()); });
}

CmdLineArgs &CmdLineArgs::HandleFault(ebbrt::EbbId id) {
  {
    ebbrt::LocalIdMap::ConstAccessor accessor;
    auto found = ebbrt::local_id_map->Find(accessor, id);
    if (found) {
      auto &m = *boost::any_cast<CmdLineArgs *>(accessor->second);
      ebbrt::EbbRef<CmdLineArgs>::CacheRef(id, m);
      return m;
    }
  }

  auto f = ebbrt::global_id_map->Get(id).Block();
  auto &str = f.Get();
  auto aptr = kj::ArrayPtr<const capnp::word>(
      reinterpret_cast<const capnp::word *>(str.data()),
      str.length() / sizeof(const capnp::word));
  auto reader = capnp::FlatArrayMessageReader(aptr);
  auto data = reader.getRoot<cmdlineargs::GlobalData>();
  (void)data;

  // try to construct
  auto p = new CmdLineArgs(std::vector<std::string>());

  auto inserted = ebbrt::local_id_map->Insert(std::make_pair(id, p));
  if (inserted) {
    ebbrt::EbbRef<CmdLineArgs>::CacheRef(id, *p);
    return *p;
  }

  // raced, delete the new matrix
  delete p;
  ebbrt::LocalIdMap::ConstAccessor accessor;
  auto found = ebbrt::local_id_map->Find(accessor, id);
  assert(found);
  (void)found; // unused variable
  auto &m = *boost::any_cast<CmdLineArgs *>(accessor->second);
  ebbrt::EbbRef<CmdLineArgs>::CacheRef(id, m);
  return m;
}

ebbrt::Future<ebbrt::EbbRef<CmdLineArgs> >
CmdLineArgs::Create(int argc, char **argv, ebbrt::EbbId id) {
  return ebbrt::global_id_map->Set(id, std::string())
      .Then([id](ebbrt::Future<void> f) {
        f.Get();
        return ebbrt::EbbRef<CmdLineArgs>(id);
      });
}
