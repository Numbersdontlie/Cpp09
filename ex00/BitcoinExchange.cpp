/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:17:01 by luifer            #+#    #+#             */
/*   Updated: 2025/08/22 15:40:38 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

//constructor
BitcoinExchange::BitcoinExchange() {}

//destructor
BitcoinExchange::~BitcoinExchange() {}

//method to check if a date is valid, it will check
//for the format size and the presence of digits and dashes
bool BitcoinExchange::isValidDate(const std::string& date) const {
	// A simple date validation (YYYY-MM-DD)
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
		return false;
	}
	for (size_t i = 0; i < date.size(); ++i) {
		if ((i == 4 || i == 7) && date[i] == '-') {
			continue;
		}
		if (!std::isdigit(date[i])) {
			return false;
		}
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if(year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	return true;
}

bool BitcoinExchange::isValidRate(const std::string& rate) const {
	// Check if the rate is a valid float number
	if (rate.empty() || rate == "0") {
		return false;
	}
	float value = std::strtof(rate.c_str(); nullptr);
	if(value < 0 || value > 1000) {
		return false; // Rate must be between 0 and 1000
	}
	return true;
}

//method to load data from csv file into map container
//it checks if the file can be opened, reads each line, splits it by comma,
// and stores the date and exchange rate in the map.
void BitcoinExchange::loadData(const std::string& filename){
    std::ifstream file(filename.c_str());
	//c_str() converts std::string to const char* for file opening
    if (!file.is_open()) {
		throw std::runtime_error("Could not open file: " + filename);
	}
    std::string line;
	std::getline(file, line); // Skip the header line
    while (std::getline(file, line)) {
		size_t commaPos = line.find(',');
		if(commaPos != std::string::npos){
			std::string date = line.substr(0, commaPos);
			std::string rateStr = line.substr(commaPos + 1);
			//Remove whitespaces
			date.erase(date.find_last_not_of(" \t\r\n") + 1);
			rateStr.erase(0, rateStr.find_first_not_of(" \t\r\n"));
			rateStr.erase(rateStr.find_last_not_of(" \t\r\n") + 1);
			//validate the date
			if(isValidDate(date)){
				float rate = std::atof(rateStr.c_str());
				exchangeRates[date] = rate;
			}
		}
    }
	file.close();
}

//method to get exchange rate for a specific date (or closest lowest date)
float BitcoinExchange::getExchangeRate(const std::string& date) const{
	// check if the date exists in the map. It need to use the i
	// iterator std::map<std::string, float>::const_iterator it
    std::map<std::string, float>::const_iterator it = exchangeRates.find(date);
    if (it != exchangeRates.end()) {
        return it->second; //to access the exchange rate (2nd value)
    }
	// If the date is not found, find the closest lower date
	it = exchangeRates.lower_bound(date);
	if (it == exchangeRates.begin()){
		throw std::runtime_error("No exchange rate available for date: " + date);
	}
	--it; // Get the previous and therefore lower element
	return it->second;
}