/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:12:52 by ltheveni          #+#    #+#             */
/*   Updated: 2025/03/24 09:48:01 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN &other) : stack(other.stack) {}

RPN &RPN::operator=(const RPN &other) {
  if (this != &other) {
    stack = other.stack;
  }
  return *this;
}

RPN::~RPN() {}

void RPN::push(int n) { stack.push(n); }

int RPN::handleOperator(std::string token) {
  int b = stack.top();
  stack.pop();
  int a = stack.top();
  stack.pop();

  if (token == "+")
    stack.push(a + b);
  else if (token == "-")
    stack.push(a - b);
  else if (token == "*")
    stack.push(a * b);
  else if (token == "/") {
    if (b == 0) {
      std::cerr << "Error: Division by zero" << std::endl;
      return -1;
    }
    stack.push(a / b);
  }
  return 0;
}

int RPN::getResult() const { return stack.top(); }
int RPN::getSize() const { return stack.size(); }
