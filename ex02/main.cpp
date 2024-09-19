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
std::vector <uint32_t> parse_arguments(int argc, char **argv) {
	std::vector <uint32_t> numbers;

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
template<typename T>
double measure_sort_time(T &container) {
	clock_t start_time = clock();

	ford_johnson(container);

	clock_t end_time = clock();

	return static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC * 1e6;
}

/**
 * @brief Measures the time taken by std::sort on a container.
 *
 * This function times the execution of std::sort for a given container.
 *
 * @tparam T Container type (e.g., std::vector or std::deque).
 * @param container The container to be sorted.
 * @return The time taken in microseconds.
 */
template<typename T>
double measure_std_sort_time(T &container) {
	clock_t start_time = clock();

	std::sort(container.begin(), container.end());

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
template<typename T>
void display_container(const T &container) {
	typename T::const_iterator it;
	for (it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

/**
 * @brief Compares two containers for equality.
 *
 * This function compares two containers element-wise to determine if they are equal.
 *
 * @tparam T Container type.
 * @param c1 First container.
 * @param c2 Second container.
 * @return True if containers are equal, false otherwise.
 */
template<typename T>
bool compare_containers(const T &c1, const T &c2) {
	if (c1.size() != c2.size()) {
		return false;
	}
	typename T::const_iterator it1 = c1.begin();
	typename T::const_iterator it2 = c2.begin();
	while (it1 != c1.end()) {
		if (*it1 != *it2) {
			return false;
		}
		++it1;
		++it2;
	}
	return true;
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
int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <numbers>..." << std::endl;
		return EXIT_FAILURE;
	}

	try {
		std::vector <uint32_t> numbers_vector = parse_arguments(argc, argv);
		std::deque <uint32_t> numbers_deque(numbers_vector.begin(), numbers_vector.end());
		std::vector <uint32_t> numbers_vector_copy(numbers_vector.begin(), numbers_vector.end());
		std::deque <uint32_t> numbers_deque_copy(numbers_deque.begin(), numbers_deque.end());

		std::cout << "Before: ";
		display_container(numbers_vector);

		double vector_time = measure_sort_time(numbers_vector);
		double deque_time = measure_sort_time(numbers_deque);

		std::cout << "After: ";
		display_container(numbers_vector);

		std::cout << "Time to process a range of " << numbers_vector.size() << " elements with std::vector: " << vector_time << " us" << std::endl;
		std::cout << "Time to process a range of " << numbers_deque.size() << " elements with std::deque: " << deque_time << " us" << std::endl;

//		// Compare with std::sort
//		double std_sort_vector_time = measure_std_sort_time(numbers_vector_copy);
//		double std_sort_deque_time = measure_std_sort_time(numbers_deque_copy);
//		bool vector_correct = compare_containers(numbers_vector, numbers_vector_copy);
//		bool deque_correct = compare_containers(numbers_deque, numbers_deque_copy);
//
//		std::cout << std::endl << " --- After sorting --- " << std::endl << std::endl;
//
//		std::cout << "Vector After: ";
//		display_container(numbers_vector);
//
//		std::cout << std::endl;
//
//		std::cout << "Deque After: ";
//		display_container(numbers_deque);
//
//		std::cout << std::endl;
//
//		std::cout << "Vector After (std::sort): ";
//		display_container(numbers_vector_copy);
//
//		std::cout << std::endl;
//
//		std::cout << "Deque After (std::sort): ";
//		display_container(numbers_deque_copy);
//
//		std::cout << std::endl << " --- Value Comparison --- " << std::endl << std::endl;
//
//		std::cout << "Vector Correct: " << (vector_correct ? "Yes" : "No") << std::endl;
//		std::cout << "Deque Correct: " << (deque_correct ? "Yes" : "No") << std::endl;
//
//		std::cout << std::endl << " --- Time Comparison --- " << std::endl << std::endl;
//
//		std::cout << "Time to process with std::vector: " << vector_time << " us" << std::endl;
//		std::cout << "Time to process with std::deque: " << deque_time << " us" << std::endl;
//		std::cout << "Time to process with std::sort on std::vector: " << std_sort_vector_time << " us" << std::endl;
//		std::cout << "Time to process with std::sort on std::deque: " << std_sort_deque_time << " us" << std::endl;

	} catch (const std::exception &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
