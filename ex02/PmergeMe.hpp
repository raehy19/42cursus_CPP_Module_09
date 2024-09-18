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
#include <limits.h>
#include <algorithm>

/**
 * @brief Converts a string to an unsigned 32-bit integer (uint32_t).
 *
 * This function takes a string and converts it to an unsigned integer, while performing
 * error checks for invalid inputs.
 *
 * @param str String to be converted.
 * @return The converted unsigned integer.
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
