#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* left;
    Node* right;
    Node(const int& i = 0, const int& val = 0, Node* l = nullptr, Node* r = nullptr):
       value(val), left(l), right(r) {};
};

class BinaryTree {
    private:
        std::vector<Node*> constructArray;
        int treeSize;

    public:
        Node* root;

        BinaryTree() {
            /*基于OJ输入格式写的二叉树生成函数，
              以constructArray index表示编号，
              通过index实现节点顺序访问连接，
              Node的val和idx独立。
            */

            // 为题目的输入格式写的特殊的二叉树构建函数
            std::cin >> treeSize;

            if (treeSize == 0) return;

            // 考虑到链表访问的困难性，这里最终选择用数组辅助构造树
            constructArray.resize(treeSize, nullptr);
            for (int i = 0; i < treeSize; i++) {
                constructArray[i] = nullptr;
            }

            int val, l, r;
            for (int i = 0; i < treeSize; i++) {
                std::cin >> val >> l >> r;
                
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

                constructArray[i]->value = val;
                constructArray[i]->left = l == -1 ? nullptr : constructArray[l];
                constructArray[i]->right = r == -1 ? nullptr : constructArray[r];
            }

            root = constructArray[0];
        }

        void _preOrderPrintTree(Node* cur) {
            if (cur == nullptr) {
                return;
            }

            std::cout << cur->value << ' ';
            _preOrderPrintTree(cur->left);
            _preOrderPrintTree(cur->right);
        }

        Node* preOrderTransform(Node* cur, Node* prev = nullptr) {
            Node* tmpL = cur->left;
            Node* tmpR = cur->right;

            if (prev != nullptr) {
                prev->right = cur;
                prev->left = nullptr;
            }

            if (cur->left == nullptr && cur->right == nullptr) {
                return cur;
            }

            if (tmpL != nullptr) {
                cur = preOrderTransform(tmpL, cur);
            }

            if (tmpR != nullptr) {
                cur = preOrderTransform(tmpR, cur);
            }

            return cur;
        }

        void printLinkedList() {
            // 直接按顺序输出二叉树前序展开的链表节点值
            if (root == nullptr) return;
            Node* cur = root;
            while (cur->right != nullptr) {
                std::cout << cur->value << ' ';
                cur = cur->right;
            }
            std::cout << cur->value;
        }
};

int main() {
    BinaryTree tree;
    tree.preOrderTransform(tree.root);
    tree.printLinkedList();
    return 0;
}
