#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::string cut_size(std::string & message, int K )
{
    if ( message.empty() || K <= 0 )
        return "";

	////Codility is great for testing
    /// 14
	int32_t size = std::min<int32_t>(message.length() - 1, K - 1); /// 15 size = 13

    if (static_cast<int32_t>(message.length()) > size + 1)
    {
        while (size >= 0 && message[size + 1] != ' ')
        {
            size--;
        }
    }

	while (size >=0 && message[size] == ' ')
	{
		size--;
	}

    return message.substr(0, size + 1);
}

int main_sentence_size()
{
	std::string  message{"Codility is great for testing"};
	std::string res = cut_size(message, 14);

	std::cout << res << std::endl;
    return 0;
}