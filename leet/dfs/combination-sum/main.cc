#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> mAnswer;

    void dfs(int target, vector<int> &traversal,
             vector<int>::iterator cand_begin, vector<int>::iterator cand_end) {

        // 중단조건
        if (target == 0) {
            mAnswer.push_back(traversal); // copy
            return;
        }
        if (target < 0) {
            return;
        }
        if (mAnswer.size() >= 150) {
            // 문제 조건에 따라
            return;
        }

        for (auto &iter = cand_begin; iter != cand_end; ++iter) {
            const char &c = *iter;

            /*
            if (target % c == 0) {
                // 굳이 leaf노드까지 방문할 필요가 없음
                size_t cnt = target / c;
                auto answer = vector<int>(traversal); // copy
                answer.insert(answer.end(), cnt, c); // [c] * cnt를 append
                mAnswer.push_back(std::move(answer));
                continue;
            }
            */
            traversal.push_back(c);
            dfs(target - c, traversal, iter, cand_end);
            traversal.pop_back();
        }
    }

  public:
    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        // sort descending order
        std::sort(candidates.begin(), candidates.end(), std::greater<int>());

        vector<int> traversal;
        dfs(target, traversal, candidates.begin(), candidates.end());

        return std::move(mAnswer);
    }
};

int main(int argc, char const *argv[]) {
    /* code */
    return 0;
}
