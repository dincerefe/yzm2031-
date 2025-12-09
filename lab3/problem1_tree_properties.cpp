#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ======================================================================================
// PROBLEM 1: Tree Properties
// ======================================================================================

/*
    1. isComplete(TreeNode* root)
    
    Check if the binary tree is a complete binary tree.
*/
bool isComplete(TreeNode* root) {
    // TODO: Implement this function
    queue<TreeNode*> node;
    if (root == nullptr) return true;
    node.push(root);
    while (node.front() != nullptr) {
        node.push(node.front()->left);
        node.push(node.front()->right);
        node.pop();
    } 
    node.pop();
    while (!node.empty() && node.front() == nullptr) {
        node.pop();
    }
    return node.empty();
}

/*
    2. isBalanced(TreeNode* root)
    
    Check if the binary tree is height-balanced.
*/

// Helper function to calculate height. You may or may not need this.
int height(TreeNode* node) {
    // TODO: Implement this function (optional helper)
    if (node == nullptr) return 0;
    int left = height(node->left);
    int right = height(node->right);
    if (left > right) {
        return left + 1;
    } return right + 1;
}

bool isBalanced(TreeNode* root) {
    // TODO: Implement this function
    if (root == nullptr) return true;
    int lefth = height(root->left);
    int righth = height(root->right);
    if (abs(lefth - righth) > 1) {
        return false;
    }
    return isBalanced(root->left) && isBalanced(root->right);
}

/*
    3. maxWidth(TreeNode* root)
    
    Given the root of a binary tree, return the maximum width of the given tree.
*/
int maxWidth(TreeNode* root) {
    // TODO: Implement this function
    {
        /* code */
        if (root == nullptr) return 0;
        queue<TreeNode*> nodes;
        nodes.push(root);
        int max_width = 0;

        while (!nodes.empty()) {
            int size = nodes.size();
            if (max_width <= size) {
                max_width = size;
            } 
            for (int i = 0; i < size; i++) {
                
                if (nodes.front()->left != nullptr) {
                    nodes.push(nodes.front()->left);
                } if (nodes.front()->right != nullptr) {
                    nodes.push(nodes.front()->right);
                }
                nodes.pop();
            }
        }
        return max_width;
    }
    
    return 0;
}

// Helper to delete tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Test Case 1: Complete and Balanced Tree
    TreeNode* root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    root1->right->left = new TreeNode(6);

    cout << "Tree 1 - Is Complete? " << (isComplete(root1) ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "Tree 1 - Is Balanced? " << (isBalanced(root1) ? "Yes" : "No") << " (Expected: Yes)" << endl;
    cout << "Tree 1 - Max Width? " << maxWidth(root1) << " (Expected: 3)" << endl;

    // Test Case 2: Skewed Tree (Not Balanced, Not Complete)
    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    root2->right->right = new TreeNode(3);

    cout << "\nTree 2 - Is Complete? " << (isComplete(root2) ? "Yes" : "No") << " (Expected: No)" << endl;
    cout << "Tree 2 - Is Balanced? " << (isBalanced(root2) ? "Yes" : "No") << " (Expected: No)" << endl;
    cout << "Tree 2 - Max Width? " << maxWidth(root2) << " (Expected: 1)" << endl;

    deleteTree(root1);
    deleteTree(root2);
    
    return 0;
}

