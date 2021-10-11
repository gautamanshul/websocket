#include <iostream>
#include <string>
#include <functional>

struct Logger
{
	std::function<void()> func;
	std::string name;
	Logger(const std::function<void()> & func, const std::string & name ) : func(func), name(name) {}

	void operator()()
	{
		std::cout << "Entering " << name << std::endl;
		func();
		std::cout << "Exiting " << name << std::endl;
	}
};

template <typename Func>
struct Logger2
{
	Func func;
	std::string name;

	Logger2(Func func, const std::string & name) : func(func), name(name) {}

	void operator() ()
	{
		std::cout << "Entering " << name << std::endl;
		func();
		std::cout << "Exiting " << name << std::endl;
	}
};

template <typename Func>
auto make_logger2(Func func, const std::string& name)
{
	return Logger2<Func>{ func, name };
}

template <typename> struct Logger3;

template <typename R, typename... Args>
struct Logger3<R(Args...)>
{
	std::function<R(Args...)> func;
	std::string name;

	Logger3( const std::function<R(Args...)> & func, const std::string & name) : func(func), name(name) {}

	R operator() (Args ...args)
	{
		std::cout << "Entering " << name << std::endl;
		R result = func(args...);
		std::cout << "Exiting " << name << std::endl;
		return result;
	}
};

template <typename R, typename... Args>
auto make_logger3(R(*func) (Args...), const std::string& name)
{
	return Logger3<R(Args...)>{ std::function<R(Args...)>(func), "Logger3" };
}

int add(int a, int b)
{
	std::cout << a << "+" << b << "=" << (a + b) << std::endl;
	return a + b;
}

int main22()
{
	auto logger3 = make_logger3(add, "Add");
	auto result = logger3(1, 3);

	getchar();
	return 0;
}