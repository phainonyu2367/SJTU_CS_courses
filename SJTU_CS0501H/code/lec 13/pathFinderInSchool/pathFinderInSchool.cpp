#include <iostream>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);    
    int N, M, S, T;
    std::cin >> N >> M >> S >> T;

    if (S == T) {
        std::cout << "True";
        return 0;
    }

    int** mat = new int*[N];
    for (int i = 0; i < N; ++i) {
        mat[i] = new int[N] {0};
    }

    // building adj-matrix
    int s, t;
    for (int i = 0; i < M; ++i) {
        std::cin >> s >> t;
        mat[s - 1][t - 1] = 1;
    }

    std::stack<int> dfsStack;
    int* visited = new int[N]{0};
    dfsStack.push(S - 1);
    visited[S - 1] = 1;

    while (!dfsStack.empty()) {
        s = dfsStack.top();
        dfsStack.pop();
        for (t = 0; t < N; ++t) {
            if (mat[s][t] == 1 && visited[t] == 0) {
                if (t == T - 1) {
                    std::cout << "True";
                    return 0;
                }
                visited[t] = 1;
                dfsStack.push(t);
            }
        }
    }
    std::cout << "False";
    return 0;
}
