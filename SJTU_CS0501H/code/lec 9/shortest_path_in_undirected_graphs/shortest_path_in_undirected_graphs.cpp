#include <iostream>
#include <vector>
#include <queue>

struct Node {
    int value;
    Node* next;
    int height;
    Node(int v, Node* n): value(v), next(n) {};
};

class UndirectedGraph {
    private:
        std::vector<Node*> vertices;

    public:
        UndirectedGraph(const int& n, const int& m) {
            vertices.resize(n, nullptr);
            for (int i = 0; i < n; ++i) {
                vertices[i] = new Node(i + 1, nullptr);
            }
            
            int v1, v2;
            for (int i = 0; i < m; ++i) {
                std::cin >> v1 >> v2;
                vertices[v1 - 1]->next = new Node(v2, vertices[v1 - 1]->next);
                vertices[v2 - 1]->next = new Node(v1, vertices[v2 - 1]->next);
            }
        }

        int findShortestPath(const int& s, const int& t) {
            if (s == t) {
                return 0;
            }
            
            std::vector<bool> visited;
            visited.resize(vertices.size(), false);
            std::queue<Node*> BFSQueue;

            vertices[s - 1]->height = 0;
            BFSQueue.push(vertices[s - 1]);
            visited[s - 1] = true;

            Node *top, *cur;
            while (!BFSQueue.empty()) {
                top = BFSQueue.front();
                BFSQueue.pop();

                if (top->value == t) {
                    return top->height;
                }

                cur = top->next;
                while (cur != nullptr) {
                    if (!visited[cur->value - 1]) {
                        vertices[cur->value - 1]->height = top->height + 1;
                        BFSQueue.push(vertices[cur->value - 1]);
                        visited[cur->value - 1] = true;
                    }
                    cur = cur->next;
                }
            }
            return -1;
        }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    UndirectedGraph ug(n, m);
    std::cout << ug.findShortestPath(s, t);
}
