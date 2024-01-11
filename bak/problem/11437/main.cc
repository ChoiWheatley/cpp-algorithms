/**
 * https://www.acmicpc.net/problem/11437
 *
 * LCA
 *
 * N <= 50'000이나 돼서 N^2 공간복잡도를 자랑하는 일반 벡터 방식은... 안될듯.
 *
 * Binary Lifting 방식 (https://www.youtube.com/watch?v=dOAxrhAUIhA)을 활용해서
 * 2^k-th ancester를 저장하는 코드를 작성해보자.
 */
#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

constexpr size_t MAX_N = 50'000;
constexpr size_t LOG = 16; // ceil of log(MAX_N, 2)

static int gUp[MAX_N][LOG] = {0}; // up[v][j] = 2^j-th ancestor of v
static int gDepth[MAX_N] = {0}; // [i] 노드의 트리상에서의 깊이. 루트는 0
static bool gVisited[MAX_N] = {false};
static map<int, vector<int>> gAdjlist;

/// @brief leaf 노드에 도달할 때까지 DFS 순회하며 up, depth 전역변수를
/// 초기화한다.
/// @param a 현재 노드 번호
static void dfs(int a, int depth) {
    if (gVisited[a]) {
        return;
    }
    gVisited[a] = true;
    gDepth[a] = depth;

    for (int b : gAdjlist[a]) {
        if (gVisited[b])
            continue;
        gUp[b][0] = a; // a is parent of b
        for (size_t j = 1; j < LOG; ++j) {
            // 2^j-th ancestor 구축:
            // 나의 2^j번째 부모는 나의 2^{j-1}번째 부모의 2^{j-1}번째 부모와
            // 같다
            gUp[b][j] = gUp[gUp[b][j - 1]][j - 1];
        }
        dfs(b, depth + 1);
    }
}

/// @brief binary lifting 방식을 활용한 빠른 LCA 찾기 알고리즘
static int lca(int a, int b) {
    if (gDepth[a] < gDepth[b]) {
        std::swap(a, b);
    }
    // a와 b의 depth를 맞춰준다. 이것도 한 칸씩 올라갈 필요 없이
    // 이진수로 성큼성큼 올라가면 된다 (...)
    const int depth_diff = gDepth[a] - gDepth[b];
    for (int j = LOG - 1; j >= 0; --j) {
        if (depth_diff & (1 << j)) { // j 번째 비트가 켜져 있으면
            a = gUp[a][j];
        }
    }

    if (a == b) {
        return a;
    }

    // 공통조상 찾기 프로젝트 시작 (feat' parametric search)
    // a와 b의 공통조상을 c라고 한다면, c 이전 노드들은 전부 공통조상이 아니고
    // c의 모든 조상은 전부 공통조상이다.
    for (int j = LOG - 1; j >= 0; --j) {
        if (gUp[a][j] != gUp[b][j]) { // 공통조상이 아니면 그제서야 올라가자
            a = gUp[a][j];
            b = gUp[b][j];
        }
    }
    // last false를 찾은 셈이므로, first true는 바로 윗 조상이다.
    return gUp[a][0];
}

int main(int argc, char const *argv[]) {
    cin.sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    size_t n;
    cin >> n;

    // 1. 트리 구축. 인풋 순서가 트리의 순회 순서를 따르지 않기 때문에 별도의
    //  인접리스트를 만들어야 한다.
    while (n-- > 1) {
        int a, b;
        cin >> a >> b;

        gAdjlist[a].push_back(b);
        gAdjlist[b].push_back(a);
    }

    // 2. dfs 사용하여 up, depth 배열을 초기화한다.
    dfs(1, 0);

    // 3. M개의 정점쌍을 입력받아 두 정점의 가장 가까운 공통조상을 출력한다.
    int m;
    cin >> m;
    while (m-- > 0) {
        int a, b;
        cin >> a >> b;

        cout << lca(a, b) << "\n";
    }

    return 0;
}
