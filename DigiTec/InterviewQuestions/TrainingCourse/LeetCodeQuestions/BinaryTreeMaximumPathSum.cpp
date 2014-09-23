#include "stdafx.h"

namespace BinaryTreeMaximumPathSum
{
    struct TreeNode
    {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr)
        {
        }
        void terminal()
        {
            left = nullptr;
            right = nullptr;
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
        int maxPathSum(TreeNode *root)
        {
            if (root == nullptr)
            {
                return 0;
            }
            int maxTreePath;
            maxPathSumWorker(root, maxTreePath);
            return maxTreePath;
        }

        int maxPathSumWorker(TreeNode* root, int& maxTreePath)
        {
            maxTreePath = INT_MIN;
            if (root == nullptr)
            {
                return 0;
            }

            int maxLeftTree;
            int maxLeft = maxPathSumWorker(root->left, maxLeftTree);

            int maxRightTree;
            int maxRight = maxPathSumWorker(root->right, maxRightTree);

            maxTreePath = max(max(max(maxLeft + root->val, maxRight + root->val), max(maxLeftTree, maxRightTree)), max(maxLeft + maxRight + root->val, root->val));
            return max(0, max(maxLeft, maxRight)) + root->val;
        }
    };

    void RunTests()
    {
        Solution s;

        TreeNode t1(1);
        TreeNode t2(2);
        TreeNode t3(3);

        TreeNode t10(10);
        TreeNode t11(11);
        TreeNode t12(12);
        TreeNode t13(13);

        // Null node
        _ASSERT(s.maxPathSum(nullptr) == 0);

        // Single node
        t1.left = nullptr;
        t1.right = nullptr;
        _ASSERT(s.maxPathSum(&t1) == 1);

        // Sample Test
        t1.left = &t2;
        t1.right = &t3;
        t2.left = nullptr;
        t2.right = nullptr;
        t3.left = nullptr;
        t3.right = nullptr;
        _ASSERT(s.maxPathSum(&t1) == 6);

        // SubTree Test
        t1.left = &t10;
        t1.right = &t2;
        t10.left = &t11;
        t10.right = &t12;
        t11.terminal();
        t12.terminal();
        t2.left = &t3;
        t2.right = nullptr;
        t3.terminal();
        _ASSERT(s.maxPathSum(&t1) == 33);

        // Long SubPath Test
        t1.left = &t10;
        t1.right = &t11;
        t10.left = &t2;
        t10.right = &t12;
        t2.terminal();
        t12.terminal();
        t11.right = &t13;
        t11.left = &t3;
        t3.terminal();
        t13.terminal();
        _ASSERT(s.maxPathSum(&t1) == 47);

        // Judge test 1
        TreeNode tNeg3(-3);
        _ASSERT(s.maxPathSum(&tNeg3) == -3);

        // Judge test 2
        TreeNode tNeg1(-1);
        t2.left = &tNeg1;
        t2.right = nullptr;
        tNeg1.terminal();
        _ASSERT(s.maxPathSum(&t2) == 2);

        // Judge test 3
        TreeNode j9(9);
        TreeNode j6(6);
        TreeNode jNeg3(-3);
        TreeNode j2_1(2);
        TreeNode j2_2(2);
        TreeNode jNeg6_1(-6);
        TreeNode jNeg6_2(-6);
        TreeNode jNeg6_3(-6);
        TreeNode jNeg6_4(-6);

        j9.left = &j6;
        j9.right = &jNeg3;
        j6.terminal();
        jNeg3.left = &jNeg6_1;
        jNeg3.right = &j2_1;
        j2_1.left = &j2_2;
        j2_1.right = nullptr;
        j2_2.left = &jNeg6_2;
        j2_2.right = &jNeg6_3;
        jNeg6_2.left = &jNeg6_4;
        jNeg6_2.right = nullptr;
        jNeg6_3.terminal();
        jNeg6_4.terminal();
        _ASSERT(s.maxPathSum(&j9) == 16);
    }
};