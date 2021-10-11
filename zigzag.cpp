#include <string>
#include <vector>
#include <iostream>

class zigzag {
public:
    std::string convert(std::string s, int numRows) {
        std::vector<std::vector<char>> output;
        output.resize(numRows);
        int selector = 0, index = -1;
        for (int i = 0; i < s.length(); )
        {

            if (index != numRows)
            {
                while (index < numRows - 1 && i < s.length() )
                {
                    ++index;
                    output[index].push_back(s[i++]);
                }
            }

            if (index == numRows - 1)
            {
                index--;
                while (index > 0 && i < s.length())
                {
                    output[index].push_back(s[i++]);
                    --index;
                    if (index == 0) {
                        output[index].push_back(s[i++]);
                        break;
                    }
                }
            }
        }

        std::string  out;
        for (auto& v : output)
        {
            for (auto& c : v)
            {
                out += c;
            }
        }

        return out;
    }
};


int main_zigzag()
{
    std::string str{ "PAYPALISHIRING" };
    zigzag z;
    auto res = z.convert(str, 3);

    std::cout << res << std::endl;
    return 0;
}