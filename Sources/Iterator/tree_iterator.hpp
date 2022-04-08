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
	public:
//		typedef	typename ft::iterator_traits<BiDirIter>::pointer 			thisPtr;
		typedef	typename ft::RedBlackTree<TreeTraits>::nodePtr 				thisPtr;
		typedef typename ft::RedBlackTree<TreeTraits>						tree;
		typedef typename TreeTraits::pointer								pointer;
		typedef typename TreeTraits::reference								reference;
		typedef tree_iterator< TreeTraits, BiDirIter>						Self;

	protected:
		thisPtr		_current;

	public:

		tree_iterator() :						_current(nullptr)		{}
		tree_iterator(const Self& other) :		_current(other.base())	{}
		explicit	tree_iterator(thisPtr x) :	_current(x)				{}

		template < class Other, class OtherBiDir >
		tree_iterator(const tree_iterator < Other, OtherBiDir > & other) {
			_current = reinterpret_cast<thisPtr> (other.base());
		}
		virtual ~tree_iterator() {}

		thisPtr		base() const			{ return _current; };
		reference	operator*() const		{ return (*(_current->_data)); }
		pointer		operator->() const		{ return (&**this);}

		Self& 		operator=(const Self& other)
		{
			if (this != &other)
				_current = other.base();
			return *this;
		}

		template < class Other, class OtherBiDir >
		Self& 	operator=(const tree_iterator<Other, OtherBiDir>& other)
		{
			_current = reinterpret_cast<thisPtr> (other.base());
			return *this;
		};

		Self&	operator++() // идем снизу вверх по дереву, от меньших элементов к большим
		{
			if (!_current || (tree::isEnd(_current) && _current->_parent)) {
				if (_current && _current->_parent && !tree::isMax(_current->_parent))
					_current = _current->_parent;
				else
					;
			}
			else if (tree::isMax(_current))
				_current = _current->_right;
			else if (_current->_right)// если есть узел справа, спускаемся в его левое поддерево
//			else if (!tree::isEnd(_current->_right))// если есть узел справа, спускаемся в его левое поддерево
				_current = tree::Min(_current->_right);
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
			if (!_current)
				;
			else if (tree::isMin(_current) && _current->_parent) {
				thisPtr	parent = _current->_parent;
				while (parent && _current == parent->_left) {
					_current = parent;
					parent = parent->_parent;
				}
				_current = tree::Max(_current)->_right;
			}
			else if (_current->_parent && tree::isMax(_current->_parent))
				_current = _current->_parent;
//			else if (!tree::isEnd(_current->_left) && _current->_left) // если есть узел слева, спускаемся в его правое поддерево
			else if (_current->_left) // если есть узел слева, спускаемся в его правое поддерево
				_current = tree::Max(_current->_left);
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
		bool 		operator==(const Self& other) const { return (_current == other.base()); }
		template	<class TreeOther>
		bool 		operator==(const tree_iterator<TreeOther, BiDirIter>& other) const { return (_current == other.base()); }
		bool 		operator!=(const Self& other) const { return !(*this == other); }
	};

	/**********************************
 	* 	template class TREE_Iterator  *
 	**********************************/
	template < class TreeTraits, class BiDirIter >
	class	const_tree_iterator : public ft::iterator <	typename iterator_traits<BiDirIter>::iterator_category,
														typename iterator_traits<BiDirIter>::value_type,
														typename iterator_traits<BiDirIter>::difference_type,
														typename iterator_traits<BiDirIter>::pointer,
														typename iterator_traits<BiDirIter>::reference >
	{
	public:
//		typedef	typename ft::iterator_traits<BiDirIter>::pointer 			thisPtr;
		typedef	typename ft::RedBlackTree<TreeTraits>::nodePtr 				thisPtr;
		typedef typename ft::RedBlackTree<TreeTraits>						tree;
		typedef typename TreeTraits::pointer								pointer;
		typedef typename TreeTraits::reference								reference;
		typedef const_tree_iterator< TreeTraits, BiDirIter>					Self;

	protected:
		thisPtr		_current;

	public:

		const_tree_iterator() :							_current(nullptr)		{}
		const_tree_iterator(const Self& other) :		_current(other.base())	{}
		explicit	const_tree_iterator(thisPtr x) :	_current(x)				{}

		template < class Other >
		const_tree_iterator(const Other& other) {
			_current = reinterpret_cast<thisPtr> (other.base());
		}
		virtual ~const_tree_iterator() {}

		thisPtr		base() const			{ return _current; };
		reference	operator*() const		{ return (*(_current->_data)); }
		pointer		operator->() const		{ return (&**this);}

		Self& 		operator=(const Self& other)
		{
			if (this != &other)
				_current = other.base();
			return *this;
		}

		template < class Other>
		Self& 		operator=(const Other& other)
		{
			_current = reinterpret_cast<thisPtr> (other.base());
			return *this;
		}

		Self&	operator++() // идем снизу вверх по дереву, от меньших элементов к большим
		{
			if (!_current || tree::isEnd(_current))
				;
			else if (tree::isMax(_current))
				_current = _current->_right;
			else if (!tree::isEnd(_current->_right))// если есть узел справа, спускаемся в его левое поддерево
				_current = tree::Min(_current->_right);
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
			if (!_current)
				;
			else if (tree::isMin(_current) && _current->_parent) {
				thisPtr	parent = _current->_parent;
				while (parent && _current == parent->_left) {
					_current = parent;
					parent = parent->_parent;
				}
				_current = tree::Max(_current)->_right;
			}
			else if (_current->_parent && tree::isMax(_current->_parent))
				_current = _current->_parent;
			else if (!tree::isEnd(_current->_left) && _current->_left) // если есть узел слева, спускаемся в его правое поддерево
				_current = tree::Max(_current->_left);
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
		bool 		operator==(const Self& other) const { return (_current == other.base()); }
		template	<class TreeOther>
		bool 		operator==(const const_tree_iterator<TreeOther, BiDirIter>& other) const { return (_current == other.base()); }
		bool 		operator!=(const Self& other) const { return !(*this == other); }
	};

}
