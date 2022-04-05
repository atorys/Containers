//
// Created by Achiote Tory on 3/30/22.
//

#pragma once

#include <memory>
#include "../Tree/tree.hpp"
#include "iterator.hpp"

namespace ft {


	/**********************************
 	* 	template class TREE_Iterator  *
 	**********************************/
	template < class TreeTraits, class BiDirIter >
	class	tree_iterator : public ft::iterator <	typename iterator_traits<BiDirIter>::iterator_category,
													typename iterator_traits<BiDirIter>::value_type,
													typename iterator_traits<BiDirIter>::difference_type,
													typename iterator_traits<BiDirIter>::pointer,
													typename iterator_traits<BiDirIter>::reference >
	{
		typedef	typename ft::iterator_traits<BiDirIter>::difference_type	thisDiff;
		typedef	typename ft::iterator_traits<BiDirIter>::pointer 			thisPtr;
		typedef	typename ft::iterator_traits<BiDirIter>::reference			thisRef;

		typedef typename TreeTraits::pointer								dataPtr;
		typedef typename TreeTraits::reference								dataRef;
		typedef tree_iterator< TreeTraits, BiDirIter>						Self;

	protected:
		thisPtr		_current;

	public:

		tree_iterator(): _current(nullptr) {}
		explicit	tree_iterator(thisPtr x) : _current(x) {}
		tree_iterator(const Self& other) : _current(other.base()) {}
		template < class Other >
		tree_iterator(const tree_iterator < Other, BiDirIter > & other): _current(reinterpret_cast<thisPtr> (other.base())) {}
		virtual ~tree_iterator() {}

		thisPtr		base() const			{ return _current; };
		dataRef		operator*() const		{ return *(_current)->_data; }
//		dataPtr		operator->() const		{ return _current->_data; } // (_current->_data)?
		dataPtr		operator->() const		{ return &**this; } // (_current->_data)?
		Self& 		operator=(const Self& other)
		{
			if (this != &other)
				_current = other.base();
			return *this;
		}

		template < class Other >
		Self& 	operator=(const tree_iterator<Other, BiDirIter>& other)
		{
			_current = reinterpret_cast<thisPtr> (other.base());
			return *this;
		};
		Self&	operator++() // идем снизу вверх по дереву, от меньших элементов к большим
		{
			if (_current == ft::RedBlackTreeTraits<TreeTraits>::max())
				_current = nullptr;
			else if (_current->_right) { // если есть узел справа, спускаемся в его левое поддерево
				_current = _current->_right;
				while (_current->_left)
					_current = _current->_left;
			}
			else { //если узла справа нет, поднимаемся до родителя и идем вверх, пока не окажемся в левом поддереве
				thisPtr	parent = _current->_parent;
				while (parent && _current == parent->_right) {
					_current = parent;
					parent = parent->_parent;
				}
				_current = parent;
			}
			return	*this;
		}
		Self	operator++(int)
		{
			Self tmp = *this;
			++(*this);
			return (tmp);
		}
		Self&	operator--() // идем сверху вниз по дереву, от больших элементов к меньшим
		{
			if (_current == nullptr)
				_current = ft::RedBlackTreeTraits<TreeTraits>::max();
			else if (_current->_left) { // если есть узел слева, спускаемся в его правое поддерево
				_current = _current->_left;
				while (_current->_right)
					_current = _current->_right;
			}
			else { //если узла слева нет, поднимаемся до родителя и идем вверх, пока не окажемся в правом поддереве
				thisPtr	parent = _current->_parent;
				while (parent && _current == parent->_left) {
					_current = parent;
					parent = parent->_parent;
				}
				_current = parent;
			}
			return	*this;
		}
		Self	operator--(int)
		{
			Self tmp = *this;
			--(*this);
			return tmp;
		}
		bool 		operator==(const tree_iterator<TreeTraits, BiDirIter>& other) const { return (_current == other.base()); }
//		template <class TreeOther>
//		bool 		operator==(const tree_iterator<TreeOther, BiDirIter>& other) const { return (_current == other.base()); }
		bool 		operator!=(const Self& other) const { return !(*this == other); }
	};

	template < class Type, class Tree, class BiDirIter >
	class	const_tree_iterator : public ft::iterator <	typename iterator_traits<BiDirIter>::iterator_category,
														typename iterator_traits<BiDirIter>::value_type,
														typename iterator_traits<BiDirIter>::difference_type,
														typename iterator_traits<BiDirIter>::pointer,
														typename iterator_traits<BiDirIter>::reference >
	{
		typedef	typename ft::iterator_traits<BiDirIter>::difference_type	thisDiff;
		typedef	typename ft::iterator_traits<BiDirIter>::const_pointer 		thisPtr;
		typedef	typename ft::iterator_traits<BiDirIter>::reference			thisRef;
		typedef const_tree_iterator<Type, Tree, BiDirIter>						Self;
	protected:

		thisPtr		_current;
		Tree*		_tree;

	public:

		const_tree_iterator(){}
		explicit	const_tree_iterator(thisPtr x, Tree* tree) : _current(x), _tree(tree) {}
		const_tree_iterator(const Self& other) : _current(other.base()), _tree(other._tree) {}
		virtual ~const_tree_iterator() {}

		thisPtr		base() const			{ return _current; };
		Type 		operator*() const		{ return *(_current)->_data; }
		Type*		operator->() const		{ return _current->_data; } // (_current->_data)?
		Self& 	operator=(const Self& other)
		{
			if (this != &other) {
				_current = other.base();
				_tree = other._tree;
			}
			return *this;
		};
		template < class TypeOther, class TreeOther >
		const_tree_iterator& 	operator=(const const_tree_iterator<TypeOther, TreeOther, BiDirIter>& other)
		{
//			tree_iterator<TypeOther, TreeOther, BiDirIter> tmp;

//			tmp._current = (Type *)
			if (this != &other) {
				_current = other.base();
				_tree = other._tree;
			}
			return *this;
		};
		Self&	operator++() // идем снизу вверх по дереву, от меньших элементов к большим
		{
			if (_current == _tree->max())
				_current = nullptr;
			else if (_current->_right) { // если есть узел справа, спускаемся в его левое поддерево
				_current = _current->_right;
				while (_current->_left)
					_current = _current->_left;
			}
			else { //если узла справа нет, поднимаемся до родителя и идем вверх, пока не окажемся в левом поддереве
				thisPtr	parent = _current->_parent;
				while (parent && _current == parent->_right) {
					_current = parent;
					parent = parent->_parent;
				}
				_current = parent;
			}
			return	*this;
		}
		Self	operator++(int)
		{
			Self tmp = *this;
			++(*this);
			return (tmp);
		}
		Self&	operator--() // идем сверху вниз по дереву, от больших элементов к меньшим
		{
			if (_current == nullptr)
				_current = _tree->max();
			else if (_current->_left) { // если есть узел слева, спускаемся в его правое поддерево
				_current = _current->_left;
				while (_current->_right)
					_current = _current->_right;
			}
			else { //если узла слева нет, поднимаемся до родителя и идем вверх, пока не окажемся в правом поддереве
				thisPtr	parent = _current->_parent;
				while (parent && _current == parent->_left) {
					_current = parent;
					parent = parent->_parent;
				}
				_current = parent;
			}
			return	*this;
		}
		Self	operator--(int)
		{
			Self tmp = *this;
			--(*this);
			return tmp;
		}
		bool 		operator==(const const_tree_iterator<Type, Tree, BiDirIter>& other) const { return (_current == other.base()); }
		template <class TreeOther>
		bool 		operator==(const const_tree_iterator<Type, TreeOther, BiDirIter>& other) const { return (_current == other.base()); }
		bool 		operator!=(const Self& other) const { return !(*this == other); }
	};

}
