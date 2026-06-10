#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>


namespace aix {
  class HttpClient {
    public:
      HttpClient() = default;
      ~HttpClient() = default;

      std::string post(const std::string& url, const std::string& json_payload);
  };
}

#endif
