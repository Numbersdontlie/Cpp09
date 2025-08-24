/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:39:06 by lperez-h          #+#    #+#             */
/*   Updated: 2025/08/24 12:48:30 by luifer           ###   ########.fr       */
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
		RPN &operator=(const RPN& other);
		//stack of numbers
		std::stack<int> numStack;
		//check if operation is valid
		void checkOperation(char op) const;
		
	public:
		RPN();
		
		~RPN();

		int evaluate(const std::string& expression); //ok

		//Methods
		void _performOperation(char op);//ok
		bool _validateExpression(const std::string& expression) const; //ok
};

#endif