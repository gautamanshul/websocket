#include <iostream>
#include <string>
#include <vector>
#include <boost/any.hpp>
#include <algorithm>
#include <mutex>

static std::mutex mtx;

struct Person;
struct PersonListener
{
	virtual ~PersonListener() = default;
	virtual void PersonChanged(Person& p, const std::string& property_name, const boost::any new_value) = 0;
};

struct ConsoleListener : PersonListener
{
	void PersonChanged(Person& p, const std::string& property_name, const boost::any  new_value) override
	{
		std::cout << "Person's " << property_name << " has been changed to ";
		if (property_name == "age")
		{
			std::cout << boost::any_cast<int>(new_value) << "\n"; 
		}
		else if (property_name == "can_vote")
		{
			std::cout << boost::any_cast<bool>(new_value) << "\n";
		}
	}
};
struct Person
{
	Person(const int age) : age(age) {}
	virtual int GetAge() const
	{
		return age;
	}

	virtual void SetAge(const int age)
	{
		auto old_c_v = GetCanVote();
		this->age = age;
		
		
		notify("age", this->age);
		auto new_c_v = GetCanVote();

		if (old_c_v != new_c_v)
		{
			notify("can_vote", new_c_v);
		}
	}

	void subscribe(PersonListener* p)
	{
		std::lock_guard<std::mutex> guard(mtx);
		if (find(begin(listeners), end(listeners), p) == end(listeners))
			listeners.push_back(p);
	}

	void Unsubscribe(PersonListener* pl)
	{
		std::lock_guard<std::mutex> guard{ mtx };
		for (auto it = listeners.begin(); it != listeners.end(); ++it)
		{
			if (*it == pl)
			{
				*it = nullptr;
			}
		}
	}

	bool GetCanVote() const
	{
		return age >= 16;
	}

	void notify(const std::string& property_name, const boost::any new_value)
	{
		for (const auto listener : listeners)
		{
			if (listener)
				listener->PersonChanged(*this, property_name, new_value);
		}
		listeners.erase(remove(listeners.begin(), listeners.end(), nullptr), listeners.end());
	}
private:
	int age;
	std::vector<PersonListener*> listeners;
};

int main10()
{
	Person p(14);

	ConsoleListener cl;
	p.subscribe(&cl);

	p.SetAge(15);
	p.SetAge(16);
	p.Unsubscribe(&cl);
	p.SetAge(17);


	getchar();
	return 0;
}