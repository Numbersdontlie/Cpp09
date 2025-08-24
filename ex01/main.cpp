/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 12:48:33 by luifer            #+#    #+#             */
/*   Updated: 2025/08/24 13:13:32 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>

int main(){
    RPN rpn;
    std::string expression = "8 9 * 9 - 9 - 9 - 4 - 1 +";
    try {
        int result = rpn.evaluate(expression);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::string expression2 = "7 7 * 7 -";
    try {
        int result2 = rpn.evaluate(expression2);
        std::cout << "Result: " << result2 << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::string expression3 = "1 2 * 2 / 2 * 2 4 - +";
    try {
        int result3 = rpn.evaluate(expression3);
        std::cout << "Result: " << result3 << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
