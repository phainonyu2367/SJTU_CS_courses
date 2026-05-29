#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid1(m, vector<int>(n));
    vector<vector<int>> grid2(m, vector<int>(n));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid1[i][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid2[i][j];
        }
    }

    vector<vector<int>> vis(m, vector<int>(n, 0));
    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    int ans = 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid2[i][j] == 0 || vis[i][j]) {
                continue;
            }

            queue<pair<int, int>> q;
            q.push({i, j});
            vis[i][j] = 1;
            bool isSubIsland = true;

            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();

                if (grid1[x][y] == 0) {
                    isSubIsland = false;
                }

                for (int k = 0; k < 4; ++k) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n) {
                        continue;
                    }
                    if (grid2[nx][ny] == 0 || vis[nx][ny]) {
                        continue;
                    }
                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }

            if (isSubIsland) {
                ++ans;
            }
        }
    }

    cout << ans;
    return 0;
}
