#include <iostream>
#include <queue>
// classic BFS problem

int BFS(char** map, int N, int M, int entriX, int entriY) {
    // initialization for bfs
    int directionsX[4] {1, 0, -1, 0};
    int directionsY[4] {0, 1, 0, -1};
    int** visited = new int*[N];
    for (int i = 0; i < N; ++i) {
        visited[i] = new int[M]{0};
    }
    std::queue<int> positionX;
    std::queue<int> positionY;
    std::queue<int> height;
    positionX.push(entriX);
    positionY.push(entriY);
    height.push(0);
    visited[entriX][entriY] = 1;

    int curX, curY, h, x, y;
    while (!positionX.empty()) {
        curX = positionX.front();
        curY = positionY.front();
        h = height.front();
        positionX.pop();
        positionY.pop();
        height.pop();

        for (int i = 0; i < 4; ++i) {
            x = curX + directionsX[i];
            y = curY + directionsY[i];
            if (x < 0 || x >= N) {
                continue;
            }
            if (y < 0 || y >= M) {
                continue;
            }
            if (visited[x][y] == 1) {
                continue;
            }
            visited[x][y] = 1;
            switch (map[x][y]) {
                case 'A':
                    for (int i = 0; i < N; ++i) {
                        delete [] visited[i];
                    }
                    delete [] visited;
                    return h + 1;
                case '#':
                    continue;
                case '.':
                    positionX.push(x);
                    positionY.push(y);
                    height.push(h + 1);
            }
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int N, M, entriX = 0, entriY = 0;
    std::cin >> N >> M;

    char** map = new char*[N];
    for (int i = 0; i < N; ++i) {
        map[i] = new char[M];
        std::cin.ignore();
        for (int j = 0; j < M; ++j) {
            std::cin.get(map[i][j]);
            if (map[i][j] == 'S') {
                entriX = i;
                entriY = j;
            }
        }
    }

    int minTime = BFS(map, N, M, entriX, entriY);
    std::cout << minTime;
}
