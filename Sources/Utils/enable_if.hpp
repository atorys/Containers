//
// Created by atory on 3/22/22.
//

#pragma once

namespace ft {

	/**
	 * SFINAE (сбой подстановки не является ошибкой)
	 * Экземпляр enable_if <Condition, Type>::type
	 * существует, если только значение Condition = TRUE
	 *
	 * Используется для удаления кандидатов из разрешения перегрузки,
	 * одно определение может быть отброшено в пользу другого
	 */
	template < bool B, class Type = void >
	struct	enable_if {};

	/**
	 * Частичная специальзация, только если B == true
	 */
	template < class Type >
	struct	enable_if <true, Type> {
		typedef Type	type;
	};
}
