//
// Created by atory on 3/24/22.
//

#pragma once

#include <memory>
#include "Utils/pair.hpp"

#define RED	"\033[31m"
#define DEF	"\033[0m"

namespace ft {

	enum	Color	{Red, Black};

	template < class Type >
	struct treeNode {
		Type*		_data;
		treeNode*	_parent;
		treeNode*	_left;
		treeNode*	_right;
		bool		_color;
		size_t 		_height;

		explicit treeNode(Type* data, treeNode* parent = nullptr):	_data(data),
																	_parent(parent),
																	_left(nullptr),
																	_right(nullptr),
																	_color(Red) {}
//		treeNode&	operator=(const treeNode& other)
//		{
//			if (this == &other)
//				return *this;
//			_data = Type(other._data);
//			_parent = other._parent;
//			_left = other._left;
//			_right = other._right;
//			_color = other._color;
//			_height = other._height;
//			return *this;
//		}

		Type&	operator*()
		{
			return *_data;
		}
	};


	template < class Type, class Alloc = std::allocator<Type> >
	class RedBlackTree {

		//_1_Member_types_______________________________________________________________________________________________
		// Type = ft::pair <Key, Value>
		typedef	RedBlackTree <Type, Alloc>		thisType;
//		typedef typename Comp::keyCompare		keyCompare;
		typedef typename Alloc::size_type		sizeType;

		typedef typename Alloc::pointer			pointer;
		typedef treeNode<Type>*					nodePtr;
		typedef treeNode<Type>					Node;

	public:

		//_2_Constructors_______________________________________________________________________________________________
		explicit RedBlackTree(const Alloc& A = Alloc()): _allocator(A), _root(nullptr) {}
		~RedBlackTree() { Clear(_root); }

		bool	getColor(const nodePtr& node) const
		{
			if (!node)
				return Black;
			return node->_color;
		}

		void	setColor(const nodePtr& node, bool color)
		{
			if (!node)
				return ;
			node->_color = color;
		}

		void	insert(const Type& X)
		{
			nodePtr	newNode = Construct(X);
			_root = Insert(newNode, _root);
			fixViolation(newNode);
		}

		void	print()
		{
			printNode(_root);
			std::cout << "\n";
		}

		void	printNode(nodePtr& node)
		{
			if (!node)
				return ;
			PrintNode(node);
			printNode(node->_left);
			printNode(node->_right);
		}


	protected:
		void	rotateLeft(const nodePtr& node) {
			nodePtr	rightChild = node->_right;
			node->_right = rightChild->_left;

			if (!node->_right)
				node->_right->_parent = node;

			rightChild->_parent = node->_parent;
			if (!node->_parent)
				this->_root = rightChild;
			else if (node == node->_parent->_left)
				node->_parent->_left = rightChild;
			else
				node->_parent->_right = rightChild;

			rightChild->_left = node;
			node->_parent = rightChild;
		}

		void	rotateRight(const nodePtr& node) {
			nodePtr	leftChild = node->_left;
			node->_left = leftChild->_right;

			if (!node->_left)
				node->_left->_parent = node;

			leftChild->_parent = node->_parent;
			if (!node->_parent)
				this->_root = leftChild;
			else if (node == node->_parent->_left)
				node->_parent->_left = leftChild;
			else
				node->_parent->_right = leftChild;

			leftChild->_right = node;
			node->_parent = leftChild;
		}

		void fixViolation(nodePtr& node) {

			nodePtr parent;
			nodePtr granny;
			nodePtr uncle;

			while (node != this->_root && getColor(node) != Red && getColor(node->_parent) == Red) {
				parent = node->_parent;
				granny = parent->_parent;
				if (parent == granny->_left) {
					uncle = granny->_right;
					if (getColor(uncle) == Red) {
						setColor(uncle, Black);
						setColor(parent, Black);
						setColor(granny, Red);
						node = granny;
					}
					else {
						if (node == parent->_right) {
							rotateLeft(parent);
							node = parent;
							parent = node->_parent;
						}
						rotateRight(granny);
						std::swap(parent->_color, granny->_color);
						node = parent;
					}
				}
				else {
					uncle = granny->_left;
					if (getColor(uncle) == Red) {
						setColor(uncle, Black);
						setColor(parent, Black);
						setColor(granny, Red);
						node = granny;
					}
					else {
						if (node == parent->_left) {
							rotateRight(parent);
							node = parent;
							parent = node->_parent;
						}
						rotateLeft(granny);
						std::swap(parent->_color, granny->_color);
						node = parent;
					}
				}
			}
			setColor(this->_root, Black);
		}


	private:
		Alloc		_allocator;
		nodePtr		_root;
		nodePtr		_TNULL;

		void	Init(nodePtr node, nodePtr parent) {
			node->_data = nullptr;
			node->_parent = parent;
			node->_left = nullptr;
			node->_right = nullptr;
			node->_color = 0;
		}

		nodePtr	Construct(const Type& X, nodePtr parent = nullptr) {
			Type*	data = _allocator.allocate(1);
			_allocator.construct(data, X);
			return (new Node(data, parent));
		}

		void	Clear(nodePtr position)
		{
			if (!position)
				return ;
			Clear(position->_left);
			Clear(position->_right);
			Destroy(position);
		}

		void	Destroy(nodePtr position)
		{
			_allocator.destroy(position->_data);
			_allocator.deallocate(position->_data, 1);
			delete	position;
			position = nullptr;
		}

		nodePtr	Insert(nodePtr& newNode, nodePtr& position)
		{
			if (!position)
				return newNode;
			else if (*(newNode->_data) < *(position->_data)) {
				position->_left = Insert(newNode, position->_left);
				position->_left->_parent = position;
			}
			else if (*(newNode->_data) > *(position->_data)) {
				position->_right = Insert(newNode, position->_right);
				position->_right->_parent = position;
			}
			return position;
		}
		void	PrintNode(nodePtr& node)
		{
			if (!node)
				return;
			if (node->_parent) {
				node->_parent->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "parent: " << *(node->_parent->_data) << ", ";
			}
			if (node->_data) {
				node->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "current: " << *(node->_data) << ", ";
			}
			if (node->_left) {
				node->_left->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "left: " << *(node->_left->_data) << ", ";
			}
			if (node->_right) {
				node->_right->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "right: " << *(node->_right->_data);
			}
			std::cout << "\n";
		}

	};
}
