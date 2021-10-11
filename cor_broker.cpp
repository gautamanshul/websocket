#include <iostream>
#include <string>
#include <boost/signals2.hpp>



struct Query
{
	std::string creature_name;
	enum Argument { attack, defense} argument;
	int result;

	Query(const std::string& creature_name, const Argument argument, const int result)
		:creature_name(creature_name),
		argument(argument),
		result(result)
	{}

};
struct Game
{
	boost::signals2::signal<void(Query&)> queries;
};

struct Creature
{
	Game& game;
	int attack, defense;
public:
	std::string name;

	Creature(Game& game, const int attack, const int defense, const std::string& name) : game(game), attack(attack), defense(defense), name(name)
	{}

	int GetAttack() const
	{
		Query q{ name, Query::Argument::attack, attack };
		game.queries(q);
		return q.result;
	}

	friend std::ostream& operator << (std::ostream& os, const Creature& creature)
	{
		os << "name " << creature.name
			<< " attack " << creature.GetAttack()
			<< " defense " << creature.defense;

		return os;
	}
};

class CreatureModifier
{
	Game& game;
	Creature& creature;
public:
	explicit CreatureModifier(Game & game, Creature & creature) : game(game), creature(creature)
	{

	}

	virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier
{
	boost::signals2::connection conn;
public:
	DoubleAttackModifier(Game & game, Creature & creature) : CreatureModifier(game, creature)
	{
		conn = game.queries.connect([&](Query & q) {
			if (q.creature_name == creature.name &&
				q.argument == Query::Argument::attack)
			{
				q.result *= 2;
			}
			});
	}

	virtual ~DoubleAttackModifier()
	{
		conn.disconnect();
	}
};

int main6(int argc, char* argv)
{
	Game game;
	Creature goblin{ game, 2, 2, "Strong goblin" };

	std::cout << goblin << "\n";
	DoubleAttackModifier dam{ game, goblin };

	std::cout << goblin << "\n";
	getchar();
	return 0;
}