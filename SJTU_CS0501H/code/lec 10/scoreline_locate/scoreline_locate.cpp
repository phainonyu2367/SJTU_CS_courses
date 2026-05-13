#include <iostream>

int binarySearchScoreLine(int query, const int* scores, int size) {
    int left = 0, right = size - 1, mid;
    if (scores[right] < query) {
        return 0;
    }
    while (left < right) {
        mid = left + (right - left) / 2;
        if (scores[mid] < query) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left + 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    int* scores = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> scores[i];
    }

    int query;
    for (int i = 0; i < q; ++i)  {
        std::cin >> query;
        std::cout << binarySearchScoreLine(query, scores, n) << '\n';
    }
}
