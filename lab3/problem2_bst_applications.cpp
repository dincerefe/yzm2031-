#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ======================================================================================
// PROBLEM 2: BST Applications
// ======================================================================================

/*
    1. kthSmallest
    
    Given the root of a binary search tree, and an integer k, return the kth smallest value (1-indexed) 
    of all the values of the nodes in the tree.
*/

int kthSmallest(TreeNode* root, int k) {
    // TODO: Implement this function
    if (root == nullptr) return -1;
    vector<int>values;
    vector<TreeNode*>nodes;
    while (values.size()<k) {
        while (root != nullptr) {
            nodes.push_back(root);
            root = root->left;
        }
        if (nodes.empty()) break;
        root = nodes.back();
        nodes.pop_back();
        values.push_back(root->val);
        root = root->right;
    }
    return values[k-1];

    
}

/*
    2. LCA (Lowest Common Ancestor)
    
    Given a binary search tree (BST), find the lowest common ancestor (LCA) node of two given nodes in the BST.
    According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes 
    p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a 
    descendant of itself).”
*/
TreeNode* LCA(TreeNode* root, TreeNode* p, TreeNode* q) {
    // TODO: Implement this function
    if (root == nullptr || p == nullptr || q == nullptr) return nullptr;
    while (root != nullptr) {
        if ((root->val >= p->val && root->val <= q->val) || (root->val <= p->val && root->val >= q->val) || root->val==q->val || root->val==p->val) {
            return root;
        } else if (root->val < p->val && root->val < q->val) {
            root = root->right;
        } else if (root->val > p->val && root->val > q->val) {
            root = root->left;
        }
    }
    return root;
}

/*
    3. rangeSum
    
    Given the root node of a binary search tree and two integers low and high, return the sum of values 
    of all nodes with a value in the inclusive range [low, high].
*/
int rangeSum(TreeNode* root, int L, int R) {
    // TODO: Implement this function
    if (root == nullptr) return 0;
    int total = 0;
    queue<TreeNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        if (nodes.front()->val >= L && nodes.front()->val <= R) {
            total += nodes.front()->val;
        }
        if (nodes.front()->left != nullptr && nodes.front()->val > L) {
            nodes.push(nodes.front()->left);
        }
        if (nodes.front()->right != nullptr && nodes.front()->val < R) {
            nodes.push(nodes.front()->right);
        }
        nodes.pop();
    }
    return total;
}

/*
    4. invertTree
    
    Given the root of a binary tree, invert the tree, and return its root.
*/
TreeNode* invertTree(TreeNode* root) {
    // TODO: Implement this function
    if (root == nullptr) return nullptr;
    queue<TreeNode*> nodes;
    nodes.push(root); 
    while (!nodes.empty()) {
        TreeNode* tmp = nodes.front();
        nodes.pop();
        TreeNode* tmp2 = tmp->left;
        tmp->left = tmp->right;
        tmp->right = tmp2;
        if (tmp->left != nullptr) {
            nodes.push(tmp->left);
        } if (tmp->right != nullptr) {
            nodes.push(tmp->right);
        }
    }

    return root; 
}

// Helper to delete tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(8);

    TreeNode* p = root->left; // 3
    TreeNode* q = root->left->right; // 4
    
    cout << "3rd Smallest: " << kthSmallest(root, 3) << " (Expected: 4)" << endl;
    
    TreeNode* lca = LCA(root, p, q);
    cout << "LCA of 3 and 4: " << (lca ? lca->val : -1) << " (Expected: 3)" << endl;
    
    lca = LCA(root, root->left->left, root->right->right); // 2 and 8
    cout << "LCA of 2 and 8: " << (lca ? lca->val : -1) << " (Expected: 5)" << endl;

    cout << "Range Sum [3, 7]: " << rangeSum(root, 3, 7) << " (Expected: 19)" << endl;

    root = invertTree(root);
    cout << "After Invert, Root Left: " << (root->left ? root->left->val : -1) << " (Expected: 7)" << endl;
    cout << "After Invert, Root Right: " << (root->right ? root->right->val : -1) << " (Expected: 3)" << endl;

    deleteTree(root);
    return 0;
}

