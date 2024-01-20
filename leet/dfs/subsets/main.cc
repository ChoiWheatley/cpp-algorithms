#include <vector>

using namespace std;

class Solution {
    using Iter = vector<int>::iterator;
    vector<vector<int>> result;

    void dfs(vector<int> &path, Iter numsBegin, Iter numsEnd) {
        result.push_back(path);

        for (Iter itr = numsBegin; itr != numsEnd; ++itr) {
            path.push_back(*itr);
            dfs(path, itr + 1, numsEnd);
            path.pop_back();
        }
    }

  public:
    vector<vector<int>> subsets(vector<int> &nums) {
        vector<int> path;
        dfs(path, nums.begin(), nums.end());
        return std::move(result);
    }
};

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
