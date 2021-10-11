#include "listener.hpp"
#include "http_session.hpp"
#include <iostream>
#include "network.hpp"

class http_session;

listener::listener(net::io_context& ioc, tcp::endpoint endpoint, std::shared_ptr<shared_state> const& state ) :
	acceptor_(ioc), socket_(ioc), state_(state), context_(ssl::context::sslv23), ssl_socket_(ioc, context_)
{
	error_code ec;

	net::ssl::context context_(ssl::context::sslv23);
	context_.set_options(ssl::context::default_workarounds | ssl::context::no_sslv2 | ssl::context::single_dh_use);

	context_.set_password_callback(std::bind(&listener::get_password, this));
	/// TBD: Set the path to server.pem
	context_.use_certificate_chain_file("server.pem");

	context_.use_private_key_file("server.pem", ssl::context::pem); // 
	context_.use_tmp_dh_file("dh2048.pem"); // obtain temporary Diffie-helman parameters

	acceptor_.open(endpoint.protocol(), ec);
	if (ec)
	{
		fail(ec, "open");
		return;
	}

	// Allow address reuse
	acceptor_.set_option(net::socket_base::reuse_address(true));
	if (ec)
	{
		fail(ec, "set option");
		return;
	}

	// Bind to the server address
	acceptor_.bind(endpoint, ec);
	if (ec)
	{
		fail(ec, "bind");
		return;
	}

	// Start listening for connections
	acceptor_.listen(
		net::socket_base::max_listen_connections, ec);

	if (ec)
	{
		fail(ec, "listen");
		return;
	}
}

std::string listener::get_password() const
{
	return "test";
}

void listener::run()
{
	// Start accepting a connection.
	// This call is outstanding until it receives an incoming connection
	// Once a connection is accepted, it will invoke our lambda object
	// Socket will hold the new connection
	// The shared pointer reference is bound in the async accept call and this extends
	// the lifetime of the listener object.
	// Networking TS takes the ownership of the completion handler
	acceptor_.async_accept(
		socket_,
		[self = shared_from_this()](error_code ec)
	{
		self->on_accept(ec);
	});
}

void listener::on_accept(error_code ec)
{
	if (ec)
	{
		fail(ec, "accept");
	}
	else
	{
		// Launch a new session for this connection
		std::make_shared<http_session>(
			std::move(socket_), state_)->run();

		// Accept another connection
		acceptor_.async_accept(
			socket_,
			[self = shared_from_this()](error_code ec)
		{
			self->on_accept(ec);
		});
	}
}

// if the operation is canceled, operation aborted error is send
// For example, if ctrl + c is invoked and server is aborted, then operation is aborted
void listener::fail(error_code ec, char const* what)
{
	// Don't report on canceled operations
	if (ec == net::error::operation_aborted)
	{
		return;
	}

	std::cerr << what << ": " << ec.message() << "\n";
}

