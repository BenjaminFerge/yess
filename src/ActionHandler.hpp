#pragma once

#include <memory>
#include <string>

#include "Poco/JSON/Object.h"
#include "Response.hpp"
#include "Server.hpp"
#include "db/Entities/Stream.hpp"
#include "db/Repositories/StreamRepository.hpp"

namespace yess
{
enum Action {
    None,
    CreateStream,
    PushEvent,
    GetAllStreams,
    GetStreamsByType,
    GetStream,
    GetEventsByStreamId,
    GetEventsByStreamType,
};
std::string actionToString(Action action);
Action actionFromString(std::string action);

class ActionHandler
{
  public:
    ActionHandler();
    ~ActionHandler();
    Response handle(Poco::JSON::Object::Ptr action);
    void saveStream(const db::Stream &stream);

  private:
    Server *m_pServer;
    std::unique_ptr<db::StreamRepository> m_streamRepository;
};
} // namespace yess
