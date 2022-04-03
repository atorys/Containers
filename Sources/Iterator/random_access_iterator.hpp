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
	class	random_access_iterator : public ft::iterator  < typename ft::iterator_traits<RandIter>::iterator_category,
															typename ft::iterator_traits<RandIter>::value_type,
															typename ft::iterator_traits<RandIter>::difference_type,
															typename ft::iterator_traits<RandIter>::pointer,
															typename ft::iterator_traits<RandIter>::reference >
	{

		typedef	typename ft::iterator_traits<RandIter>::difference_type	thisDiff;
		typedef	typename ft::iterator_traits<RandIter>::pointer 		thisPtr;
		typedef	typename ft::iterator_traits<RandIter>::reference 		thisRef;
		typedef random_access_iterator<RandIter>						Self;

	protected:

		thisPtr		_current;

	public:
		random_access_iterator(){};
		explicit random_access_iterator(thisPtr x) : _current(x) {}
		random_access_iterator(const Self& other) : _current(other.base()) {}
		virtual ~random_access_iterator(){}

		thisPtr		base() const { return _current; }

		Self& 	operator=(const Self& other)
					{
						if (this != &other)
							_current = other.base();
						return *this;
					};
		thisRef 	operator*() const { return *_current; }
		thisPtr		operator->() const { return &**this; }
		Self&	operator++()
					{
						++_current;
						return	*this;
					}
		Self	operator++(int)
					{
						Self tmp(*this);
						++_current;
						return tmp;
					}
		Self&	operator--()
					{
						--_current;
						return *this;
					}
		Self	operator--(int)
					{
						Self tmp(*this);
						--_current;
						return tmp;
					}
		Self 	operator+(thisDiff N) const { return Self (_current + N); }
		Self 	operator-(thisDiff N) const { return Self (_current - N); }
		Self&	operator+=(thisDiff N)
					{
						_current += N;
						return *this;
					}
		Self&	operator-=(thisDiff N)
					{
						_current -= N;
						return *this;
					}
		bool 		operator==(const Self& other) const { return (_current == other.base()); }
		bool 		operator==(int other) const { return (_current == (thisPtr)other); }
		bool 		operator!=(const Self& other) const { return !(*this == other); }
		bool 		operator>(const Self& other) const { return (other < *this); }
		bool 		operator<(const Self& other) const { return (_current < other.base()); } // todo : 119 почему сравниваются ссылки
		bool 		operator>=(const Self& other) const { return !(*this < other); }
		bool 		operator<=(const Self& other) const { return !(other < *this); }
		thisRef 	operator[](thisDiff N) { return *(*this + N); };
		thisDiff 	operator-(const Self& other) { return (_current - other.base());}
	};

	template < class RandIter > inline
	random_access_iterator<RandIter>	operator+(typename iterator_traits<RandIter>::difference_type N,
													const random_access_iterator<RandIter>& x)
	{
		return (x + N);
	}
}
