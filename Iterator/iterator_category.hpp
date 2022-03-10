//
// Created by atory on 3/10/22.
//

#ifndef CONTAINERS_ITERATOR_CATEGORY_HPP
#define CONTAINERS_ITERATOR_CATEGORY_HPP

#include "iterator.hpp"

namespace ft {

	/*****************************************************
	 * template function ITER_CAT
	 * returns an object of the iterator category type
	 *****************************************************/

	template < class Cat, class Type, class Diff, class Ptr, class Ref > inline
	Cat	Iter_cat(const iterator <Cat, Type, Diff, Ptr, Ref>&)
	{
		return (Cat()); // new object
	}

	template < class Type >
	random_access_iterator_tag	Iter_cat(const Type*)
	{
		return (random_access_iterator_tag());
	}

	/*
	 * integer func
	 */
		inline Int_iterator_tag	Iter_cat(bool)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(char)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(signed char)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(unsigned char)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(wchar_t)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(short)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(unsigned short)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(int)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(unsigned int)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(long)
		{
			return (Int_iterator_tag());
		}

		inline Int_iterator_tag	Iter_cat(unsigned long)
		{
			return (Int_iterator_tag());
		}
}

#endif //CONTAINERS_ITERATOR_CATEGORY_HPP
