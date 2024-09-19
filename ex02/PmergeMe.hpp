/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:55:03 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/18 20:55:07 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <cerrno>
#include <climits>
#include <limits.h>

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
uint32_t str_to_uint(const char* str);


/**
 * @brief Implements the Ford-Johnson sorting algorithm (Merge-Insertion Sort) for std::vector.
 *
 * This function sorts a std::vector of unsigned integers using the Ford-Johnson algorithm.
 *
 * @param arr The std::vector of unsigned integers to be sorted.
 */
void ford_johnson(std::vector<uint32_t>& arr);

/**
 * @brief Implements the Ford-Johnson sorting algorithm (Merge-Insertion Sort) for std::deque.
 *
 * This function sorts a std::deque of unsigned integers using the Ford-Johnson algorithm.
 *
 * @param arr The std::deque of unsigned integers to be sorted.
 */
void ford_johnson(std::deque<uint32_t>& arr);

#endif
