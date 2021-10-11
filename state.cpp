#include <iostream>
#include <string>
#include <vector>
#include <map>

enum class State {
	OffHook,
	Connecting,
	Connected,
	OnHold
};
enum class Trigger
{
	CallDialed,
	HungUp,
	CallConnected,
	PlacedOnHold,
	TakenOffHold,
	LeftMessage
};

inline std::ostream& operator << (std::ostream& os, const State & s)
{
	switch (s)
	{
	case State::OffHook:
		os << "Off the hook";
		break;

	case State::Connecting:
		os << "connecting";
		break;
	case State::Connected:
		os << "connected";
		break;
	case State::OnHold:
		os << "on hold";
		break;
	default:
		break;
	}

	return os;
}

inline std::ostream& operator << (std::ostream& os, const Trigger& t)
{
	switch (t)
	{
	case Trigger::CallDialed:
		std::cout << "call dialed";
		break;
	case Trigger::HungUp:
		std::cout << "hung up";
		break;
	case Trigger::CallConnected:
		std::cout << "call connected";
		break;
	case Trigger::PlacedOnHold:
		std::cout << "placed on hold";
		break;
	case Trigger::TakenOffHold:
		std::cout << "taken off hold";
		break;
	case Trigger::LeftMessage:
		std::cout << "left message";
		break;
	}

	return os;
}



int main13()
{
	std::map<State, std::vector<std::pair<Trigger, State>>> rules;
	
	rules[State::OffHook] = { { Trigger::CallDialed, State::Connecting }  };
	rules[State::Connecting] = { { Trigger::HungUp, State::OffHook }, {Trigger::CallConnected, State::Connected} };
	rules[State::Connected] = { { Trigger::LeftMessage, State::OffHook}, {Trigger::HungUp, State::OffHook}, {Trigger::PlacedOnHold, State::OnHold} };
	rules[State::OnHold] = { {Trigger::TakenOffHold, State::Connected}, {Trigger::HungUp, State::OffHook} };


	State currentState{ State::OffHook };
	while (true)
	{
		std::cout << "The phone is currently " << currentState << "\n";
		select_trigger:
		std::cout << "Select the trigger " << "\n";

		int i = 0;
		for (auto item : rules[currentState])
		{
			std::cout << i++ << ". " << item.first << "\n";
		}

		int input;
		std::cin >> input;
		if (input < 0 || (input + 1) > rules[currentState].size())
		{
			std::cout << "Incorrect option, please try again " << "\n";
			goto select_trigger;
		}

		currentState = rules[currentState][input].second;
	}

	std::cout << "we are done using the phone " << std::endl;
	getchar();
	return 0;
}