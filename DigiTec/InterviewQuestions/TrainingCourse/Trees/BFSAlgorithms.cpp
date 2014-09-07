#include "stdafx.h"

void PrintBFSIterativeQueue(FullNode<int>* root)
{
	vector<FullNode<int>*> queue;
	queue.push_back(root);
	while (queue.size() > 0)
	{
		FullNode<int>* current = queue.front();
		queue.erase(queue.begin());

		wprintf(L"%d", current->GetValue());
		if (current->GetLeft() != nullptr)
		{
			queue.push_back(current->GetLeft());
		}
		if (current->GetRight() != nullptr)
		{
			queue.push_back(current->GetRight());
		}
	}
}

FullNode<int>* NextInLevel(FullNode<int>* node)
{
	if (node == nullptr || node->GetParent() == nullptr)
	{
		return nullptr;
	}

	if (node->GetParent()->GetRight() != node && node->GetParent()->GetRight() != nullptr)
	{
		return node->GetParent()->GetRight();
	}
	else
	{
		FullNode<int>* nextInParentLevel = NextInLevel(node->GetParent());
		while (nextInParentLevel != nullptr)
		{
			if (nextInParentLevel->GetLeft() != nullptr)
			{
				return nextInParentLevel->GetLeft();
			}
			else if (nextInParentLevel->GetRight() != nullptr)
			{
				return nextInParentLevel->GetRight();
			}
			else
			{
				nextInParentLevel = NextInLevel(nextInParentLevel);
			}
		}
		return nullptr;
	}
}
void PrintBFSLogLinear(FullNode<int>* root)
{
	FullNode<int>* nextLevel = root;
	while (nextLevel != nullptr)
	{
		FullNode<int>* currentLevel = nextLevel;
		nextLevel = nullptr;

		while (currentLevel != nullptr)
		{
			wprintf(L"%d", currentLevel->GetValue());
			if (nextLevel == nullptr)
			{
				if (currentLevel->GetLeft() != nullptr)
				{
					nextLevel = currentLevel->GetLeft();
				}
				else
				{
					nextLevel = currentLevel->GetRight();
				}
			}
			currentLevel = NextInLevel(currentLevel);
		}
	}
}
