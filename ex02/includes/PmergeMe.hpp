/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:09:19 by ltheveni          #+#    #+#             */
/*   Updated: 2025/03/25 20:17:09 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <ctime>
#include <deque>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/time.h>
#include <vector>

class PmergeMe {
private:
  std::vector<int> vec;
  std::deque<int> deq;

public:
  PmergeMe();
  PmergeMe(int argc, char **argv);
  PmergeMe(const PmergeMe &other);
  PmergeMe &operator=(const PmergeMe &other);
  ~PmergeMe();

  void print_args(const std::string &message);

  void sort_vec(std::vector<int> &arr);
  void merge_sort_vec();
  void sort_deq(std::deque<int> &arr);
  void merge_sort_deq();
  template <typename T> bool is_sorted(const T &arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
      if (arr[i - 1] > arr[i])
        return false;
    }
    return true;
  };
  void process();
};

double get_time();
