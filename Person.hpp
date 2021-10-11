#pragma once
#include <string>
#include "ChatRoom.hpp"

/*struct Person
{
	std::string name;
	ChatRoom* room = nullptr;
	std::vector<std::string> log;

	explicit Person(const std::string& name) : name(name)
	{}

	void say(const std::string& message);
	void receive(const std::string& origin, const std::string& message);
	void pm(const std::string& who, std::string& message);

};

void Person::pm(const std::string& who, std::string& message)
{
	room->message(name, who, message);
}

void Person::say(const std::string& message)
{
	room->broadcast(name, message);
}

void Person::receive(const std::string& origin, const std::string& message)
{
	std::string s{ origin + ": \"" + message + ": \"" };
	std::cout << "[" << name << "'s chat session] " << s << "\n";
	log.emplace_back(s);
}*/

