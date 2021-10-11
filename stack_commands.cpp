/// Operations
/// -- POP
///  -- DUP
///  + or - 
/// Min int = 0
/// Max int = 20 bit
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <iostream>
#include <algorithm>

const int32_t UINT_MAX20 = 0xfffff;
const int32_t UINT_MIN20 = 0;

std::vector<std::string> extractWords(const std::string& s)
{
	std::vector<std::string> words;
	std::string word;
	std::stringstream iss(s);

	while (iss >> word)
		words.push_back(word);

	return words;
}

void throwIfEmpty(const std::string& op, const std::stack<int32_t>& numStack)
{
	if (numStack.empty())
	{
		throw std::runtime_error("Numstack is empty " + op);
	}
}

void throwLessValuesOnStack(const std::string& op, const std::stack<int32_t>& numStack)
{
	if (numStack.size() < 2)
	{
		throw std::runtime_error("Numstack has less values " + op);
	}
}

int32_t solution(std::string &  s)
{
	/// 1 2 + POP DUP
	auto ops = extractWords(s);
	std::stack<int32_t>  numStack;
	try
	{
		for (auto& op : ops)
		{
			std::transform(op.begin(), op.end(), op.begin(), ::toupper);
			if (op == "POP")
			{
				throwIfEmpty(op, numStack);
				numStack.pop();
			}
			else if (op == "DUP")
			{
				throwIfEmpty(op, numStack);
				numStack.push(numStack.top());
			}
			else if (op == "+" || op == "-")
			{
				
				throwLessValuesOnStack(op, numStack);
		
				int32_t first = numStack.top();
				numStack.pop();
				int32_t second = numStack.top();
				numStack.pop();
				int result = 0;
				if (op == "+")
				{
					result = first + second;
				}
				else
				{
					result = first - second;
				}

				if (result >= UINT_MAX20)
				{
					throw std::runtime_error(s + " Result overlow ");
				}
				else if (result < 0)
				{
					throw std::runtime_error(s + "Result undreflow ");
				}
				numStack.push(result);
			}
			else
			{
				int extract = 0;
				try
				{
					extract = std::stoi(op);
				}
				catch (const std::exception & e)
				{
					throw std::runtime_error(s + "Invalid number. String to integer conversion failed");
				}

				if (extract >= UINT_MAX20)
				{
					throw std::runtime_error(s + " Result overlow ");
				}
				else if (extract < 0)
				{
					throw std::runtime_error(s + "Result undreflow ");
				}
				numStack.push(extract);
			}
		}
		if (numStack.empty())
		{
			throw std::runtime_error(s + "Resulted in an empty stack");
		}
		return numStack.top();
	}
	catch (const std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return -1;
}

int main_stackcommands()
{
	std::string s = "1 + DUP POP";

	auto result = solution(s);
	std::cout << "Result is " << result << std::endl;
	return 0;
}