/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjeong <rjeong@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:37:26 by rjeong            #+#    #+#             */
/*   Updated: 2024/09/10 14:37:28 by rjeong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <ctime>

/**
 * @brief A class representing a Bitcoin exchange rate database.
 *
 * The BitcoinExchange class loads exchange rates from a file and calculates the value of bitcoins on specific dates.
 */
class BitcoinExchange {
	public:
		explicit BitcoinExchange(const std::string &filename = "data.csv");

		void run(const std::string &inputFilename);

	private:
		std::map<time_t, double> _db;

		void _init(const std::string &filename);

		double getRate(const std::string &date) const;

		std::time_t parseDate(const std::string &date) const;
};

#endif
