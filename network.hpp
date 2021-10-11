#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = net::ip::tcp;
using error_code = boost::system::error_code;