#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string longestPalindrome(std::string s)
    {
        if (s.length() < 1) return "";
        int start = 0, end = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            int len1 = expandFromCenter(s, i, i);
            int len2 = expandFromCenter(s, i, i + 1);
            int len = std::max(len1, len2); // 1,2
            if (len > end - start ) //2
            {
                start = i - (len - 1) / 2; // 0
                end = i + len / 2; // 1
            }
        }
        return s.substr(start, end + 1 );
    }

    int expandFromCenter(const std::string& s, int left, int right)
    {
        int L = left, R = right;
        while (L >= 0 && R < s.length() && s[L] == s[R])
        {
            R++;
            L--;
        }
        return R - L - 1;
    }
};

int main_palindrome()
{
    std::string s = "bb";//"cbbd";

    Solution sl;
    auto str = sl.longestPalindrome(s);

    std::cout << str << std::endl;
    return 0;
}