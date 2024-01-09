#include <algorithm>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <utility>

using namespace std;

using Dict = unordered_map<string, vector<string>>;

class Solution {
  public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        Dict dict;
        string tmp_sorted;
        vector<vector<string>> ret;

        // 정렬 후 사전에 추가
        for (const auto &s : strs) {
            tmp_sorted.clear();
            std::copy(s.cbegin(), s.cend(), std::back_inserter(tmp_sorted));
            std::sort(tmp_sorted.begin(), tmp_sorted.end());
            dict[tmp_sorted].push_back(s);
        }

        // 사전 각각의 리스트를 벡터에 담아 리턴
        for (auto &bucket : dict) {
            // map value를 move할 수도 있구나
            ret.push_back(std::move(bucket.second));
        }

        return ret;
    }
};