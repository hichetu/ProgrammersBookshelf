#include "stdafx.h"

namespace BinaryTreeZigZagLevelOrder
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
        vector<vector<int> > zigzagLevelOrder(TreeNode *root)
        {
            vector<vector<int>> zigZag;

            if (root != nullptr)
            {
                vector<TreeNode*>* curQueue = new vector<TreeNode*>();
                vector<TreeNode*>* nextQueue = new vector<TreeNode*>();
                bool reverse = false;

                curQueue->push_back(root);
                while (!curQueue->empty())
                {
                    zigZag.push_back(vector<int>());
                    while (!curQueue->empty())
                    {
                        TreeNode* current = curQueue->back();
                        curQueue->pop_back();

                        zigZag.back().push_back(current->val);
                        if (reverse)
                        {
                            if (current->right != nullptr)
                            {
                                nextQueue->push_back(current->right);
                            }
                            if (current->left != nullptr)
                            {
                                nextQueue->push_back(current->left);
                            }
                        }
                        else
                        {
                            if (current->left != nullptr)
                            {
                                nextQueue->push_back(current->left);
                            }
                            if (current->right != nullptr)
                            {
                                nextQueue->push_back(current->right);
                            }
                        }
                    }
                    swap(curQueue, nextQueue);
                    reverse = !reverse;
                }
            }

            return zigZag;
        }
    };

    void RunTests()
    {
        Solution s;

        TreeNode t1(1);
        s.zigzagLevelOrder(&t1);

        TreeNode t2_1(1);
        TreeNode t2_2(2);
        TreeNode t2_3(3);
        TreeNode t2_4(4);
        TreeNode t2_5(5);
        t2_1.left = &t2_2;
        t2_1.right = &t2_3;
        t2_2.left = &t2_4;
        t2_3.right = &t2_5;
        vector<vector<int>> r2 = s.zigzagLevelOrder(&t2_1);
    }
}