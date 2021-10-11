#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

/// Pair songs while on the bus
/// Goal is to select two songs from a list that will end exactly 30 seconds before the listener reaches their stop.
/// Task: Select the songs from the list
/// Unique id : 0 to N-1

/// If listener reaches in 10 min then songs should end by 9 min 30 seconds

/// no song twice
/// exactly 2 songs
/// If multiple pairs with same total time, select the pair with the longest song.

/// input: ride duration in seconds
/// song duration: list representing duratoin of song

//// out: List of ints returning ID's of two songs. Combined runtime should be exactly 30 seconds before rider reaches the stop.

/// rider_duration = 90 - 30
/// song_durations = { 1, 10, 25, 35, 60 };

std::vector<int> ids_of_songs(int rider_duration, std::vector<int> song_duration)
{
	std::vector<int> result;
	std::unordered_map<int, std::vector<int>> m;
	int longest_song = 0;

	for (int i = 0; i < song_duration.size(); ++i )
	{
		int duration_left = rider_duration - song_duration[i] - 30;
		/// Skip the song if the duration of the song is equal to 90  - 30

		if ( duration_left <= 0 || song_duration[i] >= rider_duration - 30 ) continue; // As we need to return a pair.
		auto itr = m.find(duration_left);
		if ( itr != m.end() )
		{
			/// Found the duration match. Add this to the list
			if (!result.empty() && std::max(song_duration[i], itr->first) > 
				std::max(song_duration[result[0]], song_duration[result[1]]) )
			{
				result[0] = i;
				for (auto& j : itr->second)
				{
					if ( i != j ) result[1] = j;
				}
			}
			else
			{
				result.push_back(i);
				for (auto& j : itr->second)
				{
					if (i != j) result.push_back(j);
				}
			}
		}
		else
		{
			m[song_duration[i]].push_back( i );
		}
	}
	return result;
}

int main_amazon_songs()
{
	int ride_duration = 90;
	std::vector<int> song_durations = { 1, 10, 25, 35, 60 };

	std::vector<int> result = ids_of_songs(ride_duration, song_durations);
	std::cout << "Selected songs are " << std::endl;
	for (auto r : result)
	{
		std::cout << "Song Id " << r << std::endl;
	}
	return 0;
}