#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

class Solution {
    int sAsciiCounts[256];

  public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() <= 1)
            return s.size();

        int result = 1;

        sAsciiCounts[s[0]] += 1;
        auto i = s.cbegin();
        for (auto j = i + 1; j != s.cend(); ++j) {
            while (sAsciiCounts[*j] > 0) {
                sAsciiCounts[*i] -= 1;
                ++i;
            }
            sAsciiCounts[*j] += 1;
            result = std::max(result, (int)std::distance(i, j) + 1);
        }

        return result;
    }
};