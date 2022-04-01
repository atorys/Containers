//
// Created by atory on 3/29/22.
//

#pragma once

namespace ft {

	template < class A, class B >
	struct	pair {
		A		first;
		B		second;

		pair(): first(A()), second(B()) {}

		template < class T1, class T2 >
		pair(const pair<T1, T2>& other): first(other._first), second(other._second) {}
		pair(const A& X, const B& Y): first(X), second(Y) {}

		pair&	operator=(const pair& other)
		{
			if (this == &other)
				return *this;
			first = other._first;
			second = other._second;
			return *this;
		}

		void	swap(const pair& other)
		{
			pair<A, B>	tmp(other);

			other._first = this->_first;
			other._second = this->_second;
			this = tmp;
		}
	};

	template < bool Value >
	struct	is_pair_base {
		static const bool	value = Value;
		bool	operator()() const { return value; };
	};

	template < class Type >
	struct is_pair: public ft::is_pair_base<false> {};

	template <>
	struct is_pair<int>: public ft::is_pair_base<false> {};

	template <>
	struct is_pair<char *>: public ft::is_pair_base<false> {};

	template < class T1, class T2 >
	struct is_pair< ft::pair<T1, T2> >: public ft::is_pair_base<true> {};



	template < class T1, class T2 >
	pair<T1, T2>	make_pair(const T1& X, const T2& Y)
	{
		return pair<T1, T2>(X, Y);
	}

	template < class T1, class T2 >
	bool	operator==(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return (X._first == Y._first && X._second == Y._second);
	}

	template < class T1, class T2 >
	bool	operator!=(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return !(X == Y);
	}

	template < class T1, class T2 >
	bool	operator<(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return (X._first < Y._first || (!(Y._first < X._first) && X._second < Y._second));
	}

	template < class T1, class T2 >
	bool	operator>(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return Y < X;
	}

	template < class T1, class T2 >
	bool	operator>=(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return !(X < Y);
	}

	template < class T1, class T2 >
	bool	operator<=(const pair<T1, T2>& X, const pair<T1, T2>& Y)
	{
		return !(Y < X);
	}
}