//
// Created by Achiote Tory on 3/30/22.
//

#pragma once

namespace ft {

	enum	Color	{Red, Black};

	/**
	 * Template structure Tree Node
	 */
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

		Type&	operator*() { return *_data; }
		treeNode(): _data(nullptr),
					_parent(nullptr),
					_left(nullptr),
					_right(nullptr),
					_color(Red) {}
	};

}
