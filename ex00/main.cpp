/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:37:09 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/10 14:37:09 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "BitcoinExchange.hpp"
#include <iostream>

/**
 * @brief Main function that reads the input file and runs the BitcoinExchange class.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return 0 if the program runs successfully, 1 otherwise.
 */
int main(int argc, char* argv[]) {
	if (argc < 2 || argc > 3) {
		std::cerr << "Usage: " << argv[0] << " <bitcoin_values_file> [exchange_rate_file]" << std::endl;
		return 1;
	}

	try {
		BitcoinExchange exchange(argc == 3 ? argv[2] : "data.csv");
		exchange.run(argv[1]);
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}
