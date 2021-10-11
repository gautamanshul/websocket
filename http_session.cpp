#include "http_session.hpp"

#include <iostream>

void http_session::fail(error_code ec, const char* what)
{
	if (ec == net::error::operation_aborted)
		return;

	std::cerr << what << ": " << ec.message() << "\n";
}

http_session::http_session(tcp::socket socket, std::shared_ptr<shared_state>  const& state) :
	socket_(std::move(socket)), state_(state)
{}

void http_session::run()
{
	// Read an entire http message. Message is stored in req_ var and completion handler is invoked
	// We are binding shared  from this into the lambda
	http::async_read(socket_, buffer_, req_,
		[self = shared_from_this()](error_code ec, std::size_t  bytes)
	{
		self->on_read(ec, bytes);
	});
}

template <class Body, class Allocator, class Send>
void handle_request(boost::beast::string_view  doc_root, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send)
{

}

void http_session::on_read(error_code  ec, std::size_t bytes)
{
	// This means client closed the connection, so we shutdown the socket.
	// Http handler will be destroyed once the Networking TS completion handler
	// is destroyed. 
	if (ec == http::error::end_of_stream)
	{
		socket_.shutdown(tcp::socket::shutdown_send, ec);
		return;
	}

	if (ec) return fail(ec, "read");

	// Handle websocket upgrade. HTTP session object will be destroyed
	// as we return from here.
	if (websocket::is_upgrade(req_))
	{
		std::make_shared<websocket_session>(
			std::move(socket_), state_)->run(std::move(req_));
		return;
	}
	// Handle http request. Check to see if the file is present 
	// in document root and serve it. This function will have different response type
	// based on the request type.
	handle_request(state_->doc_root(), std::move(req_),
		[this](auto&& response)
	{
		using response_type = typename std::decay<decltype(response)>::type;

		auto sp = std::make_shared<response_type>(std::move(response));

		http::async_write(this->socket_, *sp, [self = shared_from_this(), sp]
		(error_code ec, std::size_t bytes)
		{
			// Once the message is sent, the completion handler with on write 
			// function is invoked.
			self->on_write(ec, bytes, sp->need_eof());
		});
	});
}

void http_session::on_write(error_code ec, size_t bytes, bool close)
{
	if (ec)
		return fail(ec, "write");

	if (close)
	{
		// This means we should close the connection
		socket_.shutdown(tcp::socket::shutdown_send, ec);
		return;
	}

	// Clear the contents of the request message
	// otherwise the read behavior is undefined.
	req_ = {};

	// Read another request.
	http::async_read(socket_, buffer_, req_,
		[self = shared_from_this()](error_code ec, size_t bytes)
	{
		self->on_read(ec, bytes);
	});
}