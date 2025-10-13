/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:12:07 by luifer            #+#    #+#             */
/*   Updated: 2025/10/13 06:48:08 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

class BitcoinExchange {
public:
    BitcoinExchange();
    ~BitcoinExchange();

    void loadData(const std::string& filename);
    float getExchangeRate(const std::string& date) const;
	bool isValidDate(const std::string& date) const;
	bool isValidRate(const std::string& rate) const;
	void processInputFile(const std::string& inputFileName) const;

private:
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
    std::map<std::string, float> exchangeRates;
};

#endif