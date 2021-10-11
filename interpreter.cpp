#include <string>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>
#include <cctype>

struct Token
{
	std::string text;
	enum Type { integer, plus, minus, lparen, rparen } type;

	Token(const Type type, const std::string& text) : type(type), text(text) {}

	friend std::ostream& operator << (std::ostream& os, const Token& token)
	{	
		return os << "'" << token.text << "'";
	}
};

std::vector<Token> lex(std::string& input)
{
	std::vector<Token> result;
	for (int i = 0; i < input.size(); ++i)
	{
		switch (input[i])
		{
		case '(':
			result.push_back(Token{ Token::lparen, "(" });
			break;
		case ')':
			result.push_back(Token{ Token::rparen, ")" });
			break;
		case '+':
			result.push_back(Token{ Token::plus, "+" });
			break;
		case '-':
			result.push_back(Token{ Token::minus, "-" });
			break;
		default:
			std::ostringstream buffer;
			buffer << input[i];
			for (int j = i + 1; j < input.size(); ++j)
			{
				if (std::isdigit(input[j]))
				{
					buffer << input[j];
					++i;
				}
				else
				{
					result.push_back(Token{ Token::integer, buffer.str() });
					break;
				}
			}
			break;
		}
	}

	return result;
}

struct Element
{
	virtual ~Element() = default;
	virtual int eval() const = 0;
};

struct Integer : Element
{
	int value;

	explicit Integer(const int value) : value(value)
	{}

	virtual int eval() const override
	{
		return value;
	}
};

struct BinaryOperation : Element
{
	enum Type { addition, subtraction } type;
	std::shared_ptr<Element> lhs, rhs;

	int eval() const override
	{
		if (type == addition)
		{
			return lhs->eval() + rhs->eval();
		}
		else
			return lhs->eval() - rhs->eval();
	}
};

std::shared_ptr<Element> parse(const std::vector<Token> & tokens)
{
	auto result = std::make_shared<BinaryOperation>();
	bool have_lhs = false;
	for (int i = 0; i < tokens.size(); ++i)
	{
		auto token = tokens[i];
		switch (token.type)
		{
		case Token::integer:
		{
			int value = boost::lexical_cast<int>(token.text);
			auto integer = std::make_shared<Integer>(value);
			if (!have_lhs)
			{
				result->lhs = integer;
				have_lhs = true;
			}
			else result->rhs = integer;
			break;
		}
		case Token::plus:
			result->type = BinaryOperation::Type::addition;
			break;
		case Token::minus:
			result->type = BinaryOperation::Type::subtraction;
			break;
		case Token::lparen:
			for (int j = i; j < tokens.size(); ++j)
			{
				if (tokens[j].type == Token::rparen)
				{
					break;
				}
				std::vector<Token> subexpression(&tokens[i + 1], &tokens[j]);
				auto element = parse(subexpression);
				if (!have_lhs)
				{
					result->lhs = element;
				}
				else result->rhs = element;
				i = j;
			}

		}
	}
	return result;
}

int main8()
{
	std::string input{ "(13-4)-(12+1)" };
	auto tokens = lex(input);
	for (auto& t : tokens)
	{
		std::cout << t;
	}

	auto result = parse(tokens);
	std::cout << input << "=" << result->eval();
	return 0;
}