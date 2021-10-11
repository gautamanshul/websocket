#include <iostream>
#include <string>
#include <vector>

template <typename T> struct BinaryTree;

template <typename T> struct Node
{
	T value = T();
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	Node<T>* parent = nullptr;
	BinaryTree<T>* tree = nullptr;

	~Node()
	{
		if (left) delete left;
		if (right) delete right;
	}

	explicit Node(const T& value) : value(value)
	{}

	Node(const T& value, Node<T>* const left, Node<T>* const right):value(value), left(left), right(right)
	{
		this->left->parent = this->right->parent = this;
	}

	void set_tree(BinaryTree<T>* t)
	{
		tree = t;
		if (left) left->set_tree(t);
		if (right) right->set_tree(t);
	}
};

template <typename T> struct BinaryTree
{
	Node<T>* root = nullptr;

	template <typename U> struct BinaryTreeIterator
	{
		Node<U>* current = nullptr;

		explicit BinaryTreeIterator( Node<U> * const current) : current(current) {}

		bool operator != (const BinaryTreeIterator<U>& other) 
		{
			return current != other.current;
		}

		Node<U>& operator *() { return *current; }

		BinaryTreeIterator<U>& operator++()
		{
			if (current->right)
			{
				current = current->right;
				while (current->left)
					current = current->left;
			}
			else
			{
				Node<T>* p = current->parent;
				while (p && current == p->right)
				{
					current = p;
					p = p->parent;
				}
				current = p;
			}
			return *this;
		}
	};

	typedef BinaryTreeIterator<T> iterator;

	explicit BinaryTree( Node<T>* const root ) : root( root )
	{
		root->set_tree( this );
	}

	~BinaryTree()
	{
		if (root) delete root;
	}

	iterator end()
	{
		return iterator{ nullptr };
	}

	iterator begin()
	{
		Node<T>* n = root;

		if (n)
			while (n->left)
				n = n->left;

		return iterator{ n };
	}

	
};

int main3()
{
	BinaryTree<std::string> family{
		new Node<std::string> {"me",
			new Node<std::string> {"mother",
				new Node<std::string> {"mother's mother"},
				new Node <std::string> {"mother's father"}
			},
			new Node<std::string> {"father"}
		}
	};

	for (auto it = family.begin(); it != family.end(); ++it)
	{
		std::cout << (*it).value << std::endl;
	}
	getchar();
	return 0;
}