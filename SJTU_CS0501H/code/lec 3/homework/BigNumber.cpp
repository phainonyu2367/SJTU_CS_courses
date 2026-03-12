#include<iostream>
#include<string>
#include<cmath>

// Phase 1: implementation of large number storage with arrays

struct BigNumber {
    int size;
    bool negative;
    int* num;
    BigNumber(int m_size, bool neg) {
        size = m_size;
        negative = neg;
        num = new int[size];
    }

    ~BigNumber() {
        delete[] num;
    }

    BigNumber(const BigNumber& other) {
        size = other.size;
        negative = other.negative;
        num = new int[size]; // 重新分配内存
        for (int i = 0; i < size; i++) {
            num[i] = other.num[i];
        }
    } 
    // 时间复杂度O(n), 空间复杂度O(1) 
};

BigNumber parseNum(std::string num);

BigNumber readNum() {
    std::string num;
    std::cin >> num;
    BigNumber bignum = parseNum(num);
    return bignum;
}
// 时间复杂度O(n), 空间复杂度O(1) 

BigNumber parseNum(std::string num) {
    int size; bool neg;
    switch (num[0]) {
        case ('-'): size = num.size() - 1; neg = true; break;
        case ('+'): size = num.size() - 1; neg = false; break;
        default: size = num.size(); neg = false;
    }
    
    BigNumber bignum(size, neg);
    for (int idx = 0; idx < size; idx++) {// loop size times
        // 倒序接收字符串中的数字
        int i = num[idx + num.size() - size] - '0';
        if (i > 9 || i < 0) throw "Invalid value";
        bignum.num[idx] = i;
    }  

    return bignum;
}
// 时间复杂度O(n), 空间复杂度O(1) 

void printNum(const BigNumber& num) {
    if (num.negative) std::cout << '-';
    bool flag = true;
    for (int i = 0; i < num.size; i++) {
        if (flag) {
            if ((i == num.size - 1) && num.num[i] == 0) {
                std::cout << 0 << std::endl;
                return;
            }
            if (num.num[i] == 0) continue;
            else flag = false;
        }

        std::cout << num.num[i];
    }
    std::cout << std::endl;
}
// 时间复杂度O(n), 空间复杂度O(1) 

// phase 2: main function for testing

BigNumber bigSum(const BigNumber& n1, const BigNumber& n2);

int main() {
    // testing
    BigNumber num1 = readNum();
    BigNumber num2 = readNum();
    printNum(num1); printNum(num2);
    BigNumber ans = bigSum(num1, num2);
    printNum(ans);
    return 0;

    // test case 1:
    // 217284 + 776382
    // target: 993666
    // actual output: 993666

    // test case 2:
    // 1 + 999999999999999999999999999999
    // target: 1000000000000000000000000000000
    // actual output: 1000000000000000000000000000000

    // test case 3:
    // -1000 + 937
    // target: 63
    // actual output: 63

    // test case 4:
    // -50 + 50
    // target: 0
    // actual output: 0

    // ------- all test cases pass
}

// phase 3: implementation of the sum(core function)

// helper method
int absCompare(const BigNumber& n1, const BigNumber& n2) {
    if (n1.size > n2.size) return 1;
    

    if (n1.size < n2.size) return -1;

    for (int i = 0; i < n1.size; i++) {
        if (n1.num[i] > n2.num[i]) return 1;
        if (n1.num[i] < n2.num[i]) return -1;
    }
    return 0;
}
// 时间复杂度O(n), 空间复杂度O(1) 

void minus(int* ans, const BigNumber& n1, const BigNumber& n2) {
    int maxsize = n1.size;
    int minsize = n2.size;
    int temp, carry = 0;

    for (int i = 0; i < minsize; i++) {
        temp = n1.num[n1.size - 1 - i] - n2.num[n2.size - 1 - i] + carry;
        if (temp < 0) {
            carry = -1;
            ans[maxsize - i] = 10 + temp;
        } else {
            carry = 0;
            ans[maxsize - i] = temp;
        }
    }

    for (int i = minsize; i < maxsize; i++) {
        temp = n1.num[n1.size - 1 - i] + carry;
        if (temp < 0) {
            carry = -1;
            ans[maxsize - i] = 10 + temp;
        } else {
            carry = 0;
            ans[maxsize - i] = temp;
        }
    }

    ans[0] = carry;
}
// 时间复杂度O(n), 空间复杂度O(1) 

void add(int* ans, const BigNumber& n1, const BigNumber& n2) {
    int maxsize = n1.size;  // 为了可读性保留的辅助变量，当然，不影响空间复杂度
    int minsize = n2.size;
    int temp, carry = 0;

    for (int i = 0; i < minsize; i++) {
        temp = n1.num[n1.size - 1 - i] + n2.num[n2.size - 1 - i] + carry;
        carry = temp / 10;
        ans[maxsize - i] = temp % 10;
    }

    for (int i = minsize; i < maxsize; i++) {
        temp = n1.num[n1.size - 1 - i] + carry;
        carry = temp / 10;
        ans[maxsize - i] = temp % 10;
    }

    ans[0] = carry;
}
// 时间复杂度O(n), 空间复杂度O(1) 

BigNumber bigSum(const BigNumber& n1, const BigNumber& n2) {
    bool neg;
    int comp = absCompare(n1, n2);
    int maxsize = std::max(n1.size, n2.size);
    const BigNumber* max = nullptr;
    const BigNumber* min = nullptr;

    if (comp == 1) {
        neg = n1.negative;
        max = &n1;
        min = &n2;
    }
    else if (comp == -1) {
        neg = n2.negative;
        max = &n2;
        min = &n1;    
    }
    else if (comp == 0) {
        neg = !(n1.negative || n2.negative);
        max = &n1;
        min = &n2;    
    }

    BigNumber ans(maxsize + 1, neg);
    
    if (n1.negative == n2.negative) {
        add(ans.num, *max, *min);
    } else {
        minus(ans.num, *max, *min);
    }

    return ans;
}

// 调用了时间复杂度为O(n)的辅助方法，其余的过程时间复杂度均为O(1)
// 中途创建了ans用于储存答案，其空间复杂度为O(n)，其余均为常数级
// 时间复杂度O(n), 空间复杂度O(n) 