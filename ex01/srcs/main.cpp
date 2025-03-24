/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:14:35 by ltheveni          #+#    #+#             */
/*   Updated: 2025/03/24 09:45:11 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RPN.hpp"
#include <cctype>
#include <sstream>

bool check_strings(std::string &input) {
  std::istringstream iss(input);
  std::string token;

  while (iss >> token) {
    if (token.size() == 1 && (isdigit(token[0]) || token == "*" ||
                              token == "+" || token == "-" || token == "/"))
      continue;
    std::cerr << "Error: Invalid token found: " << token << std::endl;
    return false;
  }
  return true;
}

int evaluateRPN(std::string &input, bool &isError) {
  std::istringstream iss(input);
  std::string token;
  RPN rpn;

  while (iss >> token) {
    if (isdigit(token[0]))
      rpn.push(token[0] - '0');
    else {
      if (rpn.getSize() < 2) {
        std::cerr << "Error: Not enough operands for operation: " << token
                  << std::endl;
        isError = true;
        return -1;
      }
      if (rpn.handleOperator(token) == -1) {
        isError = true;
        return -1;
      }
    }
  }
  if (rpn.getSize() != 1) {
    std::cerr << "Error: too many operands" << std::endl;
    isError = true;
    return -1;
  }
  return rpn.getResult();
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "./RPN EXPRESSION" << std::endl;
    return 1;
  }
  std::string input = argv[1];
  if (!check_strings(input))
    return 1;

  bool isError = false;
  int result = evaluateRPN(input, isError);
  if (isError)
    return 1;

  std::cout << result << std::endl;
  return 0;
}
