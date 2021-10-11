#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

struct BankAccount
{
	int balance = 0;
	int overdraft_limit = -500;

	void deposit(int amount)
	{
		balance += amount;
		std::cout << "deposited " << amount << " new balance " << balance;
	}

	void withdraw(int amount)
	{
		if (balance - amount >= overdraft_limit)
		{
			balance -= amount;
			std::cout << "withdrew " << amount << " new balance " << balance;
		}
	}
};

struct ICommand
{
	virtual ~ICommand() = default;
	virtual void call() const = 0;
	virtual void undo() const = 0;
};



struct Command : ICommand
{
	BankAccount& account;
	enum Action {deposit, withdraw} action;
	int amount;

	Command(BankAccount& account, const Action action, const int amount)
		:account(account),
		action(action),
		amount(amount)
	{

	}

	void call() const override
	{
		switch (action)
		{
		case Action::deposit: 
			account.deposit(amount);
			break;
		case withdraw:
			account.withdraw(amount);
			break;
		default:
			break;
		}
	}

	void undo() const override
	{
		switch (action)
		{
		case deposit:
			account.withdraw(amount);
			break;
		case withdraw:
			account.deposit(amount);
			break;
		default:
			break;

		}
	}
};

struct CommandList : std::vector<Command>, ICommand
{
	CommandList(const std::initializer_list<value_type> & IList) : std::vector<Command>( IList){}

	void call() const override
	{
		for (auto& cmd : *this)
		{
			cmd.call();
		}
	}

	void undo() const override
	{
		/*std::for_each(rbegin(), rend(), [](Command& c) {
			c.undo();
			});*/
	}
};

int main5()
{
	BankAccount ba;
	CommandList cmds{ {ba, Command::Action::deposit,100}, {ba,Command::Action::withdraw, 50} };
	
	std::cout << ba.balance << "\n";
	cmds.call();
	std::cout << ba.balance << "\n";
	cmds.undo();
	std::cout << ba.balance << "\n";
	return 0;
}