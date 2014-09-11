// Trees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

Tree<FullNode<int>>* BuildTreeFromParts(wchar_t* treeParts)
{
    vector<FullNode<int>*> nodes;
    wchar_t* ctx = nullptr;
    wchar_t* nodeLink = wcstok_s(treeParts, L",", &ctx);
    while (nodeLink != nullptr)
    {
        wchar_t* ctx2 = nullptr;
        wchar_t* part = wcstok_s(nodeLink, L"-", &ctx2);

        int nodeId = _wtoi(part);
        if (nodes.size() <= nodeId)
        {
            nodes.push_back(new FullNode<int>(nullptr));
            nodes.back()->SetValue(nodeId);
        }
        FullNode<int>* parent = nodes[nodeId];

        bool isLeft = false;
        part = wcstok_s(nullptr, L"-", &ctx2);
        switch (part[0])
        {
        case L'l':
            isLeft = true;
            break;
        case L'r':
            isLeft = false;
            break;
        default:
            _ASSERT(false);
            break;
        }
        part++;

        int childId = _wtoi(part);
        if (nodes.size() <= childId)
        {
            nodes.push_back(new FullNode<int>(nullptr));
            nodes.back()->SetValue(childId);
        }
        FullNode<int>* child = nodes[childId];
        child->SetParent(parent);
        if (isLeft)
        {
            parent->SetLeft(child);
        }
        else
        {
            parent->SetRight(child);
        }
        // Finish the enumeration so we make sure the string is in the right state
        part = wcstok_s(nullptr, L"-", &ctx2);
        _ASSERT(part == nullptr);

        nodeLink = wcstok_s(nullptr, L",", &ctx);
    }

    Tree<FullNode<int>>* newTree = new Tree<FullNode<int>>(nodes[0]);
    return newTree;
}

Tree<FullNode<int>>* TreeConstructor(const wchar_t* treeDefinition)
{
    Tree<FullNode<int>>* newTree = nullptr;
    wchar_t* mutableTreeDefinition = _wcsdup(treeDefinition);
    wchar_t* ctx = nullptr;

    vector<wchar_t*> parts;

    wchar_t* part = wcstok_s(mutableTreeDefinition, L"\n", &ctx);
    while (part != nullptr)
    {
        parts.push_back(_wcsdup(part));
        part = wcstok_s(nullptr, L"\n", &ctx);
    }

    if (parts.size() > 0)
    {
        wchar_t* treePart = parts.front();
        parts.erase(parts.begin());

        newTree = BuildTreeFromParts(treePart);
    }
    return newTree;
}

void PrintPreOrderRecursive(FullNode<int>* root)
{
    if (root != nullptr)
    {
        wprintf(L"%d", root->GetValue());
        PrintPreOrderRecursive(root->GetLeft());
        PrintPreOrderRecursive(root->GetRight());
    }
}
void PrintPreOrderIterativeStack(FullNode<int>* root)
{
    vector<FullNode<int>*> stack;
    stack.push_back(root);

    while (stack.size() > 0)
    {
        FullNode<int>* node = stack.back();
        stack.erase(stack.end() - 1);

        wprintf(L"%d", node->GetValue());
        if (node->GetRight() != nullptr)
        {
            stack.push_back(node->GetRight());
        }
        if (node->GetLeft() != nullptr)
        {
            stack.push_back(node->GetLeft());
        }
    }
}
void PrintPreOrderParentPointer(FullNode<int>* root)
{
    FullNode<int>* current = root;
    FullNode<int>* prev = nullptr;

    while (current != nullptr)
    {
        // Works for root since m_parent == nullptr.
        if (prev == current->GetParent())
        {
            wprintf(L"%d", current->GetValue());
            prev = current;
            if (current->GetLeft() != nullptr)
            {
                current = current->GetLeft();
            }
            else if (current->GetRight() != nullptr)
            {
                current = current->GetRight();
            }
            else
            {
                current = current->GetParent();
            }
        }
        else if (prev == current->GetLeft() && current->GetRight() != nullptr)
        {
            prev = current;
            current = current->GetRight();
        }
        else
        {
            prev = current;
            current = current->GetParent();
        }
    }
}

void PrintInOrderRecursive(FullNode<int>* root)
{
    if (root != nullptr)
    {
        PrintInOrderRecursive(root->GetLeft());
        wprintf(L"%d", root->GetValue());
        PrintInOrderRecursive(root->GetRight());
    }
}
void PrintInOrderParentPointer(FullNode<int>* root)
{
    FullNode<int>* current = root;
    FullNode<int>* prev = nullptr;

    while (current != nullptr)
    {
        // Works for root since m_parent == nullptr.
        if (prev == current->GetParent())
        {
            prev = current;
            if (current->GetLeft() != nullptr)
            {
                current = current->GetLeft();
            }
            else if (current->GetRight() != nullptr)
            {
                // If we came from our parent, and don't have a left sub-tree we must print now.
                wprintf(L"%d", current->GetValue());
                current = current->GetRight();
            }
            else
            {
                // If we came from our parent, and we are returning, we must print now
                wprintf(L"%d", current->GetValue());
                current = current->GetParent();
            }
        }
        else if (prev == current->GetLeft())
        {
            // Otherwise we came from our left, but we also need to print
            wprintf(L"%d", current->GetValue());

            prev = current;
            if (current->GetRight())
            {
                current = current->GetRight();
            }
            else
            {
                current = current->GetParent();
            }
        }
        else
        {
            prev = current;
            current = current->GetParent();
        }
    }
}
void PrintInOrderParentPointer_Reduced(FullNode<int>* root)
{
    FullNode<int>* current = root;
    FullNode<int>* prev = nullptr;

    while (current != nullptr)
    {
        // Works for root since m_parent == nullptr.
        if (prev == current->GetParent())
        {
            if (current->GetLeft() != nullptr)
            {
                prev = current;
                current = current->GetLeft();
                continue;
            }
            else
            {
                prev = nullptr;
            }
        }

        if (prev == current->GetLeft())
        {
            // Otherwise we came from our left and we need to print
            // Due to our prev = nullptr in the prev == GetParent() call this also works
            // when we don't have a left sub-tree.
            wprintf(L"%d", current->GetValue());

            if (current->GetRight() != nullptr)
            {
                prev = current;
                current = current->GetRight();
                continue;
            }
            else
            {
                prev = nullptr;
            }
        }

        prev = current;
        current = current->GetParent();
    }
}

void PrintInOrderIterativeStack(FullNode<int>* root)
{
    vector<FullNode<int>*> stack;
    FullNode<int>* current = root;
    while (stack.size() > 0 || current != nullptr)
    {
        // First iterates down the left sub-tree
        if (current != nullptr)
        {
            stack.push_back(current);
            current = current->GetLeft();
        }
        else
        {
            // If we get here then our last current didn't have a left sub-tree
            current = stack.back();
            stack.erase(stack.end() - 1);
            wprintf(L"%d", current->GetValue());
            current = current->GetRight();
        }
    }
}

void PrintPostOrderRecursive(FullNode<int>* root)
{
    if (root != nullptr)
    {
        PrintPostOrderRecursive(root->GetLeft());
        PrintPostOrderRecursive(root->GetRight());
        wprintf(L"%d", root->GetValue());
    }
}
void PrintPostOrderIterativeStack(FullNode<int>* root)
{
    vector<FullNode<int>*> stack;
    FullNode<int>* current = root;
    FullNode<int>* prev = nullptr;
    while (stack.size() > 0 || current != nullptr)
    {
        // First iterates down the left sub-tree
        if (current != nullptr)
        {
            stack.push_back(current);
            current = current->GetLeft();
        }
        else
        {
            // Peek back, but don't remove it just yet.
            current = stack.back();

            // If we get here then our last current didn't have a left sub-tree
            if (current->GetRight() == nullptr || current->GetRight() == prev)
            {
                stack.erase(stack.end() - 1);
                wprintf(L"%d", current->GetValue());

                prev = current;
                current = nullptr;
            }
            else
            {
                current = current->GetRight();
            }
        }
    }
}
void PrintPostOrderParentPointer(FullNode<int>* root)
{
    FullNode<int>* current = root;
    FullNode<int>* prev = nullptr;

    while (current != nullptr)
    {
        // Works for root since m_parent == nullptr.
        if (prev == current->GetParent() && (current->GetLeft() != nullptr || current->GetRight() != nullptr))
        {
            prev = current;
            if (current->GetLeft() != nullptr)
            {
                current = current->GetLeft();
            }
            else
            {
                current = current->GetRight();
            }
        }
        else if (prev == current->GetLeft() && current->GetRight())
        {
            prev = current;
            current = current->GetRight();
        }
        else
        {
            prev = current;

            // If we are going back to our parent
            wprintf(L"%d", current->GetValue());
            current = current->GetParent();
        }
    }
}

FullNode<int>* FindNode(FullNode<int>* root, int value)
{
    if (root == nullptr)
    {
        return root;
    }
    if (root->GetValue() == value)
    {
        return root;
    }
    else if (root->GetValue() > value)
    {
        return FindNode(root->GetLeft(), value);
    }
    else
    {
        return FindNode(root->GetRight(), value);
    }
}
FullNode<int>* FindNodeIterative(FullNode<int>* root, int value)
{
    while (root != nullptr)
    {
        if (root->GetValue() == value)
        {
            break;
        }
        if (root->GetValue() > value)
        {
            root = root->GetLeft();
        }
        else
        {
            root = root->GetRight();
        }
    }
    return root;
}

int _tmain(int argc, _TCHAR* argv[])
{
    Tree<LinkNode<int>> linkTree(new LinkNode<int>());
    Tree<MAryNode<int, 3>> mAryTree(new MAryNode<int, 3>());
    Tree<TrickyNode<int>> trickyTree(new TrickyNode<int>());

    Tree<FullNode<int>>* simpleTree = TreeConstructor(L"0-l1,0-r2,1-l3,1-r4,2-l5,2-r6");
    Tree<FullNode<int>>* deepTree = TreeConstructor(L"0-l1,0-r2,1-l3,2-r4,3-l5,4-r6,5-l7,6-l8,6-r9");
    Tree<FullNode<int>>* sparseTree = TreeConstructor(L"0-l1,0-r2,1-l3,1-r4,2-l5,2-r6,3-r7,4-l8,5-l9,6-r10");

    wprintf(L"PreOrder:\n");
    PrintPreOrderRecursive(simpleTree->Root()); wprintf(L"\n");
    PrintPreOrderIterativeStack(simpleTree->Root()); wprintf(L"\n");
    PrintPreOrderParentPointer(simpleTree->Root()); wprintf(L"\n");
    PrintPreOrderRecursive(deepTree->Root()); wprintf(L"\n");
    PrintPreOrderIterativeStack(deepTree->Root()); wprintf(L"\n");
    PrintPreOrderParentPointer(deepTree->Root()); wprintf(L"\n");

    wprintf(L"InOrder:\n");
    PrintInOrderRecursive(simpleTree->Root()); wprintf(L"\n");
    PrintInOrderIterativeStack(simpleTree->Root()); wprintf(L"\n");
    PrintInOrderParentPointer(simpleTree->Root()); wprintf(L"\n");
    PrintInOrderParentPointer_Reduced(simpleTree->Root()); wprintf(L"\n");
    PrintInOrderRecursive(deepTree->Root()); wprintf(L"\n");
    PrintInOrderIterativeStack(deepTree->Root()); wprintf(L"\n");
    PrintInOrderParentPointer(deepTree->Root()); wprintf(L"\n");
    PrintInOrderParentPointer_Reduced(deepTree->Root()); wprintf(L"\n");

    wprintf(L"PostOrder:\n");
    PrintPostOrderRecursive(simpleTree->Root()); wprintf(L"\n");
    PrintPostOrderIterativeStack(simpleTree->Root()); wprintf(L"\n");
    PrintPostOrderParentPointer(simpleTree->Root()); wprintf(L"\n");
    PrintPostOrderRecursive(deepTree->Root()); wprintf(L"\n");
    PrintPostOrderIterativeStack(deepTree->Root()); wprintf(L"\n");
    PrintPostOrderParentPointer(deepTree->Root()); wprintf(L"\n");
    PrintPostOrderRecursive(sparseTree->Root()); wprintf(L"\n");
    PrintPostOrderIterativeStack(sparseTree->Root()); wprintf(L"\n");
    PrintPostOrderParentPointer(sparseTree->Root()); wprintf(L"\n");

    wprintf(L"BFS:\n");
    PrintBFSIterativeQueue(simpleTree->Root()); wprintf(L"\n");
    PrintBFSLogLinear(simpleTree->Root()); wprintf(L"\n");
    PrintBFSIterativeQueue(deepTree->Root()); wprintf(L"\n");
    PrintBFSLogLinear(deepTree->Root()); wprintf(L"\n");
    PrintBFSIterativeQueue(sparseTree->Root()); wprintf(L"\n");
    PrintBFSLogLinear(sparseTree->Root()); wprintf(L"\n");

    wprintf(L"Zig Zag:\n");
    PrintZigZagTree(simpleTree->Root()); wprintf(L"\n");
    PrintZigZagTree(deepTree->Root()); wprintf(L"\n");
    PrintZigZagTree(sparseTree->Root()); wprintf(L"\n");

    getchar();

    return 0;
}

