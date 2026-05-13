#include <iostream>

int max(int a, int b) {
    return a > b ? a: b;
}

int binarySearch(int *a, int aSize, int *b, int bSize, int k) {
    int aLeft = 0, bLeft = 0, aRight = aSize - 1, bRight = bSize - 1;
    int aMid, bMid;
    while (aLeft <= aRight && bLeft <= bRight) {
        aMid = aLeft + (aRight - aLeft) / 2;
        bMid = bLeft + (bRight - bLeft) / 2;
        if (aMid + bMid <= k - 2) {
            if (a[aMid] > b[bMid]) {
                bLeft = bMid + 1;
            } else {
                aLeft = aMid + 1;
            }
        } else {
            if (a[aMid] > b[bMid]) {
                aRight = aMid - 1;
            } else {
                bRight = bMid - 1;
            }
        }
    }

    if (aRight < 0) {
        return b[k - 1];
    }
    if (bRight < 0) {
        return a[k - 1];
    }
    if (aRight < aLeft) {
        return max(a[aRight], b[k - aLeft - 1]);
    }
    if (bRight < bLeft) {
        return max(b[bRight], a[k - bLeft - 1]);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    int *a = new int[n];
    int *b = new int[m];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }
    int k = 0;
    for (int i = 0; i < q; ++i) {
        std::cin >> k;
        std::cout << binarySearch(a, n, b, m, k) << '\n';
    }
}
