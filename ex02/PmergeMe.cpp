/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:55:13 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/18 20:55:19 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/**
 * @brief Converts a string to an unsigned 32-bit integer (uint32_t).
 *
 * This function converts a given string to a 32-bit unsigned integer.
 * It performs error checking to ensure the input string only contains numeric characters
 * and that the converted value is within the range of uint32_t. If the string contains invalid characters
 * or the value exceeds the range of uint32_t, it throws an appropriate exception.
 *
 * @param str A C-style string to be converted to an unsigned integer.
 * @return The converted unsigned integer (uint32_t).
 * @throws std::invalid_argument If the string contains non-numeric characters or the conversion fails.
 * @throws std::overflow_error If the number exceeds the range of uint32_t.
 */
uint32_t str_to_uint(const char *str) {
	// Pointer to the first invalid character in the input string.
	char *endptr;

	// Reset errno before calling strtol.
	errno = 0;

	// Convert the input string to a long integer.
	long num = std::strtol(str, &endptr, 10);

	// Check for conversion errors : non-numeric characters, overflow, or underflow.
	if (*endptr != '\0' || errno != 0 || num < 0 || num > UINT32_MAX) {
		throw std::invalid_argument("Invalid input number");
	}

	// Return the converted value as an unsigned integer.
	return static_cast<uint32_t>(num);
}


/**
 * @brief Generates the Jacobstal sequence up to the nth element.
 *
 * This function generates the Jacobstal sequence up to the nth element.
 * The Jacobstal sequence is a sequence of integers where each element is the sum of
 * the two preceding elements multiplied by two. The first two elements are 0 and 1.
 *
 * @param n The number of elements to generate in the Jacobstal sequence.
 * @return A vector containing the Jacobstal sequence up to the nth element.
 */
std::vector <size_t> jacobstal_sequence(size_t n) {
	std::vector <size_t> jacobstal;
	size_t j0 = 0;
	size_t j1 = 1;

	// Generate the Jacobstal sequence.
	jacobstal.push_back(j0);
	if (n > 1) {
		jacobstal.push_back(j1);
	}

	// Calculate the remaining elements of the sequence.
	for (size_t i = 2; i < n; i++) {
		jacobstal.push_back(jacobstal[i - 1] + 2 * jacobstal[i - 2]);
	}

	return jacobstal;
}


/**
 * @brief Implements the Ford-Johnson sorting algorithm (Merge-Insertion Sort) for std::vector.
 *
 * This function sorts a vector of unsigned integers using the Ford-Johnson algorithm.
 * The algorithm pairs consecutive elements, sorts those pairs, and merges them back into
 * a final sorted sequence. It uses binary insertion to maintain the sorted order.
 *
 * @param arr The vector of unsigned integers to be sorted.
 */
void ford_johnson(std::vector <uint32_t> &arr) {

	// Check if the vector is empty.
	if (arr.empty()) {
		return;
	}

	// Holds the last unpaired element if the vector has an odd size.
	std::vector <uint32_t> straggler;

	// Check if the vector has an odd size.
	if (arr.size() % 2) {

		// Save the last element as the straggler.
		straggler.push_back(arr.back());

		// Remove it from the original vector.
		arr.pop_back();
	}

	// Pair consecutive elements and store them in a vector of pairs.
	std::vector <std::pair<uint32_t, uint32_t> > pairs;

	// Pair consecutive elements.
	for (size_t i = 0; i < arr.size(); i += 2) {
		pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}

	// Sort each pair so that the first element is always larger.
	for (size_t i = 0; i < pairs.size(); i++) {
		if (pairs[i].first < pairs[i].second) {
			std::swap(pairs[i].first, pairs[i].second);
		}
	}

	// Sort the pairs based on their first elements using an insertion sort.
	for (size_t i = 1; i < pairs.size(); i++) {
		std::pair <uint32_t, uint32_t> key = pairs[i];

		size_t j = i;

		// Insert the key pair into the sorted sequence.
		while (j > 0 && pairs[j - 1].first > key.first) {
			pairs[j] = pairs[j - 1];
			j--;
		}
		pairs[j] = key;
	}

	// Separate pairs into two sequences:
	// 1. S (first elements of each pair)
	// 2. pend (second elements of each pair)
	std::vector <uint32_t> S;
	std::vector <uint32_t> pend;

	for (size_t i = 0; i < pairs.size(); i++) {
		S.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	// Insert the first element of pend at the beginning of S.
	S.insert(S.begin(), pend[0]);

	// Generate Jacobstal sequence for the pend vector.
	std::vector <size_t> jacobstal_indices = jacobstal_sequence(pend.size());

	// Insert remaining elements of pend into S using Jacobstal sequence
	for (size_t i = 1; i < jacobstal_indices.size(); i++) {
		size_t idx = jacobstal_indices[i];

		// Check if the index is within the range of pend.
		if (idx < pend.size()) {
			// Insert the element into S in sorted order.
			S.insert(std::lower_bound(S.begin(), S.end(), pend[idx]), pend[idx]);
		}
	}

	// If there was a straggler, insert it into S in sorted order.
	if (!straggler.empty()) {
		S.insert(std::lower_bound(S.begin(), S.end(), straggler[0]), straggler[0]);
	}

	// Copy the sorted result back into the original vector.
	arr = S;
}

/**
 * @brief Implements the Ford-Johnson sorting algorithm (Merge-Insertion Sort) for std::deque.
 *
 * This function sorts a deque of unsigned integers using the Ford-Johnson algorithm.
 * The algorithm pairs consecutive elements, sorts those pairs, and merges them back into
 * a final sorted sequence. It uses binary insertion to maintain the sorted order.
 *
 * @param arr The deque of unsigned integers to be sorted.
 */
void ford_johnson(std::deque <uint32_t> &arr) {

	// Check if the deque is empty.
	if (arr.empty()) {
		return;
	}

	// Holds the last unpaired element if the deque has an odd size.
	std::deque <uint32_t> straggler;

	// Check if the deque has an odd size.
	if (arr.size() % 2) {
		straggler.push_back(arr.back());
		arr.pop_back();
	}

	// Pair consecutive elements and store them in a deque of pairs.
	std::deque <std::pair<uint32_t, uint32_t> > pairs;

	// Pair consecutive elements.
	for (size_t i = 0; i < arr.size(); i += 2) {
		pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}

	// Sort each pair so that the first element is always larger.
	for (size_t i = 0; i < pairs.size(); i++) {
		if (pairs[i].first < pairs[i].second) {
			std::swap(pairs[i].first, pairs[i].second);
		}
	}

	// Sort the pairs based on their first elements using an insertion sort.
	for (size_t i = 1; i < pairs.size(); i++) {
		std::pair <uint32_t, uint32_t> key = pairs[i];
		size_t j = i;
		while (j > 0 && pairs[j - 1].first > key.first) {
			pairs[j] = pairs[j - 1];
			j--;
		}
		pairs[j] = key;
	}

	// Separate pairs into two sequences:
	// 1. S (first elements of each pair)
	// 2. pend (second elements of each pair)
	std::deque <uint32_t> S;
	std::deque <uint32_t> pend;

	for (size_t i = 0; i < pairs.size(); i++) {
		S.push_back(pairs[i].first);
		pend.push_back(pairs[i].second);
	}

	// Insert the first element of pend at the beginning of S.
	S.insert(S.begin(), pend[0]);

	// Generate Jacobstal sequence for the pend deque.
	std::vector <size_t> jacobstal_indices = jacobstal_sequence(pend.size());

	// Insert remaining elements of pend into S using Jacobstal sequence
	for (size_t i = 1; i < jacobstal_indices.size(); i++) {
		size_t idx = jacobstal_indices[i];

		// Check if the index is within the range of pend.
		if (idx < pend.size()) {
			// Insert the element into S in sorted order.
			S.insert(std::lower_bound(S.begin(), S.end(), pend[idx]), pend[idx]);
		}
	}

	// If there was a straggler, insert it into S in sorted order.
	if (!straggler.empty()) {
		S.insert(std::lower_bound(S.begin(), S.end(), straggler[0]), straggler[0]);
	}

	// Copy the sorted result back into the original deque.
	arr = S;
}
