#include <string>
#include <boost/lexical_cast.hpp>
#include <map>
#include <iostream>
#include <fstream>
#include <gtest/gtest.h>

class Database
{
public:
	virtual int get_population(const std::string& name) = 0;
};
class SingletonDatabase : public Database
{
	SingletonDatabase()
	{
		std::cout << "Initializing database " << std::endl;

		std::ifstream ifs("capitals.txt");
		std::string s, s2;
		
		instance_count++;
		while (std::getline(ifs, s))
		{
			std::getline(ifs, s2);
			int pop = boost::lexical_cast<int>(s2);
			capitals[s] = pop;
		}
	}
	std::map<std::string, int>  capitals;
	
public:
	static int instance_count;
	SingletonDatabase(const SingletonDatabase&) = delete;
	void operator = (const SingletonDatabase&) = delete;

	static SingletonDatabase & get()
	{
		static SingletonDatabase db;
		return db;
	}

	int get_population(const std::string& name)
	{
		return capitals[name];
	}
};

int SingletonDatabase::instance_count = 0;

struct SingletonRecordFinder
{
	int total_population(std::vector< std::string >  names)
	{
		int result = 0;
		for (auto& name : names)
		{
			result += SingletonDatabase::get().get_population(name);
		}
		return result;
	}
};

class DummyDatabase : public Database
{
	std::map<std::string, int> capitals;
public:
	DummyDatabase()
	{
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		capitals["gamma"] = 3;
	}
	int get_population(const std::string& name) override
	{
		return capitals[name];
	}
};

struct ConfigurableRecordFinder
{
	explicit ConfigurableRecordFinder(Database& db) : db{ db }
	{
	}

	int total_population(std::vector<std::string> names)
	{
		int result = 0;
		for (auto& name : names)
		{
			result += db.get_population(name);
		}
		return result;
	}

	Database& db;
};
/*
TEST(DatabaseTest, IsSingletonTest)
{
	auto& db = SingletonDatabase::get();
	auto& db1 = SingletonDatabase::get();
	ASSERT_EQ(1, db.instance_count);
	ASSERT_EQ(1, db1.instance_count);
}

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
	SingletonRecordFinder rf;
	std::vector<std::string>  names{ "Seoul", "Mexico City" };
	int tp = rf.total_population(names);
	EXPECT_EQ(1750000 + 1740000, tp);
}

TEST(RecordFinderTests, DependentTotalPopulationTest)
{
	DummyDatabase db{};
	ConfigurableRecordFinder rf{ db };
	EXPECT_EQ(4, rf.total_population(
		std::vector<std::string> {"alpha", "gamma"}));
}

int main12(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}*/

