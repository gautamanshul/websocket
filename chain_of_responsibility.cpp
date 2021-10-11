#include <iostream>
#include <string>

struct Creature
{
	std::string name;
	int attack, defense;

	Creature(const std::string& name, const int attack, const int defense)
		:name(name),
		attack(attack),
		defense(defense)
	{

	}

	friend std::ostream& operator << (std::ostream & os, const Creature & obj)
	{
		os << "name " << obj.name
			<< "attack " << obj.attack
			<< "defense " << obj.defense;

		return os;
	}
};

struct CreatureModifier
{
	CreatureModifier* next = nullptr;
protected:
	Creature& creature;
public:
	explicit CreatureModifier(Creature& creature) : creature(creature)
	{}

	virtual ~CreatureModifier() = default;

	void add(CreatureModifier* cm)
	{
		if (next) next->add(cm);
		next = cm;
	}

	virtual void handle()
	{
		if (next) next->handle();
	}
};

// 1. Double the creature's attack
// 2. Increase defense by 1 unless power > 2
// 3. No bonuses can be applied to this creature
class DoubleAttackModifier : public CreatureModifier
{
public:
	explicit DoubleAttackModifier(Creature& creature) : CreatureModifier(creature)
	{}

	void handle() override
	{
		creature.attack *= 2;
		CreatureModifier::handle();
	}
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
	explicit IncreaseDefenseModifier(Creature & creature): CreatureModifier(creature)
	{}

	void handle() override
	{
		if (creature.attack <= 2) creature.defense += 1;
		CreatureModifier::handle();
	}
};

class NoBonusModifier : public CreatureModifier
{
public:
	explicit NoBonusModifier(Creature & creature): CreatureModifier(creature){}


	void handle() override
	{

	}
};

int main4()
{
	Creature goblin{ "Goblin", 1, 1 };
	CreatureModifier root{ goblin };
	DoubleAttackModifier r1{ goblin };
	IncreaseDefenseModifier r2{ goblin };
	NoBonusModifier r3{ goblin };

	root.add(&r3);
	root.add(&r1);
	root.add(&r2);
	

	root.handle();

	getchar();
	return 0;

}