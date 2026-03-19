#include<iostream>
#include"stack.h"

int main() {
    Stack<char> s;
    std::cout << s.isempty() << std::endl;
    s.push('1');
    std::cout << s.isempty() << std::endl;
    std::cout << s.pop() << std::endl;
    std::cout << s.isempty() << std::endl;
    s.push('2');
    s.push('3');
    std::cout << s.top() << std::endl;
    std::cout << s.pop() << std::endl;
    std::cout << s.top() << std::endl;
    std::cout << s.pop() << std::endl;
}