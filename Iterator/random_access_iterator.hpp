//
// Created by atory on 3/10/22.
//

#pragma once

#include "iterator.hpp"

namespace ft {

	/****************************************
	 * template class RANDOM_ACCESS_Iterator
	 ****************************************/

	template < class RandIter >
	class	random_access_iterator : public ft::iterator  < typename iterator_traits<RandIter>::iterCategory,
															typename iterator_traits<RandIter>::valueType,
															typename iterator_traits<RandIter>::diffType,
															typename iterator_traits<RandIter>::pointer,
															typename iterator_traits<RandIter>::reference >
	{
		typedef	typename iterator_traits<RandIter>::diffType	thisDiff;
		typedef	typename iterator_traits<RandIter>::pointer 	thisPtr;
		typedef	typename iterator_traits<RandIter>::reference 	thisRef;
		typedef random_access_iterator<RandIter>				thisType;

	protected:

		thisPtr	_current;

	public:

		random_access_iterator(){};
		explicit random_access_iterator(thisPtr x) : _current(x) {};
		random_access_iterator(const random_access_iterator<RandIter>& other) : _current(other.base()) {};

		thisPtr		base() const { return _current; };

		thisRef 	operator*() const { return *_current; };
		thisPtr		operator->() const { return &**this; };
		thisType&	operator++()
		{
			++_current;
			return	*this;
		};
		thisType	operator++(int)
		{
			thisType tmp(this);
			++_current;
			return tmp.base();
		}
		thisType&	operator--()
		{
			--_current;
			return *this;
		}
		thisType	operator--(int)
		{
			thisType tmp(this);
			--_current;
			return *tmp;
		}
	};
}
