#include <iostream>
#include <vector>

class PriorityQueue {
    private:
        int* values;
        int length;
        int size;

        void resize(int newSize) {
            int* newValues = new int[newSize];
            for (int i = 0; i < size; ++i) {
                newValues[i] = values[i];
            }
            delete [] values;
            values = newValues;
            length = newSize;
        }

        void swap(int a, int b) {
            int tmp = values[a];
            values[a] = values[b];
            values[b] = tmp;
        }

        void heapifyUp(int index) {
            if (index == 0 || values[index] >= values[(index - 1) / 2]) {
                return;
            }
            swap(index, (index - 1) / 2);
            heapifyUp((index - 1) / 2);
        }

        void heapifyDown(int index) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && values[left] < values[smallest]) {
                smallest = left;
            }
            if (right < size && values[right] < values[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                swap(smallest, index);
                heapifyDown(smallest);
            }
        }

    public:
        PriorityQueue() {
            length = 32;
            size = 0;
            values = new int[length];
        }

        ~PriorityQueue() {
            delete [] values;
        }
        
        void push(int value) {
            values[size] = value;
            heapifyUp(size);
            size += 1;
            if (size == length) {
                resize(2 * length);
            }
        }

        int pop() {
            if (size == 0) {
                return -1;
            }
            int value = values[0];
            values[0] = values[size - 1];
            size -= 1;
            heapifyDown(0);
            if (length > 32 && size < length / 4) {
                resize(length / 2);
            }
            return value;
        }
};

std::vector<int> heapSort(int* values, int size) {
    std::vector<int> rank;
    PriorityQueue pq;
    for (int i = 0; i < size; ++i) {
        pq.push(values[i]);
    }
    int cur = 0;
    for (int i = 0; i < size; ++i) {
        cur = pq.pop();
        if (rank.empty() || rank.back() != cur) {
            rank.push_back(cur);
        }
    }
    return rank;
}

int find(std::vector<int> values, int value, int size) {
    for (int i = 0; i < size; ++i) {
        if (values[i] == value) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, *originalRank;
    std::cin >> n;
    originalRank = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> originalRank[i];
    }
    
    std::vector<int> rank = heapSort(originalRank, n);
    std::cout << find(rank, originalRank[0], n);
    for (int i = 1; i < n; ++i) {
        std::cout << ' ' << find(rank, originalRank[i], n);
    }
}
