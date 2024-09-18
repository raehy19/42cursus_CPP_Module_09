/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:55:27 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/18 20:55:32 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <ctime>

/**
 * @brief Parses input arguments into a vector of integers.
 *
 * This function takes command-line arguments, converts them into unsigned integers,
 * and stores them in a vector. It throws exceptions if the arguments are invalid.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of argument strings.
 * @return A vector of parsed unsigned integers.
 */
std::vector<uint32_t> parse_arguments(int argc, char** argv) {
	std::vector<uint32_t> numbers;

	for (int i = 1; i < argc; i++) {
		numbers.push_back(str_to_uint(argv[i]));
	}
	return numbers;
}

/**
 * @brief Measures the time taken by the Ford-Johnson algorithm on a container.
 *
 * This function times the execution of the Ford-Johnson sorting algorithm for a given container.
 *
 * @tparam T Container type (e.g., std::vector or std::deque).
 * @param container The container to be sorted.
 * @return The time taken in microseconds.
 */
template <typename T>
double measure_sort_time(T& container) {
	clock_t start_time = clock();
	ford_johnson(container);
	clock_t end_time = clock();
	return static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e6;
}

/**
 * @brief Displays the contents of a container.
 *
 * This function prints the contents of a container (e.g., std::vector or std::deque) to the console.
 *
 * @tparam T Container type.
 * @param container The container whose contents to display.
 */
template <typename T>
void display_container(const T& container) {
	typename T::const_iterator it;
	for (it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

/**
 * @brief Main entry point for the PmergeMe program.
 *
 * The main function parses command-line arguments, runs the Ford-Johnson sorting algorithm
 * on both std::vector and std::deque containers, and prints the sorting time.
 *
 * @param argc Argument count.
 * @param argv Argument values.
 * @return Exit status.
 */
int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <numbers>..." << std::endl;
		return EXIT_FAILURE;
	}

	try {
		std::vector<uint32_t> numbers_vector = parse_arguments(argc, argv);
		std::deque<uint32_t> numbers_deque(numbers_vector.begin(), numbers_vector.end());

		std::cout << "Before: ";
		display_container(numbers_vector);

		double vector_time = measure_sort_time(numbers_vector);
		double deque_time = measure_sort_time(numbers_deque);

		std::cout << "After: ";
		display_container(numbers_vector);

		std::cout << "Time to process with std::vector: " << vector_time << " us" << std::endl;
		std::cout << "Time to process with std::deque: " << deque_time << " us" << std::endl;

	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
