// 基于逆波兰式的计算器
#include<iostream>
#include"stack.h"
#include<cstring>
#include<cmath>

class Calculator {
    private:
        char* expr;
        char* postExpr;
        void postfixConvert(); // 中缀式转逆波兰式
        double comp();
        double binaryComp(Stack<double>& valueStack, char op);
    public:
        Calculator(const char* expr);
        ~Calculator();
        double result();
};

Calculator::Calculator(const char* s) {
    // 构造函数
    expr = new char[std::strlen(s) + 1]; // 分配内存给中缀式字符串，多给一位存储'\0'
    postExpr =new char[2*std::strlen(s) + 1];
    std::strcpy(expr, s); 
    /*先简单地进行字符串复制，本来考虑过在构造的时候就完成错误格式
    检查，但是考虑了一下，如果在这里进行排查，后面计算的时候还要再排一次
    这样增加时间消耗，于是还是保留在后面进行排查的结构*/
}

Calculator::~Calculator() {
    delete [] expr;
    delete [] postExpr;
}

/*考虑设计方案的时候，本来是想过和课上的实现方案一致，把中缀转后缀的过程和数字运算的过程
通过优先级处理的方式进行合并，但是最后还是决定使用显示中缀转后缀与分开运算的方式。这种实现
方式相比合并的方法当然是更加低效的，但是实现的过程和思路会更见显式与完整一点*/

void Calculator::postfixConvert() {
    // 接收并将中缀式转为后缀式

    /*运行逻辑：通过与栈顶的符号进行优先级比对来判断是否压入运算符栈*/

    int idx = 0; 
    /*原始打算是用idx来重复利用空间，但是如果要在数字间加上空格就有可能导致
    初始数组超出范围，而且会导致两个index指针速度不一样出现覆盖，所以必须用
    两个不同的数组*/
    Stack<char> opStack;

    for (int i = 0; i < std::strlen(expr); i++) {
        bool flag = false; // 用于括号是否闭合的判断

        if (expr[i] == '\0') { // 到空直接终止循环
            postExpr[idx] = '\0';
            break;
        }

        if (expr[i] == ' ') continue; // 跳过空格

        if (expr[i] <= '9' && expr[i] >= '0') { // 
            while (expr[i] <= '9' && expr[i] >= '0') {
                postExpr[idx] = expr[i];
                idx++; i++;
            }
            i--;
            postExpr[idx] = ' ';
            idx++;
        } else {
            switch (expr[i]) {
                case ' ': break;

                case '(': opStack.push('('); break;

                case ')': 
                    while (!opStack.isempty()) {
                        char t = opStack.pop();
                        if (t == '(') {
                            flag = true;
                            break;
                        }
                        else {
                            postExpr[idx++] = t;
                            postExpr[idx++] = ' ';
                        }
                    }
                    if (!flag) std::cerr << "Unclosed parentheses.";
                    break;

                case '^': 
                    while (!opStack.isempty() && opStack.top() == '^') {
                        postExpr[idx++] = opStack.pop();
                        postExpr[idx++] = ' ';
                    }
                    opStack.push('^');
                    break;

                case '*': case '/':
                    while (!opStack.isempty() && (opStack.top() == '*' || opStack.top() == '/' || opStack.top() == '^')) {
                        postExpr[idx++] = opStack.pop();
                        postExpr[idx++] = ' ';
                    }
                    opStack.push(expr[i]);
                    break;

                case '+': case '-':
                    while (!opStack.isempty() && (opStack.top() == '+' || opStack.top() == '-' || opStack.top() == '*' || opStack.top() == '/' || opStack.top() == '^')) {
                        postExpr[idx++] = opStack.pop();
                        postExpr[idx++] = ' ';
                    }
                    opStack.push(expr[i]);
                    break;    
                default: std::cerr << "Unexpected token.";               
            }
        }
    }

    while (!opStack.isempty()) { // 将所有还在opStack中的运算符弹出
        postExpr[idx++] = opStack.pop();
        postExpr[idx++] = ' ';
    }

    postExpr[idx] = '\0'; // 封闭数组末尾
}

double Calculator::binaryComp(Stack<double>& valueStack, char op) {
    double fst, scd;

    if (valueStack.isempty()) {
        std::cerr << "Error, missing first operand";
        return -1;
    }
    scd = valueStack.pop();

    if (valueStack.isempty()) {
        std::cerr << "Error, missing second operand";
        return -1;
    }
    fst = valueStack.pop();

    switch (op) {
        case '+': return fst + scd;
        case '-': return fst - scd;
        case '*': return fst * scd;
        case '/': return fst / scd;
        case '^': return std::pow(fst, scd);
    }

    std::cerr << "Unexpected token.";
    return -1;
}

double Calculator::comp() {
    // 计算部分
    Stack<double> valueStack; // 数值栈，用于储存数据
    char* ptr = postExpr; // 指针

    while (*ptr != '\0') {
        
        if (*ptr == ' ') {
            ptr++;
            continue;
        }

        if (*ptr <= '9' && *ptr >= '0') {
            double val = 0;
            while (*ptr <= '9' && *ptr >= '0') {
                val = val*10 + *ptr - '0';
                ptr++;
            }
            valueStack.push(val);
        } else {
            valueStack.push(binaryComp(valueStack, *ptr));
            ptr++;
        }
    }
    
    double ans = valueStack.pop();
    if (!valueStack.isempty()) std::cerr << "Extra numbers left.";
    return ans;
}

double Calculator::result() {
    postfixConvert();
    double ans = comp();
    return ans;
}

int main() {
    char input[100];
    std::cin.getline(input, 100);
    Calculator calc(input);
    std::cout << calc.result();
    return 0;
}