/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:17:01 by luifer            #+#    #+#             */
/*   Updated: 2025/08/22 00:25:50 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//constructor
BitcoinExchange::BitcoinExchange() {}

//destcurtor
BitcoinExchange::~BitcoinExchange() {}

//method to load data from csv file into map container
void BitcoinExchange::loadData(const std::string& filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        float rate;
        if (iss >> date >> rate) {
            exchangeRates[date] = rate;
        }
    }
}

//method to get exchange rate for a specific date
float BitcoinExchange::getExchangeRate(const std::string& date) const{
    auto it = exchangeRates.find(date);
    if (it != exchangeRates.end()) {
        return it->second;
    }
    throw std::runtime_error("No exchange rate found for date: " + date);
}