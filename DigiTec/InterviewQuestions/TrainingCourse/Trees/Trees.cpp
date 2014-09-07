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

void PrintInOrderRecursive(FullNode<int>* root)
{
	if (root != nullptr)
	{
		PrintInOrderRecursive(root->GetLeft());
		wprintf(L"%d", root->GetValue());
		PrintInOrderRecursive(root->GetRight());
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

int _tmain(int argc, _TCHAR* argv[])
{
	Tree<LinkNode<int>> linkTree(new LinkNode<int>());
	Tree<MAryNode<int, 3>> mAryTree(new MAryNode<int, 3>());
	Tree<TrickyNode<int>> trickyTree(new TrickyNode<int>());

	Tree<FullNode<int>>* newTree = TreeConstructor(L"0-l1,0-r2,1-l3,1-r4,2-l5,2-r6");
	
	PrintPreOrderRecursive(newTree->Root()); wprintf(L"\n");
	PrintPreOrderIterativeStack(newTree->Root()); wprintf(L"\n");

	PrintInOrderRecursive(newTree->Root()); wprintf(L"\n");
	PrintInOrderIterativeStack(newTree->Root()); wprintf(L"\n");

	PrintPostOrderRecursive(newTree->Root()); wprintf(L"\n");

	PrintBFSIterativeQueue(newTree->Root()); wprintf(L"\n");
	PrintBFSLogLinear(newTree->Root()); wprintf(L"\n");

	getchar();

	return 0;
}

