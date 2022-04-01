//
// Created by atory on 3/24/22.
//

#pragma once

#include <memory>
#include "tree_node.hpp"
#include "../Utils/pair.hpp"
#include "../Iterator/tree_iterator.hpp"
#include "tree_traits.hpp"

#define RED	"\033[31m"
#define DEF	"\033[0m"

namespace ft {

	template < class RedBlackTreeTraits >
	class RedBlackTree {
	public:

		//_1_Member_types_______________________________________________________________________________________________
		typedef	RedBlackTree < RedBlackTreeTraits >					self;

		typedef typename RedBlackTreeTraits::Data					Data;
		typedef typename RedBlackTreeTraits::Node					NodeType;
		typedef typename RedBlackTreeTraits::key_type				KeyType;
		typedef typename RedBlackTreeTraits::value_type				ValueType;
		typedef typename RedBlackTreeTraits::key_compare			key_compare;
		typedef typename RedBlackTreeTraits::sizeType				sizeType;
		typedef typename RedBlackTreeTraits::diffType				diffType;

		typedef typename RedBlackTreeTraits::pointer				nodePtr;
		typedef typename RedBlackTreeTraits::const_pointer			const_nodePtr;
		typedef typename RedBlackTreeTraits::reference				nodeRef;
		typedef typename RedBlackTreeTraits::const_reference		const_nodeRef;


		typedef typename RedBlackTreeTraits::self_type_allocator	allocPair;
		typedef typename RedBlackTreeTraits::allocator_for_node		allocNode;


		typedef ft::tree_iterator < Data, BiDirIter <NodeType, diffType, nodePtr, nodeRef> >				iterator;
		typedef ft::tree_iterator < Data, BiDirIter <NodeType, diffType, const_nodePtr, const_nodeRef> >	const_iterator;


		//_2_Constructors_______________________________________________________________________________________________
		explicit	RedBlackTree(const key_compare& comp = key_compare(), const allocPair& A = allocPair()):	_allocator(A),
																										_allocator_node(allocNode()),
																										_key_compare(comp),
																										_root(nullptr), _end(nullptr) {}
		explicit	RedBlackTree(self const& other):	_allocator(allocPair()),
														_allocator_node(allocNode()),
														_key_compare(key_compare()),
														_root(nullptr), _end(nullptr) {
			//(...)
		}
		~RedBlackTree() { Clear(_root); }

		//_3_Capacity___________________________________________________________________________________________________
		sizeType				size()	const			{ return Size(_root); }
		sizeType				max_size()	const		{ return _allocator_node.max_size(); }
		bool 					empty() const			{ return (size() == 0); }
		allocPair				get_allocator() const	{ return _allocator; } // todo : maybe allocNode?

		//_4_Element_access_____________________________________________________________________________________________

		iterator				begin()					{ return iterator(Min(this->_root)); }
		const_iterator			begin()	const			{ return const_iterator(Min(this->_root)); }
		iterator				end()					{ return iterator(this->_end); }
		const_iterator			end() const				{ return const_iterator(this->_end); }
//		const_reverse_iterator	rend() const			{ return const_reverse_iterator(this->begin()); }
//		reverse_iterator		rend()					{ return reverse_iterator(this->begin()); }
//		const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(this->end()); }
//		reverse_iterator		rbegin()				{ return reverse_iterator(this->end()); }
		iterator				min()					{ return iterator(Min(this->_root)); }
		iterator				max()					{ return iterator(Max(this->_root)); }

//		ref			at(sizeType N) throw(std::out_of_range) // same as vector[N]
//		{
//			if (this->size() <= N)
//				exception_range();
//			return *(this->begin() + N);
//		}

		//_6_Modifiers__________________________________________________________________________________________________

		void		clear()	{ Clear(this->_root); }
		void		insert(const ValueType& X)
		{
//			if (find)
//				return ;
			nodePtr	newNode = Construct(X);
			_root = Insert(newNode, _root);
			fixViolation(newNode);
		}

		iterator	find(KeyType const& key) const	{ return iterator(Find(key, this->_root)); }
		sizeType	count(KeyType const& key) const	{ return (sizeType)(Find(key, this->_root) != nullptr); }

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

	protected:
		void	rotateLeft(const nodePtr& node) {
			nodePtr	rightChild = node->_right;
			node->_right = rightChild->_left;

			if (node->_right)
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

			if (node->_left)
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

			// фиксируем правило - у каждого красного узла родитель черный
			// перекрашиваем узлы так, чтобы новый узел и родитель не нарушали это правило
			while (node != this->_root && getColor(node) == Red && getColor(node->_parent) == Red) {
				parent = node->_parent;
				granny = parent->_parent;
				// рассматриваем соседний по родителю узел "дядю"
				if (parent == granny->_left) {
					uncle = granny->_right;
					// если дядя тоже красный, перекрашиваем верхние ноды
					if (getColor(uncle) == Red) {
						setColor(uncle, Black);
						setColor(parent, Black);
						setColor(granny, Red);
						node = granny;
					}
					else { // если дядя черный, выталкиваем красный узел вверх кручением
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
		allocPair		_allocator;
		allocNode		_allocator_node;
		key_compare		_key_compare;
		nodePtr			_root;
		nodePtr			_end;

		void	Init(nodePtr node, nodePtr parent) {
			node->_data = nullptr;
			node->_parent = parent;
			node->_left = nullptr;
			node->_right = nullptr;
			node->_color = 0;
		}

		// Allocates memory and constructs new Node
		// with data = *X
		nodePtr	Construct(const ValueType& X, nodePtr parent = nullptr) {
			nodePtr newNode = _allocator_node.allocate(1);
			newNode->_data = _allocator.allocate(1);
			_allocator.construct(newNode->_data, ValueType(X));
			newNode->_parent = parent;
			newNode->_left = nullptr;
			newNode->_right = nullptr;
			newNode->_color = Red;
			return (newNode);
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
			position->_data = nullptr;
			_allocator_node.destroy(position);
			_allocator_node.deallocate(position, 1);
			position = nullptr;
		}

		nodePtr	Insert(nodePtr& newNode, nodePtr& position)
		{
			if (!position)
				return newNode;
			else if (RedBlackTreeTraits::key_compare(getKey(newNode), getKey(position))) {
				position->_left = Insert(newNode, position->_left);
				position->_left->_parent = position;
			}
			else if (RedBlackTreeTraits::key_compare(getKey(position)), getKey(newNode)) {
				position->_right = Insert(newNode, position->_right);
				position->_right->_parent = position;
			}
			return position;
		}

		nodePtr		Find(KeyType const& key, const nodePtr& position) const {
			if (!position)
				return position;
			RedBlackTreeTraits::key_compare(key, getKey(position)) ? Find(key, position->_left) : Find(key, position->_right);
		}

		sizeType	Size(const nodePtr& position) const {
			return position ? Size(position->_right) + Size(position->_left) + 1 : 0 ;
		}

		nodePtr		Min(const nodePtr& position) const {
			return position && position->_left ? Min(position->_left) : position;
		}

		nodePtr		Max(const nodePtr& position) const {
			return position && position->_right ? Max(position->_right) : position;
		}

		KeyType&	getKey(const nodePtr & position) { return RedBlackTreeTraits::GetKey(position); }

		void	PrintNode(nodePtr& node)
		{
			if (!node)
				return;
//			if (node->_parent) {
//				node->_parent->_color == Red ? std::cout << RED : std::cout << DEF;
//				std::cout << "parent: " << *(node->_parent->_data->_first) << ", ";
//			}
			if (node->_data) {
				node->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "current: " << getKey(node) << ", ";
			}
			if (node->_left) {
				node->_left->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "left: " << getKey(node->_left) << ", ";
			}
			if (node->_right) {
				node->_right->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "right: " << getKey(node->_right);
			}
			std::cout << "\n";
		}

	};
}
