#include <iostream>
#include <string>

std::string removeReplicate(const std::string& str) {
    bool modified = false;
    std::string result = str;

    do {
    modified = false;
    for (int i = 0; i < result.size() - 1; ++i) {
        if (result[i] == result[i + 1]) {
            modified = true;
            result.erase(i, 1); 
            result.erase(i, 1);
            i--;
        }

        if (result.empty()) {
            return "";
        } 
    }
    } while (modified);
    return result;
}

int main() {
    std::string str;
    std::cin >> str;
    std::cout << removeReplicate(str);
    return 0;
}