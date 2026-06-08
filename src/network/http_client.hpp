#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>


namespace aix {
  class HttpClient {
    public:
      HttpClient();
      ~HttpClient();

      std::string post(const std::string& url, const std::string& json_payload);
  };
}

#endif
