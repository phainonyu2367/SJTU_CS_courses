#include <iostream>
#include <vector>
#include <queue>

class UndirectedGraph {
    private:
        std::vector<std::vector<int>> adj;
    public:
        UndirectedGraph(int n, int m) {
            adj.resize(n);
            int v1, v2;
            for (int i = 0; i < m; ++i) {
                std::cin >> v1 >> v2;
                adj[v1 - 1].push_back(v2);
                adj[v2 - 1].push_back(v1);
            }
        }

        int getWCC() {
            std::vector<bool> visited;
            std::queue<int> BFSQueue;
            int n = adj.size(), count = 0, top;
            visited.resize(n, false);
            for (int i = 0; i < n; ++i) {
                if (visited[i]) {
                    continue;
                }
                BFSQueue.push(i + 1);
                visited[i] = true;
                while (!BFSQueue.empty()) {
                    top = BFSQueue.front();
                    BFSQueue.pop();
                    for (int j = 0; j < adj[top - 1].size(); ++j) {
                        if (visited[adj[top - 1][j] - 1]) {
                            continue;
                        }
                        BFSQueue.push(adj[top - 1][j]);
                        visited[adj[top - 1][j] - 1] = true;
                    } 
                }
                count++;
            }
            return count;
        }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    UndirectedGraph ug(n, m);
    std::cout << ug.getWCC();
}
