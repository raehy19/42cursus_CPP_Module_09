/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:13:08 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/11 16:13:09 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <string>

/**
 * @class RPN
 * @brief Class to evaluate Reverse Polish Notation expressions using a stack.
 */
class RPN {
	public:
		/**
		 * @brief Default constructor for the RPN class.
		 */
		RPN();

		/**
		 * @brief Destructor for the RPN class.
		 */
		~RPN();

		/**
		 * @brief Copy constructor for the RPN class.
		 * @param other The RPN object to copy from.
		 */
		RPN(const RPN& other);

		/**
		 * @brief Copy assignment operator for the RPN class.
		 * @param other The RPN object to assign from.
		 * @return Reference to the current object.
		 */
		RPN& operator=(const RPN& other);

		/**
		 * @brief Evaluate a Reverse Polish Notation expression.
		 *
		 * @param expression The RPN expression as a string.
		 * @return int The result of evaluating the RPN expression.
		 * @throws std::invalid_argument if the expression is invalid.
		 */
		int evaluate(const std::string& expression);
};

#endif
