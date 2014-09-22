#include "stdafx.h"

namespace PathSum2
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
        vector<vector<int> > pathSum(TreeNode *root, int sum)
        {
            vector<vector<int>> paths;

            int currentSum = 0;
            vector<TreeNode*> stack;
            TreeNode* current = root;
            TreeNode* prev = nullptr;

            while (!stack.empty() || current != nullptr)
            {
                if (current != nullptr)
                {
                    currentSum += current->val;
                    stack.push_back(current);
                    current = current->left;
                }
                else
                {
                    current = stack.back();
                    if (current->right == nullptr && current->left == nullptr && currentSum == sum)
                    {
                        vector<int> path;
                        for (const TreeNode* node : stack)
                        {
                            path.push_back(node->val);
                        }
                        paths.push_back(path);
                    }

                    if (current->right == nullptr || current->right == prev)
                    {
                        stack.pop_back();
                        currentSum -= current->val;
                        prev = current;
                        current = nullptr;
                    }
                    else
                    {
                        current = current->right;
                    }
                }
            }
            return paths;
        }
    };

    void RunTests()
    {
        Solution s;
        TreeNode one(1);
        TreeNode two(2);
        TreeNode four(4);
        TreeNode four_2(4);
        TreeNode five(5);
        TreeNode five_2(5);
        TreeNode seven(7);
        TreeNode eight(8);
        TreeNode eleven(11);
        TreeNode thirteen(13);

        // Simple problems
        _ASSERT(s.pathSum(nullptr, 1).size() == 0);
        _ASSERT(s.pathSum(&one, 1).size() == 1);

        // Sample problem
        five.left = &four;
        five.right = &eight;
        four.left = &eleven;
        four.right = nullptr;
        eleven.left = &seven;
        eleven.right = &two;
        seven.left = nullptr;
        seven.right = nullptr;
        two.left = nullptr;
        two.right = nullptr;
        eight.left = &thirteen;
        eight.right = &four_2;
        thirteen.left = nullptr;
        thirteen.right = nullptr;
        four_2.left = &five_2;
        four_2.right = &one;
        five_2.left = nullptr;
        five_2.right = nullptr;
        one.left = nullptr;
        one.right = nullptr;
        _ASSERT(s.pathSum(&five, 22).size() == 2);
    }
}