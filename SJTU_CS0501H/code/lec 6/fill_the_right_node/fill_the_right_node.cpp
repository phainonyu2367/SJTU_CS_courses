#include <iostream>
#include <vector>
#include <queue>

/*  本来想着，如果用数组来写这几道题会是更简单且更高效，
    但是后面想了想主要应该是练习链表操作，所以还是不要
    逃这个课比较好。*/


struct Node {
    int value;
    int idx;
    Node* left;
    Node* right;
    Node* next;
    Node(const int& i = 0, const int& val = 0, Node* l = nullptr, Node* r = nullptr, Node* n = nullptr):
       idx(i) ,value(val), left(l), right(r), next(n) {};
};

class BinaryTree {
    private:
        std::vector<Node*> constructArray;
        Node* root;
        int treeSize;

    public:

        BinaryTree() {
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
        
        void setNext() {
            Node* cur = root;

            if (root == nullptr) return;

            int count = 1, level = 1;
            std::queue<Node*> levelOrderQueue;
            std::queue<int> levelQueue;
            levelOrderQueue.push(cur);
            levelQueue.push(1);

            while (!levelOrderQueue.empty()) {
                cur = levelOrderQueue.front();
                levelOrderQueue.pop();
                level = levelQueue.front();
                levelQueue.pop();

                if (!levelOrderQueue.empty() && levelQueue.front() == level) {
                    cur->next = levelOrderQueue.front();
                } else {
                    cur->next = nullptr;
                }

                if (cur->left != nullptr) {
                    levelOrderQueue.push(cur->left);
                    count++;
                    levelQueue.push(level + 1);
                }

                if (cur->right != nullptr) {
                    levelOrderQueue.push(cur->right);
                    count++;
                    levelQueue.push(level + 1);
                }
            }
        }

        void printNext() {
            for (int i = 0; i < constructArray.size(); i++) {
                Node* next = constructArray[i]->next;
                if (next == nullptr) {
                    std::cout << 0 << std::endl;
                } else {
                    std::cout << next->idx << std::endl;
                }
            }
        }
};

int main() {
    BinaryTree tree;
    tree.setNext();
    tree.printNext();
}