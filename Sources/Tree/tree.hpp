//
// Created by atory on 3/24/22.
//

#pragma once

#include <memory>
#include "tree_node.hpp"
#include "../Utils/pair.hpp"
#include "../Iterator/tree_iterator.hpp"
#include "tree_traits.hpp"
#include "../Utils/enable_if.hpp"
#include "../Utils/is_integral.hpp"
#include "../Utils/equal.hpp"
#include "../Utils/lexicographical_compare.hpp"

#define RED		"\033[31m"
#define DEF		"\033[0m"

namespace ft {

	template < class RedBlackTreeTraits >
	class RedBlackTree : public RedBlackTreeTraits {
	public:

		//_1_Member_types_______________________________________________________________________________________________
		typedef	RedBlackTree < RedBlackTreeTraits >					Self;

		typedef typename RedBlackTreeTraits::Data					Data;
		typedef typename RedBlackTreeTraits::Node					node_type;
		typedef typename RedBlackTreeTraits::key_type				key_type;
		typedef typename RedBlackTreeTraits::value_type				value_type;
		typedef typename RedBlackTreeTraits::key_compare			key_compare;
		typedef typename RedBlackTreeTraits::size_type				size_type;
		typedef typename RedBlackTreeTraits::difference_type		difference_type;

		typedef typename RedBlackTreeTraits::nodePtr				nodePtr;
		typedef typename RedBlackTreeTraits::const_nodePtr			const_nodePtr;
		typedef typename RedBlackTreeTraits::nodeRef				nodeRef;
		typedef typename RedBlackTreeTraits::const_nodeRef			const_nodeRef;


		typedef typename RedBlackTreeTraits::self_type_allocator	allocPair;
		typedef typename RedBlackTreeTraits::allocator_for_node		allocNode;


		typedef ft::tree_iterator < Data, Self, BiDirIter <node_type, difference_type, nodePtr, nodeRef> >				iterator;
		typedef ft::tree_iterator < Data, Self, BiDirIter <node_type, difference_type, const_nodePtr, const_nodeRef> >	const_iterator;
//		typedef ft::reverse_iterator < iterator >																		reverse_iterator;
//		typedef ft::reverse_iterator < const_iterator >																	const_reverse_iterator;


		//_2_Constructors_______________________________________________________________________________________________
		RedBlackTree():	_allocator(allocPair()),
									_allocator_node(allocNode()),
									_key_compare(key_compare()),
									_root(nullptr), _end(nullptr) {}
		explicit	RedBlackTree(const key_compare& comp, const allocPair& A = allocPair()):
																						_allocator(A),
																						_allocator_node(allocNode()),
																						_key_compare(comp),
																						_root(nullptr), _end(nullptr) {}
		RedBlackTree(Self const& other):	_allocator(allocPair()),
											_allocator_node(allocNode()),
											_key_compare(key_compare()),
											_root(nullptr), _end(nullptr)
		{
			if (this->_root != nullptr || other.size() == 0)
				clear();
			if (other._root != nullptr) {
				this->_root = Construct(*(other._root->_data));
				Copy(this->_root, other._root);
			}
		}
		~RedBlackTree() { clear(); }

		//_3_Capacity___________________________________________________________________________________________________
		size_type				size()	const			{ return Size(_root); }
		size_type				max_size()	const		{ return _allocator_node.max_size(); }
		bool 					empty() const			{ return (size() == 0); }
		allocPair				get_allocator() const	{ return _allocator; }

		//_4_Element_access_____________________________________________________________________________________________
		iterator				begin()					{ return iterator(Min(this->_root), this); }
		const_iterator			cbegin()	const		{ return const_iterator(Min(this->_root), this); }
		iterator				end()					{ return iterator(this->_end, this); }
		const_iterator			cend() const			{ return const_iterator(this->_end, this); }
//		const_reverse_iterator	rend() const			{ return const_reverse_iterator(this->begin()); }
//		reverse_iterator		rend()					{ return reverse_iterator(this->begin()); }
//		const_reverse_iterator	rbegin() const			{ return const_reverse_iterator(this->end()); }
//		reverse_iterator		rbegin()				{ return reverse_iterator(this->end()); }
		nodePtr 				min() const				{ return Min(this->_root); }
		nodePtr 				max() const				{ return Max(this->_root); }

		key_type&				getKey(nodePtr position) const				{ return RedBlackTreeTraits::GetKey(position); }
		key_type const&			getKey(Data const& position_data) const		{ return RedBlackTreeTraits::GetKey(position_data); }
		value_type&				getValue(nodePtr position) const			{ return RedBlackTreeTraits::GetValue(position); }
		value_type const&		getValue(Data const& position_data) const	{ return RedBlackTreeTraits::GetValue(position_data); }

		value_type&				at(const key_type& key) throw(std::out_of_range) // same as tree[N]
		{
			if (find(key) == this->end())
				throw std::out_of_range("out of range");
			return getValue(Find(key, this->_root));
		}
		const value_type&		at(const key_type& key) const throw(std::out_of_range) // same as tree[N]
		{
			if (find(key) == this->end())
				throw std::out_of_range("out of range");
			return getValue(Find(key, this->_root));
		}

		value_type&				operator[]( const key_type& key)
		{
			if (find(key) == this->end())
				insert(ft::make_pair(key, value_type()));
			return getValue(Find(key, this->_root)); }


		//_5_Member_functions___________________________________________________________________________________________
		//__Assignment_operator_____________________
		Self&	operator=(const Self& other)
		{
			if (this == &other)
				;
			else if (this->_root || other.size() == 0)
				clear(); // destroy elements
			if (other._root != nullptr) {
				this->_root = Construct(*(other._root->_data));
				Copy(this->_root, other._root);
			}
			this->_key_compare = other._key_compare;
			return *this;
		};

		//_6_Modifiers__________________________________________________________________________________________________
		void						clear()
		{
			Clear(this->_root);
			this->_root = nullptr;
			Clear(this->_end);
			this->_end = nullptr;
		}
		//__Insert__________________________________________
		iterator					insert(Data const& X, iterator position) { (void)position ; return (insert(X).first); }
		ft::pair<iterator, bool>	insert(Data const& X)
		{
			if (find(getKey(X)) != this->end())
				return (ft::make_pair(find(getKey(X)), true));
			nodePtr	newNode = Construct(X);
			_root = Insert(newNode, _root);
			fixViolation(newNode);

			return (ft::make_pair(iterator(newNode, this), true));
		}
		template < class Iter >
		void						insert(Iter first, Iter last,
		typename ft::enable_if<!ft::is_integral<Iter>::value >::type* = 0)
		{
			for (; first != last; first++)
				insert(*first);
		}

		//__Erase___________________________________________
		void 		erase(iterator position) { _root = Remove(this->_root, position); }
		size_type	erase(const key_type& key)
		{

			size_type	size = this->size();
			_root = Remove(this->_root, Find(key, this->_root));
			return (size == this->size());
		}
		void		erase(iterator first, iterator last)
		{
			for (; first != last; ++first)
				erase(first);
		}

		//_7_LookUp_____________________________________________________________________________________________________
		iterator		find(key_type const& key)				{ return iterator(Find(key, this->_root), this); }
		const_iterator	find(key_type const& key) const			{ return const_iterator(Find(key, this->_root), this); }
		size_type		count(key_type const& key) const		{ return (size_type)(Find(key, this->_root) != nullptr); }
		bool 			contains(key_type const& key) const		{ return Find(key, this->_root) != nullptr; }

		iterator		lower_bound(key_type const& key) {
			iterator	it = begin();
			for (; it != end() && _key_compare(getKey(*it), key); ++it) {}
			return it;
		}
		iterator		upper_bound(key_type const& key) {
			iterator	it = lower_bound(key);
			return getKey(*it) == key && it != end() ? ++it : it;
		}
		const_iterator	lower_bound(key_type const& key) const {
			const_iterator	it = cbegin();
			for (; it != cend() && _key_compare(getKey(*it), key); ++it) {}
			return it;
		}
		const_iterator	upper_bound(key_type const& key) const {
			const_iterator	it = lower_bound(key);
			return getKey(*it) == key && it != cend() ? ++it : it;
		}

//		ft::pair<iterator, iterator>				equal_range(key_type const& key) {
//			return ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key));
//		}
		ft::pair<const_iterator, const_iterator>	equal_range(key_type const& key) const {
			const_iterator	itLow = lower_bound(key);
			const_iterator	itUp = upper_bound(key);
			return ft::make_pair<const_iterator, const_iterator>(itLow, itUp);
		}

		//_8_Observers__________________________________________________________________________________________________
		key_compare		key_comp() const	{ return _key_compare; }
//		value_compare	value_comp() const	{ return _value_compare; }
		void swap(Self &X) {(void)X;}


		typedef struct	help {
			std::string	s;
			help*		next;
		} help;

		void	print()
		{
			std::cout << "ROOT\n";
			printNode(_end, _root, 0, 0, false);
			std::cout << "\n";
		}

		void	printNode(nodePtr& parent, nodePtr& node, int depth, int rights, bool left)
		{
			if (depth) {
				for (int i = 0; i < depth - 1; i++) {
					if (rights-- > 0)
						std::cout << "    ";
					else if (parent != this->_root)
						std::cout << " │  ";
				}
				if (parent) {
					if (!left)
						std::cout << " ├──";
					else
						std::cout << " └──";
				}
			}
			PrintNode(node);
			if (!node)
				return ;
			printNode(node, node->_right, depth + 1, rights, false);
			printNode(node, node->_left, depth + 1, rights + 2,true);
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

			if (node == nullptr)
				return;
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

		void fixRemove(nodePtr& position, nodePtr node, nodePtr parent) {

			nodePtr	otherNode;
			printf("111\n");
			while ((!node) || (node->_color == Black && node != position)) {
				if (parent && parent->_left == node) {

					otherNode = parent->_right;
					if (otherNode->_color == Red) {
						otherNode->_color = Black;
						parent->_color = Red;
						rotateLeft(parent);
						otherNode = parent->_right;
					}
					else {

						if (!otherNode->_right || otherNode->_right->_color == Black) {
							otherNode->_left->_color = Black;
							otherNode->_color = Red;
							rotateRight(otherNode);
							otherNode = parent->_right;
						}

						otherNode->_color = parent->_color;
						parent->_color = Black;
						otherNode->_right->_color = Black;
						rotateLeft(parent);
						node = position;
						break ;
					}
				}
				else {
					otherNode = parent->_left;
					if (otherNode->_color == Red) {
						otherNode->_color = Black;
						parent->_color = Red;
						rotateRight(parent);
						otherNode = parent->_left;
					}
					if (!otherNode->_left || (otherNode->_left->_color == Black &&
					(!otherNode->_right || otherNode->_right->_color == Black))) {
						otherNode->_color = Red;
						node = parent;
						parent = node->_parent;
					}
					else {
						if (!otherNode->_left || otherNode->_left->_color == Black) {
							otherNode->_right->_color = Black;
							otherNode->_color = Red;
							rotateLeft( otherNode);
							otherNode = parent->_left;
						}

						otherNode->_color = parent->_color;
						parent->_color = Black;
						otherNode->_left->_color = Black;
						rotateRight(parent);
						node = position;
						break;
					}
				}
			}
			if (node)
				node->_color = Black;
		}


	private:
		allocPair		_allocator;
		allocNode		 _allocator_node;
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
		nodePtr	Construct(const Data& X, nodePtr parent = nullptr) {
			nodePtr newNode = _allocator_node.allocate(1);
			_allocator_node.construct(newNode, node_type());
			newNode->_parent = parent;
			newNode->_left = nullptr;
			newNode->_right = nullptr;
			newNode->_data = nullptr;
			newNode->_color = Red;
			newNode->_data = _allocator.allocate(1);
			_allocator.construct(newNode->_data, Data(X));
			return (newNode);
		}

		void	Clear(nodePtr position)
		{
			if (position == nullptr)
				return ;
			Clear(position->_left);
			Clear(position->_right);
			Destroy(position);
		}

		void	Destroy(nodePtr position)
		{
			if (position == nullptr)
				return ;
			if (position->_data) {
				_allocator.destroy(position->_data);
				_allocator.deallocate(position->_data, 1);
			}
			position->_data = nullptr;
			_allocator_node.destroy(position);
			_allocator_node.deallocate(position, 1);
			position = nullptr;
		}

		void	Copy(nodePtr& newNode, const nodePtr& otherNode)
		{
			if (otherNode->_left) {
				newNode->_left = Construct(*(otherNode->_left->_data), newNode);
				Copy(newNode->_left, otherNode->_left);
			}
			if (otherNode->_right) {
				newNode->_right = Construct(*(otherNode->_right->_data), newNode);
				Copy(newNode->_right, otherNode->_right);
			}
		}

		nodePtr	Insert(nodePtr& newNode, nodePtr& position)
		{
			if (!position || !newNode)
				return newNode;
			else if (_key_compare(getKey(newNode), getKey(position))) {
				position->_left = Insert(newNode, position->_left);
				position->_left->_parent = position;
			}
			else if (_key_compare(getKey(position), getKey(newNode))) {
				position->_right = Insert(newNode, position->_right);
				position->_right->_parent = position;
			}
			return position;
		}

		nodePtr	Remove(nodePtr node, nodePtr position) {

			nodePtr	child, parent, replace;
			bool	color;

			// если не является листом дерева
			if (node->_left && node->_right) {

				replace = node->_right;
				while (replace->_left) // ищем замену в левом поддереве правого ребенка
					replace = replace->_left;

				if (node->_parent == nullptr) // если удаляем корень
					position = replace;
				else { // если не корень
					if (node->_parent->_left == node) // перекидываем указатель у родителя на замену
						node->_parent->_left = replace;
					else
						node->_parent->_right = replace;
				}

				child = replace->_right;
				parent = replace->_parent;
				color = replace->_color;

				if (parent == node) //  если родитель переемника - удаляемый узел
					parent = replace;
				else {
					if (child)
						child->_parent = parent;
					parent->_left = child;
					replace->_right = node->_right;
					node->_right->_parent = replace;
				}
				replace->_parent = node->_parent;
				replace->_color = node->_color;
				replace->_left = node->_left;
				node->_left->_parent = replace;
				if (color == Black)
					fixRemove(position, child, parent);
				Destroy(node);
				return position;
			}
			if (node->_left)
				child = node->_left;
			else
				child = node->_right;

			parent = node->_parent;
			color = node->_color;

			if (child)
				child->_parent = parent;
			if (parent) {
				if (node == parent->_left)
					parent->_left = child;
				else
					parent->_right = child;
			}
			else
				position = child;

			if (color == Black)
				fixRemove(position, child, parent);
			Destroy(node);
			return position;
		}

		nodePtr		Find(const key_type& key, const nodePtr& position) const {
			if (position == nullptr)
				return position;
			return	_key_compare(key, getKey(position)) ? Find(key, position->_left) :
					_key_compare(getKey(position), key) ? Find(key, position->_right):
					position;
		}

		size_type	Size(const nodePtr& position) const {
			return position != nullptr ? Size(position->_right) + Size(position->_left) + 1 : 0 ;
		}

		nodePtr		Min(const nodePtr& position) const {
			return position != nullptr && position->_left ? Min(position->_left) : position;
		}

		nodePtr		Max(const nodePtr& position) const {
			return position != nullptr && position->_right ? Max(position->_right) : position;
		}

		void	PrintNode(nodePtr& node)
		{
			if (!node)
				std::cout << "(null)" << DEF;
			else if (node->_data) {
				node->_color == Red ? std::cout << RED : std::cout << DEF;
				std::cout << "[" << getKey(node) << "]" << DEF;
			}
//			if (node->_left) {
//				node->_left->_color == Red ? std::cout << RED : std::cout << DEF;
//				std::cout << "left: " << getKey(node->_left) << ", ";
//			}
//			if (node->_right) {
//				node->_right->_color == Red ? std::cout << RED : std::cout << DEF;
//				std::cout << "right: " << getKey(node->_right);
//			}
			std::cout << "\n";
		}

	};

	template < class RBT > inline
	bool operator==(const RedBlackTree<RBT> &X, const RedBlackTree<RBT> &Y)
	{
		return (X.size() == Y.size() && ft::equal(X.cbegin(), X.cend(), Y.cbegin()));
	}

	template < class RBT > inline
	bool operator!=(const RedBlackTree<RBT> &X, const RedBlackTree<RBT> &Y)
	{
		return !(X == Y);
	}

	template < class RBT > inline
	bool operator<(const RedBlackTree<RBT> &X, const RedBlackTree<RBT> &Y)
	{
		return ft::lexicographical_compare(X.cbegin(), X.cend(), Y.cbegin(), Y.cend());
	}

	template < class RBT > inline
	bool operator>(const RedBlackTree<RBT> &X, const RedBlackTree<RBT> &Y)
	{
		return Y < X;
	}

	template < class RBT > inline
	bool operator<=(const RedBlackTree<RBT> &X, const RedBlackTree<RBT> &Y)
	{
		return !(Y < X);
	}

	template < class RBT > inline
	bool operator>=(const RedBlackTree<RBT> &X, const RedBlackTree<RBT> &Y)
	{
		return !(X < Y);
	}

	template < class RBT > inline
	void swap(RedBlackTree<RBT> &X, RedBlackTree<RBT> &Y)
	{
		X.swap(Y);
	}
}
