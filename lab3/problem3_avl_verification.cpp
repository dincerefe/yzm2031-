#include <iostream>
#include <algorithm>
#include <climits>
#include <math.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ======================================================================================
// PROBLEM 3: AVL Verification
// ======================================================================================

/*
    isValidAVL(TreeNode* root)
    
    Check if the given binary tree is a valid AVL tree.
*/

int height(TreeNode* node) {
    if (node == nullptr) return 0;
    int left = height(node->left);
    int right = height(node->right);
    if (left > right) {
        return left + 1;
    } return right + 1;
}


bool isValidAVL(TreeNode* root, int minVal = INT_MIN, int maxVal = INT_MAX) {
    if (root == nullptr) return true;

    if (root->val <= minVal || root->val >= maxVal)
        return false;
    
    int lefth = height(root->left);
    int righth = height(root->right);
    if (abs(lefth - righth) > 1) {
        return false;
    }
    return isValidAVL(root->left, minVal, root->val) && isValidAVL(root->right, root->val, maxVal);
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode* root1 = new TreeNode(2);
    root1->left = new TreeNode(1);
    root1->right = new TreeNode(3);

    cout << "Tree 1 (AVL) - Is Valid? " << (isValidAVL(root1) ? "Yes" : "No") << " (Expected: Yes)" << endl;

    TreeNode* root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    root2->right->right = new TreeNode(3);

    cout << "Tree 2 (Skewed) - Is Valid? " << (isValidAVL(root2) ? "Yes" : "No") << " (Expected: No)" << endl;

    TreeNode* root3 = new TreeNode(2);
    root3->left = new TreeNode(3);
    root3->right = new TreeNode(1);

    cout << "Tree 3 (Not BST) - Is Valid? " << (isValidAVL(root3) ? "Yes" : "No") << " (Expected: No)" << endl;

    deleteTree(root1);
    deleteTree(root2);
    deleteTree(root3);

    return 0;
}

