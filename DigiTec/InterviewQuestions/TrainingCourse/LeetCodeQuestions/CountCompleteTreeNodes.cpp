#include "stdafx.h"

namespace CountCompleteTreeNodes
{
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class Solution
    {
    public:
        int countNodes(TreeNode* root)
        {
            if (root == nullptr)
            {
                return 0;
            }

            // Total height of the tree
            int h = height(root);
            int nodes = (1 << (h+1)) - 1;
            if (h > 0)
            {
                while (root != nullptr && h > 0)
                {
                    if (root->right == nullptr || height(root->right) < h - 1)
                    {
                        nodes -= (1 << (h - 1));
                        root = root->left;
                    }
                    else
                    {
                        root = root->right;
                    }
                    h--;
                }
            }
            return nodes;
        }

        int height(TreeNode* root)
        {
            int h = 0;
            while (root->left != nullptr)
            {
                h++;
                root = root->left;
            }
            return h;
        }
    };

    void RunTests()
    {
        Solution s;
 
        TreeNode a1(1);
        TreeNode a2(2);
        a1.left = &a2;

        _ASSERT(s.countNodes(&a1) == 2);

        TreeNode b1(1);
        TreeNode b2(2);
        TreeNode b3(3);
        b1.left = &b2;
        b1.right = &b3;
        
        _ASSERT(s.countNodes(&b1) == 3);

        TreeNode c1(1);

        TreeNode c2(2);
        TreeNode c3(3);

        TreeNode c4(4);
        TreeNode c5(5);
        TreeNode c6(6);

        c1.left = &c2;
        c1.right = &c3;

        c2.left = &c4;
        c2.right = &c5;
        c3.left = &c6;

        _ASSERT(s.countNodes(&c1) == 6);

        TreeNode d1(1);

        TreeNode d2(2);
        TreeNode d3(3);

        TreeNode d4(4);

        d1.left = &d2;
        d1.right = &d3;

        d2.left = &d4;

        _ASSERT(s.countNodes(&d1) == 4);
    }
}