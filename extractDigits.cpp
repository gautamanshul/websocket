#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int32_t> extractDigits(int32_t N) {
    std::vector<int32_t> digits;
    for (int32_t x = N; x > 0; x /= 10) {
        digits.push_back(x % 10);
    }
    return digits;
}

int32_t solution(int32_t N) {
    std::vector<int> digits = extractDigits(N);
    if (digits.size() > 9)
        return -1;
    std::sort(digits.begin(), digits.end(), std::greater<int32_t>());

    int32_t result = 0;
    for (const auto& d : digits) {
        result = result * 10 + d;
    }
    return result > 100000000 ? -1 : result;
}