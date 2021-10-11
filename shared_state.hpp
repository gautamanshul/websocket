#pragma once

#include "websocket_session.hpp"

#include <unordered_set>
#include <vector>
#include <memory>

class websocket_session;

class shared_state
{
	// Doc root. HTTP server, it servers HTML's, images and ads.
	// Doc root is the path to these files
	std::string  doc_root_;

	// Keeps track of all users currently connected. Send messages and
	// remove users
	std::unordered_set<websocket_session*> sessions_;

public:
	explicit shared_state(std::string  doc_root);

	std::string const&
		doc_root() const noexcept { return doc_root_; }

	void join(websocket_session& session);
	void leave(websocket_session& session);
	void send(std::string message);

};
