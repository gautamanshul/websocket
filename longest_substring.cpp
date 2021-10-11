#include <string>
#include <iostream>
#include <vector>

class long_substring {
public:
    int lengthOfLongestSubstring(std::string s) {
        int longest = 0;
        int stopped = 0;
        if (s.size()) longest = 1;
        for (int i = 1; i < s.size() && stopped < s.size(); )
        {
            // Check if next alphabet is same as the one held previously
            bool found = false;
            
            for (int j = !stopped ? i : stopped; j < s.size(); ++j)
            {
                for (int k = j - 1; k >= i - 1 && j < s.size(); k--)
                {
                    if (s[j] != s[k])
                    {
                        longest = j - k + 1 > longest ? j - k + 1 : longest;
                    }
                    else
                    {
                        int l = j + 1;
                        while (i++ < j)
                        {
                            ++l;
                            if (l < s.size() && s[i] == s[l]) continue;
                            else break;
                        }
                        stopped = l;
                        found = true;
                        break;
                    }
                }
                if (found)
                    break;
                else if (j + 1 == s.size())
                {
                    ++i;
                }
            }
        }

        return longest;
    }
};

int main_longest()
{
    long_substring lss;
    int length = 0;// = lss.lengthOfLongestSubstring("abcabcbb");
    length = lss.lengthOfLongestSubstring("au");
    std::cout << "Completed length =" << length << std::endl;

    getchar();
    return 0;
}