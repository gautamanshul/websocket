#include <iostream>
#include <string>
#include <algorithm>
#include <typeindex>
#include <sstream>
#include <map>

struct GameObject
{
	virtual ~GameObject() = default;
	virtual std::type_index type() const = 0;
};

template <typename T>
struct GameObjectImpl : GameObject
{
	std::type_index type() const override
	{
		return typeid(T);
	}
};

struct Planet : GameObjectImpl<Planet> {};
struct Asteroid: GameObjectImpl<Asteroid> {};
struct Spaceship: GameObjectImpl<Spaceship>{};

void spaceship_planet() {std::cout << "spaceship lands on the planet\n"; }
void asteroid_planet() {
	std::cout << "aasteroid burns up in atmosphere\n";
}
void asteroid_spaceship() { std::cout << "asteroid hits and destroys spaceship\n"; }


std::map<std::pair<std::type_index, std::type_index>, void(*)(void)> outcomes
{
	{{typeid(Spaceship),typeid(Planet)}, spaceship_planet},
{{typeid(Asteroid),typeid(Planet)}, asteroid_planet},
{{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship }
	};

void collide(GameObject& first, GameObject& second)
{
	auto it = outcomes.find({ first.type(), second.type() });
	if (it == outcomes.end())
	{
		it = outcomes.find({ second.type(), first.type() });
		if (it != outcomes.end())
		{
			std::cout << "Objects pass each other harmlessly\n";
		}
		
	}
	it->second();
}

int main7()
{
	Spaceship spaceship;
	Asteroid asteroid;
	Planet planet;

	collide(planet, spaceship);
	collide(planet, asteroid);
	collide(spaceship, asteroid);
	collide(planet, planet);
	return 0;
}