#pragma once

#include "shared_state.hpp"
#include <memory>
class http_session : public std::enable_shared_from_this<http_session>
{
	tcp::socket socket_;
	beast::flat_buffer buffer_;
	std::shared_ptr<shared_state> state_;
	http::request<http::string_body> req_;

	void fail(error_code ec, const char* what);
	void on_read(error_code ec, std::size_t);
	void on_write(error_code ec, std::size_t, bool close);

public:
	http_session(tcp::socket socket, std::shared_ptr<shared_state> const& state);
	void run();
};
