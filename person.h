#include <string>

struct Personv1
{
	std::string  name;
	void greet();

	struct PersonImpl;
	PersonImpl* impl;

	Personv1();
	~Personv1();

};