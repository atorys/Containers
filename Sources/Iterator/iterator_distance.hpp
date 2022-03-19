//
// Created by atory on 3/10/22.
//

#pragma once
#include "iterator.hpp"
#include "iterator_category.hpp"

namespace ft {

	/*************************************************
	 * template func DISTANCE
	 * adds to N the distance between first and last
	 *************************************************/

	template < class InIter > inline
	typename ft::iterator_traits <InIter>::diffType	distance(InIter first, InIter last)
	{
		typename ft::iterator_traits<InIter>::diffType N = 0;
		distanceIterTag(first, last, N, ft::Iter_cat(first));
		return (N);
	}

	template < class InIter, class Diff > inline
	void	distance(InIter first, InIter last, Diff& N)
	{
		distanceIterTag(first, last, N, ft::Iter_cat(first));
	}

	/*
	 * template func DISTANCE dependent on iterator category
	 */
	template < class InIter, class Diff > inline
	void	distanceIterTag(InIter first, InIter last, Diff& N, input_iterator_tag)
	{
		for (; first != last; ++first)
			++N;
	}

	template < class InIter, class Diff > inline
	void	distanceIterTag(InIter first, InIter last, Diff& N, forward_iterator_tag)
	{
		for (; first != last; ++first)
			++N;
	}

	template < class InIter, class Diff > inline
	void	distanceIterTag(InIter first, InIter last, Diff& N, bidirectional_iterator_tag)
	{
		for (; first != last; ++first)
			++N;
	}

	template < class InIter, class Diff > inline
	void	distanceIterTag(InIter first, InIter last, Diff& N, random_access_iterator_tag)
	{
		N += last - first;
	}
}
