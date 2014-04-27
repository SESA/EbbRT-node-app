//          Copyright Boston University SESA Group 2013 - 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "FileSystem.h"
#include "FileSystem.capnp.h"

#include <capnp/serialize.h>

#include <ebbrt/CapnpMessage.h>
#include <ebbrt/Debug.h>
#include <ebbrt/GlobalIdMap.h>

EBBRT_PUBLISH_TYPE(, FileSystem);

FileSystem::FileSystem(ebbrt::EbbId id, ebbrt::Messenger::NetworkId frontend_id)
    : ebbrt::Messagable<FileSystem>(id), frontend_id_(frontend_id),
      request_(0) {}

namespace {
class StringOutputStream : public kj::OutputStream {
public:
  void write(const void *buffer, size_t size) override {
    str_.append(static_cast<const char *>(buffer), size);
  }
  void
  write(kj::ArrayPtr<const kj::ArrayPtr<const kj::byte> > pieces) override {
    for (auto &piece : pieces) {
      write(piece.begin(), piece.size());
    }
  }

  std::string &String() { return str_; }

private:
  std::string str_;
};
}

ebbrt::Future<void> FileSystem::PreCreate(ebbrt::EbbId id) {
  capnp::MallocMessageBuilder message;
  auto builder = message.initRoot<filesystem::GlobalData>();
  auto nid = ebbrt::messenger->LocalNetworkId().ToBytes();
  builder.setNetworkAddress(capnp::Data::Reader(
      reinterpret_cast<const capnp::byte *>(nid.data()), nid.length()));
  StringOutputStream stream;
  capnp::writeMessage(stream, message);
  return ebbrt::global_id_map->Set(id, std::move(stream.String()));
}

FileSystem &FileSystem::CreateRep(ebbrt::EbbId id) {
  auto f = ebbrt::global_id_map->Get(id).Block();
  auto &str = f.Get();
  auto aptr = kj::ArrayPtr<const capnp::word>(
      reinterpret_cast<const capnp::word *>(str.data()),
      str.length() / sizeof(const capnp::word));
  auto reader = capnp::FlatArrayMessageReader(aptr);
  auto data = reader.getRoot<filesystem::GlobalData>();
  auto net_addr = data.getNetworkAddress();
  auto nid =
      ebbrt::Messenger::NetworkId::FromBytes(net_addr.begin(), net_addr.size());
  return *new FileSystem(id, nid);
}

void FileSystem::DestroyRep(ebbrt::EbbId id, FileSystem &rep) { delete &rep; }

ebbrt::Future<FileSystem::StatInfo> FileSystem::Stat(const char *path) {
  lock_.lock();
  auto v = request_++;
  auto &p = stat_promises_[v];
  lock_.unlock();
  ebbrt::IOBufMessageBuilder message;
  auto builder = message.initRoot<filesystem::Message>();
  auto request_builder = builder.initRequest();
  auto stat_builder = request_builder.initStatRequest();
  stat_builder.setId(v);
  stat_builder.setPath(capnp::Text::Reader(path));
  SendMessage(frontend_id_, ebbrt::AppendHeader(message));
  return p.GetFuture();
}

ebbrt::Future<std::string> FileSystem::GetCwd() {
  lock_.lock();
  auto v = request_++;
  auto &p = cwd_promises_[v];
  lock_.unlock();
  ebbrt::IOBufMessageBuilder message;
  auto builder = message.initRoot<filesystem::Message>();
  auto request_builder = builder.initRequest();
  auto get_cwd_builder = request_builder.initGetCwdRequest();
  get_cwd_builder.setId(v);
  SendMessage(frontend_id_, ebbrt::AppendHeader(message));
  return p.GetFuture();
}

void FileSystem::ReceiveMessage(ebbrt::Messenger::NetworkId nid,
                                std::unique_ptr<ebbrt::IOBuf> &&buffer) {
  auto reader = ebbrt::IOBufMessageReader(std::move(buffer));
  auto message = reader.getRoot<filesystem::Message>();

  switch (message.which()) {
  case filesystem::Message::Which::REQUEST: {
#ifdef __ebbrt__
    EBBRT_UNIMPLEMENTED();
#else
    auto request = message.getRequest();
    switch (request.which()) {
    case filesystem::Request::Which::STAT_REQUEST: {
      auto stat_request = request.getStatRequest();
      // TODO(dschatz): do this on a separate thread
      struct stat buf;
      std::cout << "Stat: " << stat_request.getPath().cStr() << std::endl;
      auto ret = stat(stat_request.getPath().cStr(), &buf);
      if (ret != 0)
        throw std::runtime_error("stat failed");
      ebbrt::IOBufMessageBuilder send_message;
      auto send_builder = send_message.initRoot<filesystem::Message>();
      auto reply_builder = send_builder.initReply();
      auto stat_reply_builder = reply_builder.initStatReply();
      stat_reply_builder.setId(stat_request.getId());
      stat_reply_builder.setDev(buf.st_dev);
      stat_reply_builder.setIno(buf.st_ino);
      stat_reply_builder.setMode(buf.st_mode);
      stat_reply_builder.setNlink(buf.st_nlink);
      stat_reply_builder.setUid(buf.st_uid);
      stat_reply_builder.setGid(buf.st_gid);
      stat_reply_builder.setRdev(buf.st_rdev);
      stat_reply_builder.setSize(buf.st_size);
      stat_reply_builder.setAtime(buf.st_atime);
      stat_reply_builder.setMtime(buf.st_mtime);
      stat_reply_builder.setCtime(buf.st_ctime);
      SendMessage(nid, ebbrt::AppendHeader(send_message));
      break;
    }
    case filesystem::Request::Which::GET_CWD_REQUEST: {
      auto get_cwd_request = request.getGetCwdRequest();
      char buf[PATH_MAX];
      auto ret = getcwd(buf, PATH_MAX);
      if (ret == nullptr)
        throw std::runtime_error("getcwd failed");
      ebbrt::IOBufMessageBuilder send_message;
      auto send_builder = send_message.initRoot<filesystem::Message>();
      auto reply_builder = send_builder.initReply();
      auto get_cwd_reply_builder = reply_builder.initGetCwdReply();
      get_cwd_reply_builder.setId(get_cwd_request.getId());
      get_cwd_reply_builder.setCwd(capnp::Text::Reader(buf));
      SendMessage(nid, ebbrt::AppendHeader(send_message));
      break;
    }
    }
#endif
    break;
  }
  case filesystem::Message::Which::REPLY: {
    auto reply = message.getReply();
    switch(reply.which()) {
    case filesystem::Reply::Which::STAT_REPLY: {
      auto stat_reply = reply.getStatReply();
      StatInfo sinfo;
      sinfo.stat_dev = stat_reply.getDev();
      sinfo.stat_ino = stat_reply.getIno();
      sinfo.stat_mode = stat_reply.getMode();
      sinfo.stat_nlink = stat_reply.getNlink();
      sinfo.stat_uid = stat_reply.getUid();
      sinfo.stat_gid = stat_reply.getGid();
      sinfo.stat_rdev = stat_reply.getRdev();
      sinfo.stat_size = stat_reply.getSize();
      sinfo.stat_atime = stat_reply.getAtime();
      sinfo.stat_mtime = stat_reply.getMtime();
      sinfo.stat_ctime = stat_reply.getCtime();
      auto id = stat_reply.getId();
      std::lock_guard<std::mutex> lock(lock_);
      auto it = stat_promises_.find(id);
      assert(it != stat_promises_.end());
      it->second.SetValue(sinfo);
      stat_promises_.erase(it);
      break;
    }
    case filesystem::Reply::Which::GET_CWD_REPLY: {
      auto get_cwd_reply = reply.getGetCwdReply();
      auto id = get_cwd_reply.getId();
      std::lock_guard<std::mutex> lock(lock_);
      auto it = cwd_promises_.find(id);
      assert(it != cwd_promises_.end());
      it->second.SetValue(std::string(get_cwd_reply.getCwd().cStr()));
      cwd_promises_.erase(it);
      break;
    }
    }
    break;
  }
  }
}
