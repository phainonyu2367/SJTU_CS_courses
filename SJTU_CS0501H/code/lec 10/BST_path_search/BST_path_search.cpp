#include <iostream>

class BST {
    private:
        struct Node {
            int value;
            Node* left;
            Node* right;
            Node(int v, Node* l = nullptr, Node* r = nullptr): value(v), left(l), right(r) {};
        };

        Node* root;

        void addNode(int value) {
            if (root == nullptr) {
                root = new Node(value);
            } else {
                Node* cur = root;
                while (true) {
                    if (value > cur->value) {
                        if (cur->right == nullptr) {
                            cur->right = new Node(value);
                            return;
                        } else {
                            cur = cur->right;
                        }
                    } else if (value < cur->value) {
                        if (cur->left == nullptr) {
                            cur->left = new Node(value);
                            return;
                        } else {
                            cur = cur->left;
                        }
                    }
                }
            }
        }
    public:
    BST(int size) {
        root = nullptr;
        int value = 0;
        for (int i = 0; i < size; ++i) {
            std::cin >> value;
            addNode(value);
        }
    }

    void pathTo(int query) {
        Node* cur = root;
        if (root == nullptr) {
            std::cout << -1;
            return;
        }
        while (cur != nullptr) {
            if (cur->value == query) {
                std::cout << query;
                return;
            }
            std::cout << cur->value << ' ';
            if (query > cur->value) {
                cur = cur->right;
            } else if (query < cur->value) {
                cur = cur->left;
            }
        }
        std::cout << -1;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    BST bst(n);
    bst.pathTo(k);
}
