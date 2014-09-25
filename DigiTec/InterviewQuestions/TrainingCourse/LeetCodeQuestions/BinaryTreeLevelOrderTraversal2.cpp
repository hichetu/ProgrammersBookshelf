#include "stdafx.h"

namespace BinaryTreeLevelOrderTraversal2
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
        vector<vector<int> > levelOrderBottom(TreeNode *root)
        {
            vector<vector<int>> output;
            list<TreeNode*> levelOrderQueue;
            vector<TreeNode*> levelStack;
            vector<TreeNode*> reverseStack;

            if (root != nullptr)
            {
                levelOrderQueue.push_back(root);
                levelOrderQueue.push_back(nullptr);

                while (!levelOrderQueue.empty())
                {
                    TreeNode* current = levelOrderQueue.front();
                    levelOrderQueue.pop_front();

                    if (current != nullptr)
                    {
                        if (current->left != nullptr)
                        {
                            levelOrderQueue.push_back(current->left);
                        }
                        if (current->right != nullptr)
                        {
                            levelOrderQueue.push_back(current->right);
                        }
                        levelStack.push_back(current);
                    }
                    else
                    {
                        // Mark the new level with a new sentinel
                        if (levelOrderQueue.size() > 0)
                        {
                            levelOrderQueue.push_back(nullptr);
                        }
                        if (!levelStack.empty())
                        {
                            do
                            {
                                reverseStack.push_back(levelStack.back());
                                levelStack.pop_back();
                            }
                            while (!levelStack.empty());
                            reverseStack.push_back(nullptr);
                        }
                    }
                }

                while (!reverseStack.empty())
                {
                    TreeNode* current = reverseStack.back();
                    reverseStack.pop_back();

                    if (current != nullptr)
                    {
                        output.back().push_back(current->val);
                    }
                    else
                    {
                        output.push_back(vector<int>());
                    }
                }
            }
            return output;
        }
    };

    void RunTests()
    {
        Solution s;

        // Judge 1
        TreeNode t1(1);

        s.levelOrderBottom(&t1);
    }
}