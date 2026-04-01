#include <iostream>
#include <vector>
#include <cmath>

/*这道题当然数组是最优解*/

int main() {
    int size = 0;
    std::cin >> size;

    if (size == 0) return 0;

    std::vector<int> tree;
    tree.resize(size, 0);

    int val, left, right;

    for (int i = 0; i < size; i++) {
        std::cin >> val >> left >> right;
        if (tree[i] == 0) {
            tree[i] = i + 1;
        }

        if (left != 0 && 2 * i + 1 < size)
            tree[2 * i + 1] = left;
        if (right != 0 && 2 * i + 2 < size)
            tree[2 * i + 2] = right;
    }
    
    for (int i = 0; i < size - 1; i++) {
        // i+1 是 1-indexed 位置，判断它是否不是某层最后一个节点
        if (((i + 2) & (i + 1)) != 0) {
            std::cout << i + 2 << std::endl;
        } else {
            std::cout << 0 << std::endl;
        }
    }
    std::cout << 0 << std::endl;
}