//
// Created by Achiote Tory on 3/30/22.
//

#pragma once
#include "iterator.hpp"

namespace ft {

	/**********************************
 	* 	template class TREE_Iterator  *
 	**********************************/

//	template < class Type, class BiDirIter >
//	class	tree_iterator : public ft::iterator <	typename iterator_traits<BiDirIter>::iterator_category,
//													typename iterator_traits<BiDirIter>::value_type,
//													typename iterator_traits<BiDirIter>::difference_type,
//													typename iterator_traits<BiDirIter>::pointer,
//													typename iterator_traits<BiDirIter>::reference >
//	{
//		typedef	typename ft::iterator_traits<BiDirIter>::difference_type	thisDiff;
//		typedef	typename ft::iterator_traits<BiDirIter>::pointer 			thisPtr;
//		typedef	typename ft::iterator_traits<BiDirIter>::reference			thisRef;
//		typedef tree_iterator<Type, BiDirIter>								Self;
//	protected:
//
//		thisPtr		_current;
//
//	public:
//
//		tree_iterator(){}
//		explicit	tree_iterator(thisPtr x) : _current(x) {}
//		tree_iterator(const Self& other) : _current(other.base()) {}
//		virtual ~tree_iterator() {}
//
//		thisPtr		base() const			{ return _current; };
//		Type 		operator*() const		{ return *(_current)->_data; }
//		Type*		operator->() const		{ return _current->_data; } // (_current->_data)?
//		tree_iterator& 	operator=(const Self& other)
//		{
//			if (this != &other) {
//				_current = other.base();
//			}
//			return *this;
//		};
//		Self&	operator++() // идем снизу вверх по дереву, от меньших элементов к большим
//		{
//			if (_current == nullptr)
//				return nullptr;
//			else if (_current->_right) { // если есть узел справа, спускаемся в его левое поддерево
//				_current = _current->_right;
//				while (_current->_left)
//					_current = _current->_left;
//			}
//			else { //если узла справа нет, поднимаемся до родителя и идем вверх, пока не окажемся в левом поддереве
//				thisPtr	parent = _current->_parent;
//				while (parent && _current == parent->_right) {
//					_current = parent;
//					parent = parent->_parent;
//				}
//				_current = parent;
//			}
//			return	*this;
//		}
//		Self	operator++(int)
//		{
//			Self tmp = *this;
//			++(*this);
//			return (tmp);
//		}
//		Self&	operator--() // идем сверху вниз по дереву, от больших элементов к меньшим
//		{
//			if (_current == nullptr)
//				return nullptr;
//			else if (_current->_left) { // если есть узел слева, спускаемся в его правое поддерево
//				_current = _current->_left;
//				while (_current->_right)
//					_current = _current->_right;
//			}
//			else { //если узла слева нет, поднимаемся до родителя и идем вверх, пока не окажемся в правом поддереве
//				thisPtr	parent = _current->_parent;
//				while (parent && _current == parent->_left) {
//					_current = parent;
//					parent = parent->_parent;
//				}
//				_current = parent;
//			}
//			return	*this;
//		}
//		Self	operator--(int)
//		{
//			Self tmp = *this;
//			--(*this);
//			return tmp;
//		}
//		bool 		operator==(const Self& other) const { return (_current == other.base()); }
//		bool 		operator!=(const Self& other) const { return !(*this == other); }
//	};
//
	template < class Type, class Tree, class BiDirIter >
	class	tree_iterator : public ft::iterator <	typename iterator_traits<BiDirIter>::iterator_category,
													typename iterator_traits<BiDirIter>::value_type,
													typename iterator_traits<BiDirIter>::difference_type,
													typename iterator_traits<BiDirIter>::pointer,
													typename iterator_traits<BiDirIter>::reference >
	{
		typedef	typename ft::iterator_traits<BiDirIter>::difference_type	thisDiff;
		typedef	typename ft::iterator_traits<BiDirIter>::pointer 			thisPtr;
		typedef	typename ft::iterator_traits<BiDirIter>::reference			thisRef;
		typedef tree_iterator<Type, Tree, BiDirIter>						Self;
	protected:

		thisPtr		_current;
		Tree*		_tree;

	public:

		tree_iterator(){}
		explicit	tree_iterator(thisPtr x, Tree* tree) : _current(x), _tree(tree) {}
		tree_iterator(const Self& other) : _current(other.base()), _tree(other._tree) {}
		virtual ~tree_iterator() {}

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
		Self& 	operator=(const tree_iterator<TypeOther, TreeOther, BiDirIter>& other)
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
		bool 		operator==(const tree_iterator<Type, Tree, BiDirIter>& other) const { return (_current == other.base()); }
		template <class TreeOther>
		bool 		operator==(const tree_iterator<Type, TreeOther, BiDirIter>& other) const { return (_current == other.base()); }
		bool 		operator!=(const Self& other) const { return !(*this == other); }
	};

}
