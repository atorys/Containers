//
// Created by Achiote Tory on 3/30/22.
//

#pragma once

#include <memory>

namespace ft {

	enum	Color	{Red, Black};

	template < class Type >
	struct treeNode {
		Type*		_data;
		treeNode*	_parent;
		treeNode*	_left;
		treeNode*	_right;
		bool		_color;

//		treeNode&	operator=(const treeNode& other)
//		{
//			if (this == &other)
//				return *this;
//			_data = Type(other._data);
//			_parent = other._parent;
//			_left = other._left;
//			_right = other._right;
//			_color = other._color;
//			_height = other._height;
//			return *this;
//		}
		bool	operator>(const treeNode& other) const {

		}

		Type&	operator*() { return *_data; }
	};

}
