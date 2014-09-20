#include "stdafx.h"

namespace BinaryLevelOrderTraversal
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
        vector<vector<int>> levelOrder(TreeNode *root)
        {
            vector<vector<int>> levelOrderVector;
            if (root != nullptr)
            {
                vector<TreeNode*> queue;
                queue.push_back(root);
                do
                {
                    vector<int> currentLevel;
                    vector<TreeNode*> nextQueue;

                    do
                    {
                        TreeNode* current = queue.front();
                        queue.erase(queue.begin());

                        currentLevel.push_back(current->val);
                        if (current->left != nullptr)
                        {
                            nextQueue.push_back(current->left);
                        }
                        if (current->right != nullptr)
                        {
                            nextQueue.push_back(current->right);
                        }
                    }
                    while (queue.size() > 0);

                    levelOrderVector.push_back(currentLevel);
                    queue.swap(nextQueue);
                }
                while (queue.size() > 0);
            }

            return levelOrderVector;
        }
    };

    void RunTests()
    {
        TreeNode root(3);
        TreeNode nine(9);
        TreeNode twenty(20);
        TreeNode fifteen(15);
        TreeNode seven(7);

        root.left = &nine;
        root.right = &twenty;
        twenty.left = &fifteen;
        twenty.right = &seven;

        Solution s;
        vector<vector<int>> output = s.levelOrder(&root);

        Solution s2;
        vector<vector<int>> output2 = s2.levelOrder(nullptr);
    }
};