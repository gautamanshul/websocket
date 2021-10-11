#include <string>
#include <iostream>
#include <vector>
#include <boost/any.hpp>
#include <boost/signals2.hpp>

template <typename T>
struct INotifyPropertyChanged
{
	virtual ~INotifyPropertyChanged() = default;
	boost::signals2::signal<void(T&, const std::string&)> PropertyChanged;
};

struct Person : INotifyPropertyChanged<Person>
{
	explicit Person(const int age) : age(age)
	{

	}

	virtual int GetAge() const
	{
		return age;
	}

	virtual void SetAge(const int age)
	{
		if (this->age == age) return;
		this->age = age;
		PropertyChanged(*this, "age");
	}

private:
	int age;
};


int main11()
{
	Person p{ 123 };
	p.PropertyChanged.connect([](Person&, const std::string& property_name) {
		std::cout << property_name << " has been changed" << std::endl;
		});

	p.SetAge(20);

	getchar();
	return 0;
}