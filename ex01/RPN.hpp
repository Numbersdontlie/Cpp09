/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lperez-h <lperez-h@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:39:06 by lperez-h          #+#    #+#             */
/*   Updated: 2025/08/22 16:43:25 by lperez-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <string>
#include <stack>
#include <stdexcept>
#include <cctype>

class RPN {
	private:
		//canonical form
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		//stack of numbers
		std::stack<int> numStack;
		//check if operation is valid
		void checkOperation(char op) const;
		
	public:
		RPN();
		
		~RPN();

		int evaluate(const std::string& expression);

		//Methods
		void _performOperation(char op);
		void _checkExpression(const std::string& expression) const;
		void _validateCharacter(char c) const;
		void _validateStackSize() const;
		void _validateOperation(char op) const;
		void _validateExpression(const std::string& expression) const;
};