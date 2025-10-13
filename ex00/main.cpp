/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 00:27:13 by luifer            #+#    #+#             */
/*   Updated: 2025/10/13 07:14:55 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    std::string inputFileName = argv[1];
    try {
        BitcoinExchange exchange;
        exchange.loadData("data.csv");
        exchange.processInputFile(inputFileName);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}