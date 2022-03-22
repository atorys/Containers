//
// Created by atory on 3/22/22.
//

#pragma once

namespace ft {

	template < bool, class Type = void >
	struct	enable_if {};

	template < class Type >
	struct	enable_if <true, Type> {
		typedef Type	type;
	};
}
