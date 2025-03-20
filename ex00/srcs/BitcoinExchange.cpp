/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:10:28 by ltheveni          #+#    #+#             */
/*   Updated: 2025/03/20 16:48:11 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &dataPath) {
  std::string line;

  std::ifstream file(dataPath.c_str(), std::ios::in);
  if (!file) {
    std::cerr << "Error: open file data.csv" << std::endl;
    exit(1);
  }
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string date;
    std::string exchange_rate_str;

    if (std::getline(ss, date, ',') && std::getline(ss, exchange_rate_str)) {
      float exchange_rate =
          static_cast<float>(std::atof(exchange_rate_str.c_str()));
      data[date] = exchange_rate;
    }
  }
  file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
    : data(other.data) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
  if (this != &other) {
    data = other.data;
  }
  return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::map<std::string, float> BitcoinExchange::getData() const { return data; }

float BitcoinExchange::getExchangeRate(const std::string &date, float value) {
  std::map<std::string, float>::iterator it = data.lower_bound(date);

  if (it != data.end() && it->first == date)
    return it->second * value;
  --it;
  return it->second * value;
}
