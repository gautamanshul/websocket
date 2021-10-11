#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <unordered_map>


template <typename Collection>
auto getIndex(Collection & collection)
{
	return [&collection](const auto& iterator)
	{
		return std::distance(begin(collection), iterator);
	};
}

class Solution
{
public:
	std::vector<int> twoSum(std::vector<int>& nums, int target) {
		std::unordered_map<int, int>  m;

		const auto index = getIndex(nums);
		for( auto itr1 = begin(nums); itr1 != end(nums); ++itr1)
		{
			auto itr2 = m.find(target - *itr1);
			if (itr2 != m.end())
			{
				return std::vector<int>{ itr2->second, *itr1 };
			}
			else
			{
				m[*itr1] = index(itr1);
			}
		}

		return std::vector<int>();
	}
};

int main23()
{
	Solution s;
	std::vector<int> nums{2, 7, 11, 15};

	auto v = s.twoSum(nums, 9);
	for (const auto itr : v)
	{
		std::cout << "iterator "<< itr << std::endl;
	}
	getchar();
	return 0;
}