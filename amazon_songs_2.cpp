#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;
std::vector<int> IDsOfSongs(int rideDuration, std::vector<int> songDurations) {
    std::vector<int> result;
    std::unordered_map<int, std::vector<int>> songDurationToIds;
    for (int i = 0; i < songDurations.size(); ++i) {
        if (songDurationToIds.find(songDurations[i]) == songDurationToIds.end()) {
            songDurationToIds[songDurations[i]] = {};
        }
        songDurationToIds[songDurations[i]].push_back(i);
    }

    for (int i = 0; i < songDurations.size(); ++i) {
        int targetDuration = rideDuration - songDurations[i] - 30;
        if (targetDuration <= 0) {
            continue;
        }

        auto potentialSongIdsItr = songDurationToIds.find(targetDuration);
        if (potentialSongIdsItr == songDurationToIds.end()) {
            continue;
        }

        auto& potentialSongIds = potentialSongIdsItr->second;
        for (auto& j : potentialSongIds) {
            if (i != j && result.empty()) {
                result.push_back(i);
                result.push_back(j);
            }
            else if (i != j && !result.empty()
                && std::max(songDurations[i], songDurations[j]) > 
                   std::max(songDurations[result[0]], songDurations[result[1]]))
            {
                result[0] = i;
                result[1] = j;
            }
        }
    }

    return result;
}

int main_songs_2() {
    std::vector<int> result = IDsOfSongs(90, { 1, 10, 25, 35, 59 });
    if (!result.empty()) {
        std::cout << result[0] << " " << result[1] << std::endl;
    }
    return 0;
}