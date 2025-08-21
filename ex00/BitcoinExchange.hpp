/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:12:07 by luifer            #+#    #+#             */
/*   Updated: 2025/08/22 00:14:13 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>

class BitcoinExchange {
public:
    BitcoinExchange();
    ~BitcoinExchange();

    void loadData(const std::string& filename);
    float getExchangeRate(const std::string& date) const;

private:
    std::map<std::string, float> exchangeRates;
};

#endif