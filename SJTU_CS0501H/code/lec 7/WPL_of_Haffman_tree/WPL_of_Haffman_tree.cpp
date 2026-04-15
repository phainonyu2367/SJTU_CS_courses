#include <iostream>
#include <vector>

struct Node {
    int left;
    long long weight;
    int right;
    Node(int l, int w, int r): left(l), weight(w), right(r) {};
};

int _findRoot(std::vector<bool> rootFinder, int size) {
    // Find the rood idx according to the rootFinder
    for (int i = 0; i < size; ++i) {
        if (rootFinder[i]) {
            return i;
        }
    }

    return -1;
}

int constructTree(std::vector<Node*>& tree, int size) {
    /*
    Construct the tree and return the idx of the root
    @param 
        - std::vector<Node*> tree
            - vector that stores the tree
        - int size
            - size of the tree
    @return
        - int idx
            - index of the root
    */
    std::vector<bool> rootFinder;
    rootFinder.resize(size, true);
    int left, right;
    long long weight;

    for (int i = 0; i < size; ++i) {
        std::cin >> left >> weight >> right;
        tree[i] = new Node(left, weight, right);

        if (left > 0) {
            rootFinder[left - 1] = false;
        }

        if (right > 0) {
            rootFinder[right - 1] = false;
        }
    }


    return _findRoot(rootFinder, size);
}

long long _WPLHelper(const std::vector<Node*>& tree, int root, int height) {
    // Helper method for WPL to do recursion
    if (root == -1) {
        return 0;
    }

    if (tree[root]->left == 0 && tree[root]->right == 0) {
        return height * tree[root]->weight;
    } else {
        return _WPLHelper(tree, tree[root]->left - 1, height + 1) + 
               _WPLHelper(tree, tree[root]->right - 1, height + 1);
    }
}

long long WPL(const std::vector<Node*>& tree, int root) {
    /*
    Calculate the WPL of the tree using recursion
    @param
        - const std::vector<Node*>& tree
            - the tree
    @return
        - int WPL
            - the WPL of the input tree
    */
    return _WPLHelper(tree, root, 0);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::vector<Node*> tree;
    int size;
    std::cin >> size;
    tree.resize(size, nullptr);

    int root_idx = constructTree(tree, size);

    // code for robustness, but will not be used in the Online Judge
    // if (root_idx == -1) {
    //     std::cerr << "Error! Missing root.";
    //     return -1;
    // }

    std::cout << WPL(tree, root_idx);
    return 0;
}