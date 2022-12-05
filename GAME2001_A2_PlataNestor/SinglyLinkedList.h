#pragma once
#include <cassert>

// Template Class Declarations
template <class T> class LinkIterator;
template <class T> class LinkedList;
template <class T> class PriorityQueue;

// Define a node
template <class T>
class LinkNode
{
public:
	// Give access to the private member variables
	friend class LinkIterator<T>;
	friend class LinkedList<T>;
	friend class PriorityQueue<T>;
private:
	T m_data;
	LinkNode* m_next;	// Self-referencial Pointer
	int m_priority;
};

// Define an iterator
template <class T>
class LinkIterator
{
public:
	LinkIterator()
	{
		m_node = nullptr;
	}
	~LinkIterator() {}
	// ----------- OVERLOADED OPERATORS ------------------
	// Assignmnet operator (=) <-- Set the iterator to point to a node  // a = b
	void operator=(LinkNode<T>* node)
	{
		m_node = node;
	}
	// Dereferencing operator (*) <-- Read the data stored on the node being pointed too // itr*
	T& operator*()
	{
		assert(m_node != nullptr);
		return m_node->m_data;
	}
	// Incremental operator (++) Prefix and Postfox <-- Move the iterator to the next node
	void operator++()	// Prefix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}
	void operator++(int) // Postfix
	{
		assert(m_node != nullptr);
		m_node = m_node->m_next;
	}
	// Comparison Operator (!= & ==) <-- Check whether the node we are pointing too is equal to a node we pass in
	bool operator!=(LinkNode<T>* node)
	{
			return (m_node != node);
	}

	bool operator==(LinkNode<T>* node)
	{
		return (m_node == node);
	}

private:
	LinkNode<T>* m_node;	// Pointer to a node in the linked list
};

// Define a linked list itself
template <class T>
class LinkedList
{
public:
	// Constructor and Destructor
	LinkedList() : m_size(0), m_root(nullptr), m_lastNode(nullptr) {}
	~LinkedList()
	{
		while (m_root)
		{
			// Pop()
		}
	}
	// --------------- POSITIONING FUNCTIONS ----------------------

	virtual LinkNode<T>* End()
	{
		return nullptr;
	}
	virtual LinkNode<T>* Back()
	{
		assert(m_lastNode != nullptr);
		return m_lastNode;
	}

	virtual LinkNode<T>* Front()
	{
		assert(m_root != nullptr);
		return m_root;
	}
	virtual void Push(T newData, int priority)
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != nullptr);
		node->m_data = newData;
		node->m_next = nullptr;
		node->m_priority = priority;

		// Add the new LinkNode to the existing LinkedList
		if (m_lastNode != nullptr) // LinkedList is populated. Push to the end of the list.
		{
			m_lastNode->m_next = node;
			m_lastNode = node;
		}
		else // An empty linked list
		{
			m_root = node;
			m_lastNode = node;
		}

		m_size++;
	}
	virtual void Pop()
	{
		assert(m_root != nullptr);

		// Check if there is only 1 node (aka just a root)
		if (m_root->m_next == nullptr)
		{
			delete m_root;
			m_root = nullptr;
			m_lastNode = nullptr;
		}
		else // Linked list has 2 or more items
		{
			LinkNode<T>* prevNode = m_root;

			// Traverse the linked list until we reach the end
			while (prevNode->m_next != nullptr && prevNode->m_next != m_lastNode)
			{
				prevNode = prevNode->m_next;
			}

			// The previous while loop simply positions the poinster to the 2nd last node in the list
			delete m_lastNode;
			prevNode->m_next = nullptr;
			m_lastNode = prevNode;

			prevNode = nullptr;
		}

		m_size = (m_size == 0 ? m_size : m_size - 1);// Prevent negative sizes
	}



private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};

template <class T>
class PriorityQueue  :public LinkedList<T>
{
public:
	PriorityQueue() : m_size(0), m_root(nullptr), m_lastNode(nullptr) {}

	// --------------- LINKED LIST OPERATIONS ---------------------

	virtual LinkNode<T>* End()
	{
		return nullptr;
	}
	virtual LinkNode<T>* Back()
	{
		assert(m_lastNode != nullptr);
		return m_lastNode;
	}

	virtual LinkNode<T>* Front()
	{
		assert(m_root != nullptr);
		return m_root;
	}
	void Push(T newData, int priority)
	{
		// Create a standalone LinkNode object
		LinkNode<T>* node = new LinkNode<T>;

		assert(node != nullptr);
		node->m_data = newData;
		node->m_next = nullptr;
		node->m_priority = priority;

		// Add the new LinkNode to the existing LinkedList
		if (m_lastNode != nullptr) // LinkedList is populated. Push to the end of the list.
		{
			LinkNode<T>* temp2 = m_lastNode;
			LinkNode<T>** temp3 = &temp2;
			while (temp2 && temp2->m_priority < node->m_priority)
			{
				temp3 = &temp2->m_next;
				temp2 = temp2->m_next;
			}
			*temp3 = node;
			node->m_next = temp2;
		}
		else // An empty linked list
		{
			m_root = node;
			m_lastNode = node;
		}

		m_size++;
	}
	virtual void Pop()
	{
		assert(m_root != nullptr);

		// Check if there is only 1 node (aka just a root)
		if (m_root->m_next == nullptr)
		{
			delete m_root;
			m_root = nullptr;
			m_lastNode = nullptr;
		}
		else // Linked list has 2 or more items
		{
			LinkNode<T>* prevNode = m_root;
			m_root = m_root->m_next;
			delete prevNode;
		}

		m_size = (m_size == 0 ? m_size : m_size - 1);	// Prevent negative sizes
	}


private:
	int m_size;					// Holds the size of the linked list
	LinkNode<T>* m_root;		// Point to the root of the linked list
	LinkNode<T>* m_lastNode;	// Point to the last node of the linked list
};