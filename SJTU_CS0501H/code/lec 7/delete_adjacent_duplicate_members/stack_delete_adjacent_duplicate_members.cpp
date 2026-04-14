#include <iostream>
#include <string>
#include <stack>

void removeReplicate(const std::string& str) {
    char cur;
    std::stack<char> result;
    for (int i = str.size() - 1; i >= 0; --i) {
        cur =  str[i];

        if (result.empty()) {
            result.push(cur);
            continue;
        }

        if (result.top() == cur) {
            result.pop();
        } else {
            result.push(cur);
        }
    }

    while (!result.empty()) {
        std::cout << result.top();
        result.pop();
    }
}

int main() {
    std::string str;
    std::cin >> str;
    removeReplicate(str);
    return 0;
}