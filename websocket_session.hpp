#pragma once

#include "beast_support.hpp"
#include "shared_state.hpp"
#include "network.hpp"

#include <string>
#include <vector>
#include <memory>

class shared_state;

class websocket_session : public std::enable_shared_from_this<websocket_session>
{
	beast::flat_buffer buffer_;
	// While http doesn't save state information, websockets need to save the state
	// information. Beast manages all the protocol details
	// Websocket can only send one message at a time
	websocket::stream<tcp::socket> ws_;

	// State has the list of connected websocket sessions
	std::shared_ptr<shared_state>  state_;

	// queue is for the outgoing messages
	std::vector<std::shared_ptr<std::string const>> queue_;

	void fail(error_code ec, const char* what);
	void on_accept(error_code ec);
	void on_read(error_code ec, std::size_t);
	void on_write(error_code ec, std::size_t);

public:
	~websocket_session();
	websocket_session(tcp::socket socket, std::shared_ptr<shared_state> const& state);

	template<class Body, class Allocator>
	void run(http::request<Body, http::basic_fields<Allocator>> req);

	void send(std::shared_ptr<std::string const> const& ss);
};
