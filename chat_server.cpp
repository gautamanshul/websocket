#include <boost/beast/core.hpp>
//#include <boost/beast/ssl.hpp>
#include <boost/beast/http.hpp>
///#include <boost/beast/websocket.hpp>
#include <boost/asio/io_context.hpp>
//#include <boost/asio/ssl.hpp>

#include "listener.hpp"
#include "shared_state.hpp"


#include <string>
#include <unordered_set>
#include <memory>
#include <iostream>

//namespace net = boost::asio;
//net::io_context  ioc;
//namespace ssl = boost::asio::ssl;
//using tcp = net::ip::tcp;
//using error_code = boost::system::error_code;

// Holds the server data. Information that every object in the system needs to have access to.
//class shared_state;

// Accepts incoming connections
//class listener;

// Handle HTTP requests on a connection
//class http_session;

// Maintains the active websocket connection
//class websocket_session;



// Usage: websocket-chat-server <address> <port> <doc_root>
// Creates and runs the server
int main(int argc, char* argv[])
{
	auto address = net::ip::make_address(argv[1]);
	auto port = static_cast<unsigned short>(std::atoi(argv[2]));
	auto doc_root = argv[3];

	// The IO context is needed for all input output
	net::io_context  ioc;
	

	// Create and launch a listening port
	// Run will make a copy of the shared ptr to extend the lifetime of the listener

	std::make_shared<listener>(
		ioc,
		tcp::endpoint{ address, port },
		std::make_shared<shared_state>(doc_root)
		)->run();
	// Run will block and networking TS takes over the thread and uses it to invoke the completion handlers.
	ioc.run();
	return EXIT_SUCCESS;
}

// send a payload prefixed with a header
//template <class SyncWriteStream>
//void send_message(SyncWriteStream& stream, net::const_buffer payload)
//{
	//auto  header = make_header(payload);

	// Create a non-owning, 2 element buffer range. Write is only called once. This avoids multiple IO request.
	//std::array<2, net::const_buffer> b{ header, payload };
	//net::write(stream, b);
//}

// Write a buffer to the sequence returns the number of bytes written
//template <class SyncWriteStream, class ConstBufferSequence>
//size_t write(SyncWriteStream& stream, ConstBufferSequence const& b);

// Consbuffer is a biderictional range of contiguous memory regions
// Reference semantics
// Length is fixed and cannot be resized
// Lightweight and copyable (no vector)
// Networking TS concept, user-defined type possible
// Beast provides several buffer sequence types



//int func_test()
//{
//	std::string s = "Hello world";
//	net::write(sock, net::const_buffer(s.data(), s.size()));
//	
//	net::write(sock, net::buffer(s));
//
//
//	/// Read data into a buffer until it contains a specified string
//
//	auto matching_bytes = net::read_until(sock, b, "\r\n\r\n");
//}

// Dynamic buffer is a resizable buffer sequence with a read area and a write area
// Useful when expected input size is unknown
// User defined types are possible
// Beast provides several dynamic buffer types
//template < class SyncReadStream, class DynamicBuffer >
//size_t read_until(SyncReadStream& s, DynamicBuffer&& buffer, std::string_view match);

// Dynamic buffer on declaration starts out empty. Read and write area are zero bytes
//X a;
//auto bytes_transferred = sock.read_some(a.prepare(128)); // Resize write area to have 128 bytes of storage.

// Move bytes from write area to read area
//a.commit(bytes_transferred);

// Process the data in the read area
//auto bytes_used = process(a.data()); //return 40

// Remove bytes from read area
//a.consume(bytes_used);

// Perform a blocking read
//auto bytes_transferred = sock.read_some(b);

// Start a blocking read. This call returns immediatel//y
//sock.async_read_some(buffers, [&](error_code ec, size_t bytes_transferred)
	//{
		// Lambda expression is invoked when read operation completes at a later stage

//	});


