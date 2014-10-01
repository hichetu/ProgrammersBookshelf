#include "stdafx.h"

namespace ConstructBinaryFromInorderAndPostorder
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    /**
    * Definition for binary tree
    * struct TreeNode {
    *     int val;
    *     TreeNode *left;
    *     TreeNode *right;
    *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    * };
    */
    class Solution
    {
    public:
        TreeNode* buildSubTree(vector<int>& postorder, vector<int>& inorder, int start, int end)
        {
            if (start > end)
            {
                return nullptr;
            }

            TreeNode* root = new TreeNode(postorder.back());
            postorder.pop_back();
            int mid = findNode(root->val, inorder, start, end);
            root->right = buildSubTree(postorder, inorder, mid + 1, end);
            root->left = buildSubTree(postorder, inorder, start, mid - 1);
            return root;
        }

        int findNode(int value, vector<int>& inorder, int start, int end)
        {
            for (int i = start; i <= end; i++)
            {
                if (inorder[i] == value)
                {
                    return i;
                }
            }
        }

        TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
        {
            if (postorder.size() == 0)
            {
                return nullptr;
            }
            TreeNode* root = buildSubTree(postorder, inorder, 0, inorder.size() - 1);
        }
    };

    void RunTests()
    {
        Solution s;

        vector<int> s1post = { 1, 3, 2 };
        vector<int> s1inorder = { 3, 2, 1 };
        TreeNode* r1 = s.buildTree(s1inorder, s1post);

        vector<int> s2post = { 1, 3, 2 };
        vector<int> s2inorder = { 3, 2, 1 };
        TreeNode* r2 = s.buildTree(s2inorder, s2post);
    }
}