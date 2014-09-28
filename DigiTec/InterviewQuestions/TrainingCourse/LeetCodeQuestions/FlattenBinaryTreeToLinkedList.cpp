#include "stdafx.h"

namespace FlattenBinaryTreeToLinkedList
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
        TreeNode* flattenList(TreeNode* root)
        {
            if (root != nullptr)
            {
                TreeNode* left = root->left;
                TreeNode* right = root->right;

                TreeNode* leftTail = nullptr;
                if (left != nullptr)
                {
                    leftTail = flattenList(left);
                }
                TreeNode* rightTail = nullptr;
                if (right != nullptr)
                {
                    rightTail = flattenList(right);
                }

                root->left = nullptr;
                root->right = left;
                if (root->right == nullptr)
                {
                    root->right = right;
                }
                if (leftTail != nullptr)
                {
                    root = leftTail;
                    leftTail->right = right;
                }
                if (rightTail != nullptr)
                {
                    root = rightTail;
                }
            }
            return root;
        }

        void flatten(TreeNode *root)
        {
            flattenList(root);
        }
    };

    void RunTests()
    {
        Solution s;

        TreeNode t1(1);
        TreeNode t2(2);
        t1.right = &t2;
        s.flatten(&t1);

        TreeNode t2_1(1);
        TreeNode t2_2(2);
        TreeNode t2_3(3);
        TreeNode t2_4(4);
        TreeNode t2_5(5);
        TreeNode t2_6(6);
        t2_1.left = &t2_2;
        t2_2.left = &t2_3;
        t2_2.right = &t2_4;
        t2_1.right = &t2_5;
        t2_5.right = &t2_6;
        s.flatten(&t2_1);
    }
}