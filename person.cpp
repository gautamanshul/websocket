#include "person.h"
#include <iostream>

struct Personv1::PersonImpl
{
	void greet( Personv1 * p);
};

void Personv1::PersonImpl::greet(Personv1 * p)
{
	std::cout << "Hello, my name is " << p->name << std::endl;
}

Personv1::Personv1() : impl( new PersonImpl )
{}

Personv1::~Personv1()
{
	delete impl;
}

void Personv1::greet()
{
	impl->greet(this);
}