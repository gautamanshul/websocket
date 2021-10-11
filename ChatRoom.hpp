#pragma once
#include "Person.hpp"
#include <vector>
#include <iostream>
#include <algorithm>
// Mediator
/*struct Person;
struct ChatRoom
{
	std::vector<Person> people;

public:
	class PersonReference
	{
	public:
		std::vector<Person>& people;
		int index;
		explicit PersonReference(std::vector<Person>& p, int index) : people(p), index(index)
		{}

		Person* operator ->() const { return &people[index]; }
	};
	void broadcast(const std::string& origin, const std::string& message);
	PersonReference join(Person&& p);

	void message(const std::string& origin, const std::string& who, const std::string& message)
	{
		auto target = std::find_if(begin(people), end(people), [&](const Person & p) {
			return p.name == who;
			});

		if (target != end(people))
		{
			target->receive(origin, message);
		}
	}
};

ChatRoom::PersonReference ChatRoom::join(Person&& p)
{
	std::string join_msg{ p.name + " join's the chatroom" };
	broadcast("room", join_msg);

	p.room = this;
	people.emplace_back(p);

	return PersonReference{ people, people.size() - 1 };
}

void ChatRoom::broadcast(const std::string& origin, const std::string& message)
{

	for (auto & p : people)
		if (p.name != origin) 
		{ 
			p.receive(origin, message); 
		}
}*/