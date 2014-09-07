#include "stdafx.h"
// Print a tree in zig-zag order. If the tree were completely full and populated in order.
// Then the values should alternate right-to-left/left-to-right at each level. Examples
//                   1
//                 /   \
//                2     3
//               / \   / \
//              4   5 6   7 = 1 2 3 7 6 5 4 (assume the first row prints right to left, so the second row prints left to right)

void PrintZigZagTree(FullNode<int>* root)
{
    if (root != nullptr)
    {
        vector<FullNode<int>*> stack1;
        vector<FullNode<int>*> stack2;
        vector<FullNode<int>*>* currentStack = &stack1;
        vector<FullNode<int>*>* workStack = &stack2;
        bool fZig = true;

        currentStack->push_back(root);
        while (!currentStack->empty())
        {
            while (!currentStack->empty())
            {
                FullNode<int>* node = currentStack->back();
                currentStack->pop_back();

                wprintf(L"%d", node->GetValue());
                if (fZig)
                {
                    if (node->GetRight() != nullptr)
                    {
                        workStack->push_back(node->GetRight());
                    }
                    if (node->GetLeft() != nullptr)
                    {
                        workStack->push_back(node->GetLeft());
                    }
                }
                else
                {
                    if (node->GetLeft() != nullptr)
                    {
                        workStack->push_back(node->GetLeft());
                    }
                    if (node->GetRight() != nullptr)
                    {
                        workStack->push_back(node->GetRight());
                    }
                }
            }
            swap(currentStack, workStack);
            fZig = !fZig;
        }
    }
}

// Opportunities: The stacks use very little space basically O(2b) were b is the maximum breadth of the tree at any given level.
//
// If this is an issue, then we could use parent pointers to compute NextInLevel/PreviousInLevel and trade linear time
// for log linear time O(nlogn) and O(1) space.