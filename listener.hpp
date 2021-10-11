#pragma once
#include "shared_state.hpp"
#include "network.hpp"
#include <memory>

class listener : public std::enable_shared_from_this<listener>
{
	tcp::acceptor acceptor_;
	tcp::socket  socket_;
	ssl::stream<tcp::socket> ssl_socket_;
	std::shared_ptr<shared_state>  state_;
	ssl::context context_;

	void fail(error_code, const char* what);
	void on_accept(error_code ec);
	std::string get_password() const;
public:
	listener(
		net::io_context& ioc,
		tcp::endpoint endpoint,
		std::shared_ptr<shared_state> const& state);
	void run();
};
