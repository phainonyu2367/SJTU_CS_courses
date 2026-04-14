#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;
    
    std::vector<int> g(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> g[i];
    }

    // left 充当栈顶指针，g[0..left-1] 就是栈内容
    int left = 0;
    for (int right = 0; right < n; ++right) {
        bool alive = true;
        // 碰撞条件：栈顶向右(>0) 且 当前向左(<0)
        while (alive && left > 0 && g[left - 1] > 0 && g[right] < 0) {
            if (g[left - 1] < -g[right]) {
                left--;            // 栈顶被消灭，继续比
            } else if (g[left - 1] == -g[right]) {
                left--;            // 同归于尽
                alive = false;
            } else {
                alive = false;     // 当前被消灭
            }
        }
        if (alive) {
            g[left++] = g[right];  // 入栈
        }
    }

    // 输出
    if (left == 0) {
        std::cout << "Empty";
    } else {
        for (int i = 0; i < left; ++i) {
            std::cout << g[i] << (i == left - 1 ? "" : " ");
        }
    }

    return 0;
}
