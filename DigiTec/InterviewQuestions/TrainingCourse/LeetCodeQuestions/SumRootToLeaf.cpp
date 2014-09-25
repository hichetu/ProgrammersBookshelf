#include "stdafx.h"

namespace SumRootToLeaf
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr)
        {
        }
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
        int sumNumbers(TreeNode *root)
        {
            int totalSum = 0;
            int currentPath = 0;
            TreeNode* current = root;
            TreeNode* prev = nullptr;
            vector<TreeNode*> stack;

            while (!stack.empty() || current != nullptr)
            {
                if (current != nullptr)
                {
                    stack.push_back(current);
                    currentPath *= 10;
                    currentPath += current->val;
                    current = current->left;
                }
                else
                {
                    current = stack.back();
                    if (current->left == nullptr && current->right == nullptr)
                    {
                        totalSum += currentPath;
                    }
                    if (current->right == nullptr || current->right == prev)
                    {
                        currentPath /= 10;

                        stack.pop_back();
                        prev = current;
                        current = nullptr;
                    }
                    else
                    {
                        current = current->right;
                    }
                }
            }
            return totalSum;
        }
    };
};