#include "http_client.hpp"
#include <curlpp/Easy.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/cURLpp.hpp>
#include <list>
#include <sstream>

namespace aix {
std::string HttpClient::post(const std::string &url, const std::string &json_payload) {
    curlpp::Easy request;

    try {
        request.setOpt(new curlpp::options::Url(url));
        std::list<std::string> header;
        header.push_back("Content-Type: application/json");
        request.setOpt(new curlpp::options::HttpHeader(header));
        request.setOpt(new curlpp::options::PostFields(json_payload));
        request.setOpt(new curlpp::options::PostFieldSize(json_payload.length()));
        std::ostringstream respones_stream;
        request.setOpt(new curlpp::options::WriteStream(&respones_stream));
        request.perform();
        return respones_stream.str();

    } catch (curlpp::LogicError &e) {
        return "Logic Error: " + std::string(e.what());
    } catch (curlpp::RuntimeError &e) {
        return "Runtime Error: " + std::string(e.what());
    }
}

} // namespace aix
