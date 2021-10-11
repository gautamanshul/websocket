#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>

class String
{
	std::string s;
public:
	String(const std::string & s) : s(s) {}
	 
	String to_lower() const
	{
		std::string str(s);
		boost::to_lower(str);
		return { str };
	}

	std::vector<std::string> split(const std::string & delimiter = " " )
	{
		std::vector<std::string> ss;
		boost::split(ss, s, boost::is_any_of(delimiter), boost::algorithm::token_compress_on);
		return ss;
	}
};

int main_adapter()
{
	String s{ "Hello   world" };
	auto parts = s.to_lower().split();
	for (const auto& p : parts)
	{
		std::cout << "<" << p << ">" << std::endl;
	}
	return 0;
}