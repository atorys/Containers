//
// Created by atory on 3/20/22.
//

#pragma once

namespace ft {

	/**
	 * Проверяет, является ли Type целочисленным типом
	 */
	template < class Type, bool Value >
	struct	is_integral_base
	{
		static const bool	value = Value;
		typedef	Type		type;

		bool	operator()() const { return value; };
	};

	template < class Type >
	struct	is_integral:					public	ft::is_integral_base<Type, false> {};

	template <>
	struct	is_integral<bool>:				public ft::is_integral_base<bool, true> {};

	template <>
	struct	is_integral<char>:				public ft::is_integral_base<char, true> {};

	template <>
	struct	is_integral<signed char>:		public ft::is_integral_base<signed char, true> {};

	template <>
	struct	is_integral<unsigned char>:		public ft::is_integral_base<unsigned char, true> {};

	template <>
	struct	is_integral<wchar_t>:			public ft::is_integral_base<wchar_t, true>	{};

	template <>
	struct	is_integral<short>:				public ft::is_integral_base<short, true> {};

	template <>
	struct	is_integral<unsigned short>:	public ft::is_integral_base<unsigned short, true> {};

	template <>
	struct	is_integral<int>:				public ft::is_integral_base<int, true> {};

	template <>
	struct	is_integral<unsigned int>:		public ft::is_integral_base<unsigned int, true> {};

	template <>
	struct	is_integral<long>:				public ft::is_integral_base<long, true> {};

	template <>
	struct	is_integral<unsigned long>:		public ft::is_integral_base<unsigned long, true> {};

	template <>
	struct	is_integral<long long>:			public ft::is_integral_base<long long, true> {};
}
