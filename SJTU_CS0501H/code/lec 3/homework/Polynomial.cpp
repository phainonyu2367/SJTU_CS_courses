#include<iostream>

// 已经写了封装好的链表结构，但是封装好的链表结构在这题里面不太使用
// 而且我有一些细节没有想好怎么处理，所以就用裸链表了

// phase 1: essential SLList component
struct Node {
    double coef;
    int exp;
    Node* next;
    Node(double c, int e, Node* n): coef(c), exp(e), next(n){};
};

class SLList {
    // simplified version of SLList
    public:
        Node* head;
        Node* tail;

        SLList() {
            head = new Node(-1, -1, nullptr);
            tail = head;
        }

        void addLast(double c, int e) {
            if (c == 0) return;
            tail->next = new Node(c, e, nullptr);
            tail = tail->next;
        }

        ~SLList() {
            Node* cur; Node* temp;
            cur = temp = head;
            while (cur != nullptr) {
                cur = cur->next;
                delete temp;
                temp = cur;
            }
        }

        SLList(const SLList& lst) {
            head = new Node(0, -1, nullptr);
            tail = head;
            Node* cur = lst.head->next;
            while (cur != nullptr) {
                this->addLast(cur->coef, cur->exp);
                cur = cur->next;
            }
        }

        SLList& operator=(const SLList& lst) {

            if (this == &lst) return *this; // 自赋值检查

            // 清理旧数据
            Node* cur = head->next;
            while (cur != nullptr) {
                Node* temp = cur;
                cur = cur->next;
                delete temp;
            }
            head->next = nullptr;
            tail = head;

            cur = lst.head->next;
            while (cur != nullptr) {
                this->addLast(cur->coef, cur->exp);
                cur = cur->next;
            }
            return *this;
        }
};

// phase 2: test & main helper method
void dispList(SLList& lst) {
    Node* cur = lst.head->next;
    if (cur == nullptr) std::cout << 0 << std::endl;
    std::cout << cur->coef << "x^" << cur->exp;
    cur = cur->next;
    while (cur != nullptr) {
        std::cout << '+' << cur->coef << "x^" << cur->exp;
        cur = cur->next;
    }
    std::cout << std::endl;
}

SLList polySum(SLList& lst1, SLList& lst2);

int main() {
    // Test function for the method
    SLList l1, l2;
    l1.addLast(2, 8);
    l1.addLast(0, 5);
    l1.addLast(1, 4);
    l1.addLast(2, 2);

    l2.addLast(1, 7);
    l2.addLast(3, 4);
    l2.addLast(1, 2);
    l2.addLast(1, 0);

    dispList(l1);
    dispList(l2);

    SLList ans = polySum(l1, l2);
    dispList(ans);
}

// phase 3: implementation of the polySum()

SLList polySum(SLList& lst1, SLList& lst2) {
    SLList ans;
    Node* ptr1; Node* ptr2;
    ptr1 = lst1.head->next; ptr2 = lst2.head->next;
    while (!(ptr1 == nullptr && ptr2 == nullptr)) {
        if (ptr1 == nullptr || ptr1->exp < ptr2->exp) {
            ans.addLast(ptr2->coef, ptr2->exp);
            ptr2 = ptr2->next;
            continue;
        }
        if (ptr2 == nullptr || ptr2->exp < ptr1->exp) {
            ans.addLast(ptr1->coef, ptr1->exp);
            ptr1 = ptr1->next;
            continue;
        }
        ans.addLast(ptr2->coef + ptr1->coef, ptr2->exp);
        ptr1 = ptr1->next; 
        ptr2 = ptr2->next;
    }
    return ans;
}