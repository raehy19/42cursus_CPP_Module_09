/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:13:12 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/11 16:13:15 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>

/**
 * @brief Default constructor for the RPN class.
 */
RPN::RPN() {
	// No specific initialization needed for this example.
}

/**
 * @brief Destructor for the RPN class.
 */
RPN::~RPN() {
	// No dynamic memory to clean up in this example.
}

/**
 * @brief Copy constructor for the RPN class.
 *
 * Performs a deep copy of the original RPN object.
 * @param other The RPN object to copy from.
 */
RPN::RPN(const RPN &other) {
	// No deep copying needed for this example, as we don't use dynamically allocated memory.
	*this = other;
}

/**
 * @brief Copy assignment operator for the RPN class.
 *
 * Performs deep copy assignment.
 * @param other The RPN object to assign from.
 * @return Reference to the current object.
 */
RPN &RPN::operator=(const RPN &other) {
	if (this != &other) {
		// Nothing specific to copy in this case
	}
	return *this;
}

/**
 * @brief Evaluate a Reverse Polish Notation expression.
 *
 * @param expression The RPN expression as a string.
 * @return int The result of evaluating the RPN expression.
 * @throws std::invalid_argument if the expression is invalid.
 */
int RPN::evaluate(const std::string &expression) {
	// Check for an empty expression
	if (expression.empty()) {
		throw std::invalid_argument("Error: Empty expression.");
	}

	std::stack<int> stack;
	std::stringstream ss(expression);
	std::string token;

	// Process each token in the expression
	while (ss >> token) {
		if (token.size() > 1) {
			throw std::invalid_argument(
				"Error: Invalid token size. Numbers must be 0-9 and operators must be single characters.");
		} else if (isdigit(static_cast<unsigned char> (token[0]))) {
			// If the token is a number, push it onto the stack
			stack.push(token[0] - '0');
		} else if (token == "+" || token == "-" || token == "*" || token == "/") {
			// Ensure there are at least two operands on the stack
			if (stack.size() < 2) {
				throw std::invalid_argument("Error: Not enough operands for the operator.");
			}

			// Pop the top two operands from the stack
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();
			int result = 0;

			// Perform the operation
			if (token == "+") result = a + b;
			else if (token == "-") result = a - b;
			else if (token == "*") result = a * b;
			else if (token == "/") {
				if (b == 0) {
					throw std::invalid_argument("Error: Division by zero.");
				}
				result = a / b;
			}

			// Push the result onto the stack
			stack.push(result);
		} else {
			throw std::invalid_argument("Error: Invalid token in expression.");
		}
	}

	// Ensure there's exactly one result left on the stack
	if (stack.size() != 1) {
		throw std::invalid_argument("Error: Too many operands or not enough operators in the expression.");
	}

	return stack.top();
}
