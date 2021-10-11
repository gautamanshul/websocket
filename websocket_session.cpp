
#include <boost/beast/websocket.hpp>
#include <boost/asio/io_context.hpp>
#include "websocket_session.hpp"

#include <iostream>

websocket_session::websocket_session(tcp::socket socket, std::shared_ptr<shared_state> const& state) :
	ws_(std::move(socket)), state_(state) {}

template <class Body, class Allocator>
void websocket_session::run(http::request<Body, http::basic_fields<Allocator>> req)
{
	/// http upgrade to websocket request is passed into beast websocket. 
	/// Beast validates the request, makes sure everything is kosher.
	/// Sends back the proper response and completion handler is invoked which calls on accept.
	ws_.async_accept(req,
		[self = shared_from_this()](error_code ec)
	{
		self->on_accept(ec);
	});
}

void websocket_session::on_accept(error_code ec)
{
	if (ec)
	{
		return fail(ec, "accept");
	}

	/// Add the session to the state list
	state_->join(*this);

	// Read a message
	ws_.async_read(buffer_, [sp = shared_from_this()](error_code ec, std::size_t bytes)
	{
		sp->on_read(ec, bytes);
	});
}

void websocket_session::on_read(error_code ec, size_t bytes)
{
	if (ec)
	{
		return fail(ec, "read");
	}

	// send message to all connections
	state_->send(beast::buffers_to_string(buffer_.data()));

	// Clear the buffer
	buffer_.consume(buffer_.size());

	// Read into the buffer again
	ws_.async_read(buffer_, [sp = shared_from_this()](error_code ec, size_t bytes)
	{
		sp->on_read(ec, bytes);
	});
}

void websocket_session::send(std::shared_ptr<std::string const> const& ss)
{
	// Always add to the queue
	queue_.push_back(ss);

	// Are we already writing
	if (queue_.size() > 1)
		return;

	// net:buffer converts the first string the the queue into a const buffer
	// Then we have a completion handler which is invoked after message is sent
	ws_.async_write(
		net::buffer(*queue_.front()), [sp = shared_from_this()](
			error_code ec, size_t bytes)
	{
		sp->on_write(ec, bytes);
	});
}

void websocket_session::on_write(error_code ec, size_t bytes)
{
	if (ec) return fail(ec, "write");

	queue_.erase(queue_.begin());

	if (!queue_.empty())
	{
		ws_.async_write(
			net::buffer(*queue_.front()),
			[sp = shared_from_this()](error_code ec, size_t bytes)
		{
			sp->on_write(ec, bytes);
		});
	}
}

void websocket_session::fail(error_code ec, const char* what)
{
	/// Don't report these as we don't want to flood the console.
	/// Client might close the websocket and we don't need to report it.
	if (ec == net::error::operation_aborted ||
		ec == websocket::error::closed)
	{
		return;
	}

	std::cerr << what << ": " << ec.message() << "\n";
}

websocket_session::~websocket_session()
{
	state_->leave(*this);
}
