/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 09:45:09 by luifer            #+#    #+#             */
/*   Updated: 2025/08/24 13:02:14 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

//constructor
RPN::RPN() {}

//destructor
RPN::~RPN() {}

RPN::RPN(const RPN& other) {
    (void)other;
}

//copy assignment operator
RPN& RPN::operator=(const RPN& other) {
    (void)other;
    return(*this);
}

// function to validate that the RPN expression is valid
// and therefore can be evaluated
bool RPN::_validateExpression(const std::string& expression) const {
    int numCount = 0;
    int opCount = 0;
    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        if (std::isspace(c)) {
            continue;
        } else if (std::isdigit(c)) {
            numCount++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            opCount++;
            //At any point we shouldn't have more operators than numbers
            if (opCount >= numCount) {
                return false;
            }
        } else {
            return false; // Invalid character
        }
    }
    //Valid RPN: exactly (numCount - 1) opCount
    return (opCount == numCount - 1) && (numCount > 0);
}

//Function to perform the operation
//it will pop the top two elements from the stack, apply the operator with a case statement,
//and push the result back onto the stack
void RPN::_performOperation(char op) {
    if (numStack.size() < 2) {
        throw std::runtime_error("Invalid RPN expression");
    }
    int b = numStack.top(); numStack.pop();
    int a = numStack.top(); numStack.pop();
    switch (op) {
        case '+': numStack.push(a + b); break;
        case '-': numStack.push(a - b); break;
        case '*': numStack.push(a * b); break;
        case '/':
            if (b == 0) {
                throw std::runtime_error("Division by zero not possible");
            }
            numStack.push(a / b);
            break;
        default:
            throw std::runtime_error("Invalid operator try with : + - * /");
    }
}

//Function to evaluate the RPN expression
int RPN::evaluate(const std::string& expression) {
    if (!_validateExpression(expression)) {
        throw std::runtime_error("Invalid RPN expression");
    }
    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];
        if (std::isspace(c))
            continue; // Skip spaces
        else if (std::isdigit(c)) {
            numStack.push(c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            _performOperation(c);
        }
    }
    if (numStack.size() != 1) {
        throw std::runtime_error("Invalid RPN expression");
    }
    return numStack.top();
}
