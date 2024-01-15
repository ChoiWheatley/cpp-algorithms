/**
 * BFS 순회를 돌면서 도달한 지점 (i, j) visited 체크
 */
#include <deque>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

constexpr char D = 'D';
constexpr char R = 'R';
constexpr char G = 'G';
constexpr int DELTAS[] = {-1, 0, 1, 0}; // (i, (i + 1) % 4)
constexpr size_t MAX_BOARD = 100;
constexpr int INF = 1 << 30;

static bool visited[MAX_BOARD][MAX_BOARD];
static bool dont_go[MAX_BOARD][MAX_BOARD]; // 이미 가망이 없는 위치들을 저장함

/// @brief i, j방향으로 갈 수 있는지
bool can_go(int i, int j, const vector<string> &board) {
    size_t N = board.size();
    size_t M = board[0].size();

    if (i < 0 || i >= N || j < 0 || j >= M) {
        return false;
    }
    char sample = board[i][j];
    if (sample == D) {
        return false;
    }
    return true;
}

static int g_depths[MAX_BOARD]
                   [MAX_BOARD]; // BFS 탐색 시 해당 인덱스에 도달하는 최소비용

int bfs(int i, int j, const vector<string> &board) {
    const size_t N = board.size();
    const size_t M = board[0].size();

    auto q = deque<pair<int, int>>{make_pair(i, j)};
    visited[i][j] = true;

    while (!q.empty()) {
        auto [curi, curj] = q.front();
        q.pop_front();
        const int curdepth = g_depths[curi][curj];

        if (curi < 0 || curi >= N || curj < 0 || curj >= M) {
            // nonsense
            continue;
        }

        for (size_t dii = 0; dii < 4; ++dii) {
            size_t dji = (dii + 1) % 4;
            int di = DELTAS[dii];
            int dj = DELTAS[dji];
            int tmpi = curi;
            int tmpj = curj;


            // 미끄러지는 코드
            while (can_go(tmpi + di, tmpj + dj, board)) {
                tmpi += di;
                tmpj += dj;
            }

            cout << "(i, j): (" << tmpi << ", " << tmpj << ")\n";

            if (visited[tmpi][tmpj]) {
                // 이미 방문했음
                continue;
            }

            visited[tmpi][tmpj] = true;
            g_depths[tmpi][tmpj] = curdepth + 1;

            if (board[tmpi][tmpj] == G) {
                return g_depths[tmpi][tmpj];
            }
            q.push_back(make_pair(tmpi, tmpj));
        }
    }

    return INF;
}

int solution(vector<string> board) {
    size_t N = board.size();
    size_t M = board[0].size();
    // cout << N << ", " << M << "\n";
    // R 위치를 찾는다
    int ri = -1;
    int rj = -1;
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            if (board[i][j] == R) {
                ri = i;
                rj = j;
                goto DO;
            }
        }
    }
DO:
    if (ri < 0 || rj < 0) {
        // something is wrong
        return -2;
    }
    int res = bfs(ri, rj, board);
    return res == INF ? -1 : res;
}

int main(void) {
    int result =
        solution({"...D..R", ".D.G...", "....D.D", "D....D.", "..D...."});
    cout << "RESULT: " << result << endl;
    return 0;
}
