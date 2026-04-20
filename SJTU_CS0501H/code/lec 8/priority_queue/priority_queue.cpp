#include <iostream>
#include <vector>

class PriorityQueue {
    private:
        std::vector<int> minBinHeap;
        int size;
        int min(int a, int b) {
            if (a >= b) {
                return b;
            }
            return a;
        }
    public:
        PriorityQueue() {
            minBinHeap.resize(10, 0);
            size = 0;
        }

        void push(int x) {
            if (size == minBinHeap.capacity()) {
                minBinHeap.resize(2 * size);
            }
            minBinHeap[size] = x;
            int idx = size++;
            while (idx > 0 && minBinHeap[(idx - 1) / 2] > x) {
                minBinHeap[idx] = minBinHeap[(idx - 1) / 2];
                minBinHeap[(idx - 1)  / 2] = x;
                --idx /= 2;
            }
        }

        int pop() {
            int minimum = minBinHeap[0];
            minBinHeap[0] = minBinHeap[--size];
            int cur = 0;
            while (2 * cur + 1 < size && minBinHeap[cur] > min(minBinHeap[2 * cur + 1], minBinHeap[2 * cur + 2])) {
                if (2 * cur + 2 >= size && minBinHeap[2 * cur + 1] >= minBinHeap[cur]) {
                    return minimum;
                }
                
                if (minBinHeap[2 * cur + 1] < minBinHeap[2 * cur + 2]) {
                    minBinHeap[cur] = minBinHeap[2 * cur + 1];
                    minBinHeap[2 * cur + 1] = minBinHeap[size];
                    cur = 2 * cur + 1;
                } else {
                    minBinHeap[cur] = minBinHeap[2 * cur + 2];
                    minBinHeap[2 * cur  + 2] = minBinHeap[size];
                    cur = 2 * cur + 2;
                }
            }
            return minimum;
        }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    PriorityQueue pq;
    int execTurn, action, val;
    std::cin >> execTurn;
    for (int i = 0; i < execTurn; ++i) {
        std::cin >> action;
        switch (action) {
            case 1:
                std::cin >> val;
                pq.push(val);
                break;
            case 2:
                std::cout << pq.pop() << std::endl;
                break;
        }
    }
}
