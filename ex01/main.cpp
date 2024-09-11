/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:13:01 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/11 16:13:02 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

/**
 * @brief Main function to process input and evaluate the RPN expression.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return int Exit status of the program.
 */
int main(int argc, char *argv[]) {

	// Check for the correct number of command-line arguments
	if (argc != 2) {
		std::cerr << "Usage: ./RPN \"<expression>\"" << std::endl;
		return 1;
	}

	try {
		// Create an RPN object
		RPN rpn;

		// Get the expression from the command-line arguments
		std::string expression = argv[1];

		// Evaluate the expression
		int result = rpn.evaluate(expression);

		// Output the result
		std::cout << result << std::endl;

	} catch (const std::invalid_argument &e) {
		// Output the error message
		std::cerr << e.what() << std::endl;

		return 1;
	}

	return 0;
}
