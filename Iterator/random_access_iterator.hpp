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
	class	random_access_iterator : public ft::iterator  < typename ft::iterator_traits<RandIter>::iterCategory,
															typename ft::iterator_traits<RandIter>::valueType,
															typename ft::iterator_traits<RandIter>::diffType,
															typename ft::iterator_traits<RandIter>::pointer,
															typename ft::iterator_traits<RandIter>::reference >
	{
		typedef	typename ft::iterator_traits<RandIter>::diffType	thisDiff;
		typedef	typename ft::iterator_traits<RandIter>::pointer 	thisPtr;
		typedef	typename ft::iterator_traits<RandIter>::reference 	thisRef;
		typedef random_access_iterator<RandIter>					thisType;

	protected:

		thisPtr		_current;

	public:

		random_access_iterator(){};
		explicit random_access_iterator(thisPtr x) : _current(x) {};
		random_access_iterator(const random_access_iterator<RandIter>& other) : _current(other.base()) {};
		virtual ~random_access_iterator(){};

		thisPtr		base() const { return _current; };

		thisType& 	operator=(const thisType& other)
					{
						if (this != &other)
							_current = other.base();
						return *this;
					};
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
						return tmp;
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
						return tmp;
					}
		thisType 	operator+(thisDiff N) const { return thisType (_current + N); };
		thisType 	operator-(thisDiff N) const { return thisType (_current - N); };
		thisType&	operator+=(thisDiff N)
					{
						_current += N;
						return *this;
					}
		thisType&	operator-=(thisDiff N)
					{
						_current -= N;
						return *this;
					}
		bool 		operator==(const thisType& other) const { return (_current == other.base()); };
		bool 		operator==(int other) const { return (_current == (thisPtr)other); };
		bool 		operator!=(const thisType& other) const { return (*this != other); };
		bool 		operator>(const thisType& other) const { return (*this > other); };
		bool 		operator<(const thisType& other) const { return (*this < other); }; // todo : 119 почему сравниваются ссылки
		bool 		operator>=(const thisType& other) const { return (*this >= other); };
		bool 		operator<=(const thisType& other) const { return (*this <= other); };
		thisRef 	operator[](thisDiff N) { return *(*this + N); };
		thisDiff 	operator-(const thisType& other) { return (_current - other.base());};
	};

	template < class RandIter > inline
	random_access_iterator<RandIter>	operator+(typename iterator_traits<RandIter>::diffType N,
													const random_access_iterator<RandIter>& x)
	{
		return (x + N);
	}
}
