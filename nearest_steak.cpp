#include <vector>
#include <queue>
#include <iostream>
/// total steak houses int N
// pair of x and y coordinate
// numSteakHouses 
// Return list<std::pair<int,int> >

struct loc {
	int x, y, distance;
	loc(int x, int y, int distance) : x(x), y(y), distance(distance) {};
};
auto cmp = [](const loc & x, const loc & y ) {
	return x.distance > y.distance;
};
std::vector<std::pair<int, int>> nearestXsteakHouses(int totalSteakHouses, int** allLocations, int numSteakhouses)
{
	std::priority_queue<loc,std::vector<loc>, decltype(cmp)> pq(cmp);
	for (int i = 0; i < totalSteakHouses; ++i)
	{
		/// Calculate the x2 + y2 distance
		int x = allLocations[i][0];
		int y = allLocations[i][1];

		int distance = x * x + y * y;
		std::cout << "x " << x << "y " << y << "dist "<< distance << std::endl;
		loc l{ x,y,distance };
		pq.push(l);

	}

	std::vector<std::pair<int, int>> locations;

	int i = 0;
	while (!pq.empty() && i < numSteakhouses)
	{
		locations.push_back({ pq.top().x, pq.top().y });
		pq.pop();
		++i;
	}
	return locations;
}

int main_steakhouse()
{
	int t = 3;
	int** allLocations;
	allLocations = new int* [6];
	for (int i = 0; i < 3; ++i)
	{
		allLocations[i] = new int[2];
	}
	allLocations[0][0] = 1;
	allLocations[0][1] = 2;
	allLocations[1][0] = 3;
	allLocations[1][1] = 4;
	allLocations[2][0] = 1;
	allLocations[2][1] = -1;

	int num = 2;

	std::vector<std::pair<int, int>> res = nearestXsteakHouses(3, allLocations, num);
	std::for_each(res.begin(), res.end(), [](auto & el) {
		std::cout << "x is " << el.first << "y is " << el.second << std::endl;
		});
	return 0;
}