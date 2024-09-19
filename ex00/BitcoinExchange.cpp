/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:37:21 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/10 14:37:22 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Trims leading and trailing whitespace from a string.
 * @param str The string to trim.
 * @return The trimmed string.
 */
std::string trim(const std::string &str) {
	std::size_t first = str.find_first_not_of(' ');
	std::size_t last = str.find_last_not_of(' ');
	return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
}


/**
 * @brief Constructor for BitcoinExchange.
 * @param filename Name of the file containing exchange rates.
 *
 * Loads exchange rates from a given file.
 */
BitcoinExchange::BitcoinExchange(const std::string &filename) {
	_init(filename);
}

/**
 * @brief Initializes the exchange rate database from a file.
 * @param filename Name of the file containing exchange rates.
 *
 * Reads exchange rates from a CSV file and stores them in the database.
 * Each line contains a date and a corresponding exchange rate.
 */
void BitcoinExchange::_init(const std::string &filename) {
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Could not open file: " + filename);
	}

	std::string line, date;
	double rate;

	// Skip the header
	std::getline(file, line);

	while (std::getline(file, line)) {

		std::istringstream stream(line);

		std::getline(stream, date, ',');

		if (!(stream >> rate)) {
			std::cout << "Error: parsing rate failed => " << line << std::endl;
			continue;
		}

		_db[parseDate(date)] = rate;
	}
}

/**
 * @brief Converts a string date to a time_t object and checks for validity.
 * @param date Date string in the format YYYY-MM-DD.
 * @return A time_t object representing the date, throws if the date is invalid.
 */
std::time_t BitcoinExchange::parseDate(const std::string &date) const {
	std::tm tm = {};
	std::istringstream ss(date);

	// To verify correct delimiters '-' in the date string
	char delimiter1, delimiter2;
	int year, month, day;

	ss >> year >> delimiter1 >> month >> delimiter2 >> day;

	// Verify correct date format and delimiters
	if (ss.fail() || delimiter1 != '-' || delimiter2 != '-' || !ss.eof()) {

		// Skip any whitespace characters
		ss >> std::ws;

		if (!ss.eof()) {
			throw std::runtime_error("Invalid date format: " + date);
		}
	}

	// Adjust year since tm_year counts years since 1900
	tm.tm_year = year - 1900;

	// Adjust month from 1-12 to 0-11
	tm.tm_mon = month - 1;
	tm.tm_mday = day;

	// Validate tm date
	if (tm.tm_mon < 0 || tm.tm_mon > 11 || tm.tm_mday < 1 || tm.tm_mday > 31) {
		throw std::runtime_error("Invalid date values: " + date);
	}

	std::time_t result = std::mktime(&tm);
	if (result == -1) {
		throw std::runtime_error("Invalid date conversion: " + date);
	}

	return result;
}

/**
 * @brief Runs the bitcoin value calculation.
 * @param inputFilename Name of the file containing bitcoin values and dates.
 *
 * Reads a file where each line contains a date and a bitcoin amount. Calculates the
 * value of the bitcoin amount based on the exchange rate of the closest previous date.
 */
void BitcoinExchange::run(const std::string &inputFilename) {
	std::ifstream file(inputFilename);

	if (!file) {
		throw std::runtime_error("Could not open file: " + inputFilename);
	}

	std::string line;
	std::string date;
	double value;

	// Skip the header
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::istringstream stream(line);

		std::getline(stream, date, '|');

		if (!(stream >> value)) {
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (value < 0) {
			std::cout << "Error: value is not a positive number: " << value << std::endl;
			continue;
		}

		if (value > 1000) {
			std::cout << "Error: value is too large: " << value << std::endl;
			continue;
		}

		try {
			date = trim(date);

			double rate = getRate(date);

			std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << (value * rate)
					  << std::endl;

		} catch (const std::exception &e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}
}

/**
 * @brief Retrieves the exchange rate for a given date.
 * @param date The date for which to find the closest prior exchange rate.
 * @return The exchange rate as a double.
 */
double BitcoinExchange::getRate(const std::string &date) const {
	std::time_t parsedDate = parseDate(date);
	std::map<time_t, double>::const_iterator it = _db.lower_bound(parsedDate);

	if (it == _db.end() || (it->first != parsedDate)) {
		if (it != _db.begin()) {
			--it;
		} else {
			throw std::runtime_error("No rate available before date: " + date);
		}
	}

	return it->second;
}


