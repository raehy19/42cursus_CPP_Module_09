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
 * @brief Generates an Jacobstal sequence for insertion.
 *
 * This function generates a Jacobstal insertion sequence for the Ford-Johnson algorithm.
 *
 * @param left The left index of the sequence.
 * @param right The right index of the sequence.
 * @param sequence The vector to store the generated sequence.
 */
void generate_insertion_sequence(size_t left, size_t right, std::vector <size_t> &sequence) {
	if (left > right) return;
	size_t mid = left + (right - left) / 2;
	sequence.push_back(mid);
	if (mid > 0) {
		generate_insertion_sequence(left, mid - 1, sequence);
	}
	generate_insertion_sequence(mid + 1, right, sequence);
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

	// Base case: If the vector has 0 or 1 elements, it is already sorted.
	if (arr.size() <= 1) {
		return;
	}

	// Special case: If the vector has up to 16 elements, use insertion sort.
	if (arr.size() <= 16) {

		// insertion sort
		for (size_t i = 1; i < arr.size(); i++) {
			uint32_t key = arr[i];
			size_t j = i;
			while (j > 0 && arr[j - 1] > key) {
				arr[j] = arr[j - 1];
				j--;
			}
			arr[j] = key;
		}
		return;
	}

	// Holds the last unpaired element if the vector has an odd size.
	std::vector <uint32_t> straggler;

	// Check if the vector has an odd size.
	if (arr.size() % 2) {
		straggler.push_back(arr.back());
		arr.pop_back();
	}

	// Pair consecutive elements and store them in a vector of pairs.
	std::vector <std::pair<uint32_t, uint32_t> > pairs;

	// Pair consecutive elements and sort.
	for (size_t i = 0; i < arr.size(); i += 2) {
		if (arr[i] < arr[i + 1]) {
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		} else {
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		}
	}

	// Separate pairs into two sequences:
	// 1. S (first elements of each pair)
	std::vector <uint32_t> S;

	for (size_t i = 0; i < pairs.size(); i++) {
		S.push_back(pairs[i].first);
	}

	// Sort S using Ford-Johnson algorithm.
	ford_johnson(S);

	// 2. pend (second elements of each pair)
	std::vector <uint32_t> pend;

	for (size_t i = 0; i < pairs.size(); i++) {
		pend.push_back(pairs[i].second);
	}

	// Insert pend[0] to S
	std::vector<uint32_t>::iterator it = std::lower_bound(S.begin(), S.end(), pend[0]);
	S.insert(it, pend[0]);

	// Generate insertion sequence for the pend vector.
	std::vector <size_t> insertion_sequence;
	generate_insertion_sequence(1, pend.size() - 1, insertion_sequence);

	// Insert remaining elements of pend into S using insertion sequence.
	for (size_t i = 0; i < insertion_sequence.size(); i++) {
		size_t idx = insertion_sequence[i];
		if (idx < pend.size()) {
			uint32_t value_to_insert = pend[idx];

			it = std::lower_bound(S.begin(), S.end(), value_to_insert);
			S.insert(it, value_to_insert);
		}
	}

	// If there was a straggler, insert it into S in sorted order.
	if (!straggler.empty()) {
		it = std::lower_bound(S.begin(), S.end(), straggler[0]);
		S.insert(it, straggler[0]);
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

	// Base case: If the deque has 0 or 1 elements, it is already sorted.
	if (arr.size() <= 1) {
		return;
	}

	// Special case: If the deque has up to 16 elements, use insertion sort.
	if (arr.size() <= 16) {

		// insertion sort
		for (size_t i = 1; i < arr.size(); i++) {
			uint32_t key = arr[i];
			size_t j = i;
			while (j > 0 && arr[j - 1] > key) {
				arr[j] = arr[j - 1];
				j--;
			}
			arr[j] = key;
		}
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

	// Pair consecutive elements and sort.
	for (size_t i = 0; i < arr.size(); i += 2) {
		if (arr[i] < arr[i + 1]) {
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		} else {
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		}
	}

	// Separate pairs into two sequences:
	// 1. S (first elements of each pair)
	std::deque <uint32_t> S;

	for (size_t i = 0; i < pairs.size(); i++) {
		S.push_back(pairs[i].first);
	}

	// Sort the S sequence using Ford-Johnson.
	ford_johnson(S);

	// 2. pend (second elements of each pair)
	std::deque <uint32_t> pend;

	for (size_t i = 0; i < pairs.size(); i++) {
		pend.push_back(pairs[i].second);
	}

	// Insert pend[0] to S
	std::deque<uint32_t>::iterator it = std::lower_bound(S.begin(), S.end(), pend[0]);
	S.insert(it, pend[0]);

	// Generate insertion sequence for the pend vector.
	std::vector <size_t> insertion_sequence;
	generate_insertion_sequence(1, pend.size() - 1, insertion_sequence);

	// Insert remaining elements of pend into S using insertion sequence.
	for (size_t i = 0; i < insertion_sequence.size(); i++) {
		size_t idx = insertion_sequence[i];
		if (idx < pend.size()) {
			uint32_t value_to_insert = pend[idx];

			it = std::lower_bound(S.begin(), S.end(), value_to_insert);
			S.insert(it, value_to_insert);
		}
	}

	// If there was a straggler, insert it into S in sorted order.
	if (!straggler.empty()) {
		it = std::lower_bound(S.begin(), S.end(), straggler[0]);
		S.insert(it, straggler[0]);
	}

	// Copy the sorted result back into the original deque.
	arr = S;
}
