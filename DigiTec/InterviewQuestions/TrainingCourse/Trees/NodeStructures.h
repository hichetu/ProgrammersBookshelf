template <typename TRoot>
class Tree
{
public:
	Tree(TRoot* root) : m_root(root)
	{
	}

	TRoot* Root()
	{
		return m_root;
	}

private:
	TRoot* m_root;
};

template <typename TValue>
class FullNode
{
public:
	FullNode(FullNode<TValue>* parent) : 
		m_value(TValue()), m_parent(parent), 
		m_left(nullptr), m_right(nullptr)
	{
	}

	void SetValue(const TValue& value)
	{
		m_value = value;
	}
	TValue GetValue()
	{
		return m_value;
	}
	void SetParent(FullNode<TValue>* node)
	{
		m_parent = node;
	}
	void SetLeft(FullNode<TValue>* node)
	{
		m_left = node;
	}
	FullNode<TValue>* GetLeft()
	{
		return m_left;
	}
	void SetRight(FullNode<TValue>* node)
	{
		m_right = node;
	}
	FullNode<TValue>* GetRight()
	{
		return m_right;
	}

private:
	TValue m_value;
	FullNode<TValue>* m_parent;
	FullNode<TValue>* m_left;
	FullNode<TValue>* m_right;
};

template <typename TValue>
class TraversalNode
{
public:
	TraversalNode() : m_value(TValue()), 
		m_left(nullptr), m_right(nullptr)
	{
	}

private:
	TValue m_value;
	TraversalNode<TValue>* m_left;
	TraversalNode<TValue>* m_right;
};

template <typename TValue, unsigned long TMAry>
class MAryNode
{
public:
	MAryNode() : m_value(TValue())
	{
		memset(m_children, 0, sizeof(m_children));
	};

private:
	TValue m_value;
	MAryNode<TValue, TMAry>* m_children[TMAry];
};

template <typename TValue>
class LinkNode
{
public:
	LinkNode() : m_value(TValue()), 
		m_pNextSibling(nullptr), m_pFirstChild(nullptr)
	{
	};

private:
	TValue m_value;
	LinkNode<TValue>* m_pNextSibling;
	LinkNode<TValue>* m_pFirstChild;
};

template <typename TValue>
class TrickyNode
{
public:
	TrickyNode() : m_value(TValue()), m_pFirstChild(nullptr), 
		m_pParentOrNextSibling(nullptr), m_isLeftChild(false), 
		m_hasNextSibling(false)
	{
	}
	
	bool isRoot()
	{
		// For this tree, you either point to your 
		// parent or sibling, unless you are the root
		return (m_pParentOrNextSibling == nullptr);
	}

	TrickyNode<TValue>* LeftChild() const
	{
		if (m_pFirstChild != nullptr && m_pFirstChild->m_isLeftChild)
		{
			return m_pFirstChild;
		}
		return nullptr;
	}

	TrickyNode<TValue>* RightChild() const
	{
		if (m_pFirstChild != nullptr)
		{
			if (!m_pFirstChild->m_isLeftChild)
			{
				return m_pFirstChild;
			}
			else if (!m_pFirstChild->m_hasNextSibling)
			{
				m_pFirstChild->m_pParentOrNextSibling;
			}
		}
		return nullptr;
	}

	TrickyNode<TValue>* Parent() const
	{
		if (!m_pParentOrSibling || !m_hasNextSibling)
		{
			return m_pParentOrSibling;
		}
		else
		{
			return m_pParentOrSibling->m_pParentOrSibling;
		}
	}

private:
	TValue m_value;
	TrickyNode<TValue>* m_pFirstChild;
	TrickyNode<TValue>* m_pParentOrNextSibling;
	bool m_isLeftChild;
	bool m_hasNextSibling;
};