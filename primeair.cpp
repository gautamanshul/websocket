#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>


/*class less_than
{
public:
	template <typename  T1 = std::pair<int, int>, typename T2 = std::pair<int, int>>
	bool operator () (T1 const & l, T2 const & r) const
	{
		return std::get<1>(l) < std::get<1>(r);
	}
};*/

class less_than
{
public:
	bool operator () (const std::pair<int, int>& l, const std::pair<int, int>& r)
	{
		return l.second < r.second;
	}

	bool operator () (const std::pair<int, int>& l, const int r)
	{
		return l.second < r;
	}


	bool operator () (const int l, const std::pair<int, int>& r)
	{
		return l < r.second;
	}
};

std::vector<std::pair<int, int>> optimal_utilization(
	int max_operating_travel_dist,
	std::vector<std::pair<int, int>> forward_shipping_route_list,
	std::vector<std::pair<int, int>> return_shipping_route_list
)
{
	std::vector < std::pair<int, int> > result;
	auto cmp = [](auto l, auto r) {
		return l.second < r.second;
	};
	std::sort(forward_shipping_route_list.begin(), forward_shipping_route_list.end(), cmp);
	std::sort(return_shipping_route_list.begin(), return_shipping_route_list.end(), cmp);

	int best_distance = 0;
	for (auto & f: forward_shipping_route_list)
	{
		if (std::get<1>(f) >= max_operating_travel_dist) continue;

		// get the remaining distance and find the lowest router with weight less than or equal to it in return route list
		int remaining_distance = max_operating_travel_dist - std::get<1>(f);

		// Find the lower bound iterator in the reverse route list >= remaining distance
		auto itr = std::lower_bound(return_shipping_route_list.begin(), return_shipping_route_list.end(), remaining_distance, less_than());

		// if the iterator is == to end of the list, decrement iterator to the last iterator
		if (itr == return_shipping_route_list.end()) --itr;

		/// Loop until all pairs are identified
		while (itr != return_shipping_route_list.begin())
		{
			/// Calculate the total distance
			int total_distance = std::get<1>(f) + itr->second;
			
			/// The total distance can be greater than the best distance and less than the max operating distance.
			/// Add this pair to the vector.
			if (total_distance > best_distance&& total_distance <= max_operating_travel_dist)
			{
				/// Clear the result as we found a better pair
				result.clear();
				result.emplace_back(std::get<0>(f), std::get<0>(*itr));
				best_distance = total_distance;
 			}
			else if (total_distance == best_distance)
			{
				/// Add to the list of best distances
				result.emplace_back(std::get<0>(f), std::get<0>(*itr));
			}
			itr--;
		}

		/// Calculate the total distance
		int total_distance = std::get<1>(f) + itr->second;

		/// The total distance can be greater than the best distance and less than the max operating distance.
		/// Add this pair to the vector.
		if (total_distance > best_distance&& total_distance <= max_operating_travel_dist)
		{
			/// Clear the result as we found a better pair
			result.clear();
			result.emplace_back(std::get<0>(f), std::get<0>(*itr));
			best_distance = total_distance;
		}
		else if (total_distance == best_distance)
		{
			/// Add to the list of best distances
			result.emplace_back(std::get<0>(f), std::get<0>(*itr));
		}

	}
	return result;	
}


int main_amazon_primeair() {
	/*std::vector<std::pair<int, int>> forwardRoutingList = { {1, 8}, {2, 7}, {3, 14} };
	std::vector<std::pair<int, int>> returnRoutingList = { {1, 5}, {2, 10}, {3, 14} };
*/
std::vector<std::pair<int, int>> forwardRoutingList = { { 1, 3000 },{ 2, 5000 },{ 3, 7000 }, {4, 10000} };
std::vector<std::pair<int, int>> returnRoutingList = { { 1, 2000 },{ 2, 3000 },{ 3, 4000 }, {4, 5000} };

	/*std::vector<std::pair<int, int>> forwardRoutingList = { { 1, 2000 },{ 2, 4000 },{ 3, 6000 } };
	std::vector<std::pair<int, int>> returnRoutingList = { { 1, 2000 } };*/

	std::vector<std::pair<int, int>> result = optimal_utilization(10000, forwardRoutingList, returnRoutingList);
	std::cout << "Best pair are " << std::endl;
	for (auto r : result)
	{
		std::cout << std::get<0>(r) << " " << std::get<1>(r) << std::endl;
	}
	getchar();
	return 0;
}