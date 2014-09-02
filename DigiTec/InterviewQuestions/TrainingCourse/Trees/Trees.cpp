// Trees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include "NodeStructures.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Tree<LinkNode<int>> linkTree(new LinkNode<int>());
	Tree<MAryNode<int, 3>> mAryTree(new MAryNode<int, 3>());
	Tree<TrickyNode<int>> trickyTree(new TrickyNode<int>());

	return 0;
}

