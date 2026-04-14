#include <iostream>
#include <stack>

int main() {
    // initialization
    int size;
    int* arr;
    std::cin >> size;
    arr = new int[size];
    for (int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    // 用stack来实现，从而能够实现逐个轮次判断
    std::stack<int> golemStack;
    bool flag = true;
    // 最后输出从左往右，这里就从右往左读
    for (int i = size - 1; i >= 0; --i) {

        flag = true;

        if (golemStack.empty()) {
            golemStack.push(arr[i]);
            continue;
        }

        if (arr[i] > 0) {
            if (golemStack.top() > 0) {
                golemStack.push(arr[i]);
            } else {
                while (!golemStack.empty() && golemStack.top() < 0) {
                    if (golemStack.top() + arr[i] > 0) {
                        golemStack.pop();
                        continue;
                    } 
                    
                    if (golemStack.top() + arr[i] == 0) {
                        golemStack.pop();
                        flag = false;
                        break;
                    }

                    if (golemStack.top() + arr[i] < 0) {
                        flag = false;
                        break;
                    }
                }

                if (flag) {
                    golemStack.push(arr[i]);
                }
            }
        } else {
            golemStack.push(arr[i]);
        }
    }

    if (golemStack.empty()) {
        std::cout << "Empty";
    } else {
        std::cout << golemStack.top();
        golemStack.pop();
    }

    while (!golemStack.empty()) {
        std::cout << ' ' << golemStack.top();
        golemStack.pop();
    }
}