#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>

struct Expression
{
	virtual double eval() const = 0;
	virtual void collect(std::vector<double> &) const = 0;
};

struct Literal : Expression
{
	double value;

	explicit Literal(const double value) : value(value)
	{}

	double eval() const override
	{
		return value;
	}

	void collect(std::vector<double>& collection) const override
	{
		collection.push_back(value);
	}
};

struct AdditionExpression : Expression
{
	std::shared_ptr<Expression> left, right;

	explicit AdditionExpression(const std::shared_ptr<Expression> & left, const std::shared_ptr<Expression> & right) : 
		left{left}, right{right}
	{}

	double eval() const override
	{
		return left->eval() + right->eval();
	}

	void collect(std::vector<double>& collection) const override
	{
		left->collect(collection);
		right->collect(collection);
	}
};


int main_comp(int ac, char* argv[])
{
	AdditionExpression sum{
		std::make_shared<Literal>(2),
		std::make_shared<AdditionExpression>(
			std::make_shared<Literal>(3),
			std::make_shared<Literal>(4)
		)
	};

	std::cout << sum.eval() << std::endl;
	std::vector<double>  collection;
	sum.collect(collection);

	double total = 0;
	for (auto x : collection)
	{
		total += x;
	}

	boost::accumulators::accumulator_set<double, boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
	for (auto x : collection) acc(x);
	std::cout << "mean is " << boost::accumulators::mean(acc) << std::endl;

	getchar();
	return 0;
}