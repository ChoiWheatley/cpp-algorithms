/**
 * https://www.acmicpc.net/problem/5052
 * trie를 구축하면서 어떤 번호가 다른 번호의 접두어인 경우 False를 리턴하고,
 * 아닌 경우 True를 리턴하세요
 *
 * 사람들이 왜 다들 길이를 기준으로 정렬을 하나 봤더니 길이가 긴 놈 부터
 * 트라이를 만들어가면 일관성 검사를 순서대로 할 수 없었기 때문이었다.
 *
 * 정렬하지 않고 그대로 Trie 노드를 만들고 생성된 노드의 포인터를 벡터에 저장한
 * 뒤에 일관성 체크를 수행하는 방법으로 풀었다.
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Trie {
    Trie *children[10];
    bool end = false;
};

constexpr size_t POOL_SIZE = 100'001;
constexpr size_t MAX_N = 10'000;

static Trie gPool[POOL_SIZE];
static size_t gTop = 0;

Trie *new_trie() { return &gPool[gTop++]; }
void clear_trie() {
    for (size_t i = 0; i < POOL_SIZE; ++i) {
        gPool[i] = Trie{};
    }
    gTop = 0;
}

int main(int argc, char const *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    auto trie_traces = vector<vector<Trie *>>();
    while (t-- > 0) {
        clear_trie();
        trie_traces.clear();

        Trie *root = new_trie();
        auto trie_trace = vector<Trie *>();
        int n;

        cin >> n;

        while (n-- > 0) {
            string number;
            Trie *cur = root;

            cin >> number;

            for (char c : number) {
                auto index = static_cast<size_t>(c - '0');
                if (!cur->children[index]) {
                    cur->children[index] = new Trie();
                }
                if (cur->children[index]->end) {
                    goto INCONSISTENT;
                }
                trie_trace.push_back(cur->children[index]);
                cur = cur->children[index];
            }
            trie_traces.push_back(std::move(trie_trace));
            cur->end = true;
        }

        // 일관성 체크를 실시한다
        for (const auto &trace : trie_traces) {
            for (auto it = trace.cbegin(); it != trace.cend() - 1; ++it) {
                // 마지막 노드를 제외한 놈들은 전부 end = false여야 한다.
                if ((*it)->end) {
                    goto INCONSISTENT;
                }
            }
        }

        cout << "YES\n";
        continue;
    INCONSISTENT:
        cout << "NO\n";
        while (n-- > 0) { // 남은 인풋을 소진
            string fallthrough;
            cin >> fallthrough;
        }
    }

    return 0;
}
