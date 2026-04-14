#include <iostream>
#include <queue>
#include <cmath>

struct Customer {
    int id;
    int target;
    Customer(int i = 0, int t = 0): id(i), target(t) {};
};

int queueSimu() {
    int size, target;
    std::queue<Customer*> simuQueue;
    std::cin >> size >> target;
    Customer* cur;
    int tmp;
    for (int i = 0; i < size; i++) {
        std::cin >> tmp;
        cur = new Customer(i, tmp);
        simuQueue.push(cur);
    }

    tmp = 0;

    while (true) {
        cur = simuQueue.front();
        cur->target -= 1;
        tmp += 1;

        if (target == cur->id && cur->target == 0) {
            return tmp;
        }

        simuQueue.pop();
        if (cur->target != 0) {
            simuQueue.push(cur);
        }
    }
}

int directProcess() {
    int size, target, count = 0;
    std::cin >> size >> target;
    int* ticket = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> ticket[i];
    }
    for (int i = 0; i <= target; ++i) {
        count += std::min(ticket[i], ticket[target]);
    }
    for (int i = target + 1; i < size; ++i) {
        count += std::min(ticket[i], ticket[target] - 1);
    }
    delete [] ticket;
    return count;
}

int main() {
    std::cout << directProcess();
    return 0;
}