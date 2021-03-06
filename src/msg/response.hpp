#pragma once

#include <string>

namespace yess::msg
{
enum class ResponseStatus { OK, Error };
class Response
{
  public:
    Response(ResponseStatus status, std::string message);
    std::string getMessage();
    ResponseStatus getStatus();
    bool operator==(const Response& resp) const;

  private:
    ResponseStatus m_status;
    std::string m_message;
};
} // namespace yess::msg
