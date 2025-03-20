/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:13:55 by ltheveni          #+#    #+#             */
/*   Updated: 2025/03/20 16:39:48 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"
#include <cctype>

void parse_spaces(std::string &s) {
  s.erase(0, s.find_first_not_of(" \t"));
  s.erase(s.find_last_not_of(" \t") + 1);
}

int check_date(const std::string &date) {
  if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
    std::cerr << "Error: Invalid format (YYYY-MM-DD): '" << date << "'"
              << std::endl;
    return 0;
  }

  for (int i = 0; i < 10; ++i) {
    if (i == 4 || i == 7)
      continue;
    if (!std::isdigit(date[i])) {
      std::cerr << "Error: Invalid character in date: '" << date << "'"
                << std::endl;
      return 0;
    }
  }

  int year, month, day;
  std::istringstream ss(date);
  char dash1, dash2;
  if (!(ss >> year >> dash1 >> month >> dash2 >> day))
    return 0;
  if (dash1 != '-' || dash2 != '-') {
    std::cerr << "Error: Incorrect separators ('-'): '" << date << "'"
              << std::endl;
    return 0;
  }
  if (year < 0) {
    std::cerr << "Error: Invalid year: '" << date << "'" << std::endl;
    return 0;
  }
  if (month < 1 || month > 12) {
    std::cerr << "Error: Invalid month: '" << date << "'" << std::endl;
    return 0;
  }
  if (day < 1 || day > 31) {
    std::cerr << "Error: Invalid day: '" << date << "'" << std::endl;
    return 0;
  }
  return 1;
}

int check_value(const std::string &value) {
  char *endp;
  double num = std::strtod(value.c_str(), &endp);

  if (*endp != '\0') {
    std::cerr << "Error: Invalid number format: " << value << std::endl;
    return 0;
  }
  if (num < 0) {
    std::cerr << "Error: not a positive number." << std::endl;
    return 0;
  }
  if (num > 1000) {
    std::cerr << "Error: too large a number." << std::endl;
    return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Error: could not open file." << std::endl;
    return 1;
  }

  BitcoinExchange btc("data.csv");

  std::string line;
  std::ifstream file(argv[1], std::ios::in);
  if (!file) {
    std::cerr << "Error: open file data.csv" << std::endl;
    exit(1);
  }
  bool first_line = true;
  while (std::getline(file, line)) {
    if (first_line) {
      first_line = false;
      continue;
    }
    std::istringstream ss(line);
    std::string date;
    std::string value_str;
    float value = 0.0;

    if (std::getline(ss, date, '|') && std::getline(ss, value_str)) {
      parse_spaces(date);
      parse_spaces(value_str);

      if (!check_date(date))
        continue;
      if (!check_value(value_str))
        continue;

      value = static_cast<float>(atof(value_str.c_str()));
      float exchange_rate = btc.getExchangeRate(date, value);
      std::cout << date << " => " << value_str << " = " << exchange_rate
                << std::endl;
    } else {
      std::cerr << "Error: bad input => " << line << std::endl;
    }
  }
  file.close();
  (void)argv;
  return 0;
}
