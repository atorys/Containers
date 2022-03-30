//
// Created by Achiote Tory on 3/30/22.
//

#pragma once
#include "iterator.hpp"

namespace ft {

	/**********************************
 	* 	template class TREE_Iterator  *
 	**********************************/

	template < class Type, class BiDirIter >
	class	tree_iterator : public ft::iterator <	typename iterator_traits<BiDirIter>::iterCategory,
													typename iterator_traits<BiDirIter>::valueType,
													typename iterator_traits<BiDirIter>::diffType,
													typename iterator_traits<BiDirIter>::pointer,
													typename iterator_traits<BiDirIter>::reference >
	{
		typedef	typename ft::iterator_traits<BiDirIter>::diffType	thisDiff;
		typedef	typename ft::iterator_traits<BiDirIter>::pointer 	thisPtr;
		typedef	typename ft::iterator_traits<BiDirIter>::reference	thisRef;
		typedef tree_iterator<Type, BiDirIter>						thisType;
	protected:

		thisPtr		_current;

	public:

		tree_iterator(){}
		explicit	tree_iterator(thisPtr x) : _current(x) {}
		tree_iterator(const thisType& other) : _current(other.base()) {}
		virtual ~tree_iterator() {}

		thisPtr		base() const			{ return _current; };
		Type 		operator*() const		{ return *(_current)->_data; }
		Type*		operator->() const		{ return _current->_data; } // (_current->_data)?
		thisType&	operator++() // идем снизу вверх по дереву, от меньших элементов к большим
		{
			if (_current->_right) { // если есть узел справа, спускаемся в его левое поддерево
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
		thisType	operator++(int)
		{
			thisType tmp = *this;
			++(*this);
			return (tmp);
		}
		thisType&	operator--() // идем сверху вниз по дереву, от больших элементов к меньшим
		{
			if (_current->_left) { // если есть узел слева, спускаемся в его правое поддерево
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
		thisType	operator--(int)
		{
			thisType tmp = *this;
			--(*this);
			return tmp;
		}
		bool 		operator==(const thisType& other) const { return (_current == other.base()); }
		bool 		operator!=(const thisType& other) const { return !(*this == other); }
	};

}
