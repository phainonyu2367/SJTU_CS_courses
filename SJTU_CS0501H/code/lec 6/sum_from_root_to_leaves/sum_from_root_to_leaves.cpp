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

        std::vector<int> numConstructArray;
        std::vector<int> ansArray;

        bool _isLeaf(Node* cur) {
            return cur->left == nullptr && cur->right == nullptr;
        }

        void _sumHelper(Node* cur, int currentSum) {
            if (cur == nullptr) return;
            
            currentSum = currentSum * 10 + cur->value;
            
            if (_isLeaf(cur)) {
                ansArray.push_back(currentSum);
                return;
            }
            
            _sumHelper(cur->left, currentSum);
            _sumHelper(cur->right, currentSum);
        }

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
            numConstructArray.reserve(treeSize);
            ansArray.reserve(treeSize);

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

        // void _preOrderPrintTree(Node* cur) {
        //     if (cur == nullptr) {
        //         return;
        //     }

        //     std::cout << cur->value << ' ';
        //     _preOrderPrintTree(cur->left);
        //     _preOrderPrintTree(cur->right);
        // }

        int sumOfAll() {
            if (root == nullptr) return 0;
            _sumHelper(root, 0);
            int ans = 0;
            for (int i = 0; i < ansArray.size(); i++) {
                ans += ansArray[i];
            }
            return ans;
        }
        


};

int main() {
    BinaryTree tree;
    std::cout << tree.sumOfAll();
    return 0;
}