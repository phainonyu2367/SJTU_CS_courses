#include <iostream>
#include <vector>
#include <stack>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;
    Node(const int& val, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr):
       value(val), parent(p), left(l), right(r) {};
};

class BinaryTree {
    private:
        std::vector<Node*> constructArray;
        int treeSize;

    public:
        Node* root;

        BinaryTree(int treeSize) {
            /*基于OJ输入格式写的二叉树生成函数，
              以constructArray index表示编号，
              通过index实现节点顺序访问连接，
              Node的val和idx独立。
            */

            // 为题目的输入格式写的特殊的二叉树构建函数
            if (treeSize == 0) {
                return;
            }

            // 考虑到链表访问的困难性，这里最终选择用数组辅助构造树
            constructArray.resize(treeSize, nullptr);
            for (int i = 0; i < treeSize; i++) {
                constructArray[i] = nullptr;
            }

            int l, r;
            for (int i = 0; i < treeSize; i++) {
                std::cin >> l >> r;
                
                l--; r--;

                if (l != -1 && constructArray[l] == nullptr) {
                    constructArray[l] = new Node(l + 1);
                }

                if (r != -1 && constructArray[r] == nullptr) {
                    constructArray[r] = new Node(r + 1);
                }
                
                if (constructArray[i] == nullptr) {
                    constructArray[i] = new Node(i + 1);
                }

                constructArray[i]->left = l == -1 ? nullptr : constructArray[l];
                constructArray[i]->right = r == -1 ? nullptr : constructArray[r];
                if (l != -1) {
                    constructArray[l]->parent = constructArray[i];
                }
                if (r != -1) {
                    constructArray[r]->parent = constructArray[i];
                }
            }
        }

        int LCA(int left, int right) {
            std::stack<int> lparents, rparents;
            Node* cur = constructArray[left - 1];
            while (cur != nullptr) {
                lparents.push(cur->value);
                cur = cur->parent;
            }
            cur = constructArray[right - 1];
            while (cur != nullptr) {
                rparents.push(cur->value);
                cur = cur->parent;
            }
            int p;
            while (!rparents.empty() && !lparents.empty() && lparents.top() == rparents.top()) {
                p = lparents.top();
                lparents.pop();
                rparents.pop();
            }
            return p;
        }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int treeSize, left, right;
    std::cin >> treeSize >> left >> right;
    BinaryTree tree(treeSize);
    std::cout << tree.LCA(left, right);
}