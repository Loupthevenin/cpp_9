/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltheveni <ltheveni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:09:07 by ltheveni          #+#    #+#             */
/*   Updated: 2025/03/25 20:33:24 by ltheveni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(int argc, char **argv) {
  for (int i = 1; i < argc; ++i) {
    std::stringstream ss(argv[i]);
    int num;
    if (!(ss >> num) || num < 0)
      throw std::runtime_error("Error: Invalid input detected");
    vec.push_back(num);
    deq.push_back(num);
  }
}

PmergeMe::PmergeMe(const PmergeMe &other) : vec(other.vec), deq(other.deq) {}

PmergeMe::~PmergeMe() {}

void PmergeMe::print_args(const std::string &message) {
  std::cout << message;
  for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    std::cout << " " << *it;
  std::cout << std::endl;
}

void PmergeMe::sort_vec(std::vector<int> &arr) {
  if (arr.size() <= 1)
    return;

  int n = arr.size();

  for (int size = 1; size < n; size *= 2) {
    for (int low = 0; low < n - size; low += 2 * size) {
      int mid = std::min(low + size - 1, n - 1);
      int high = std::min(low + 2 * size - 1, n - 1);

      std::vector<int> left(arr.begin() + low, arr.begin() + mid + 1);
      std::vector<int> right(arr.begin() + mid + 1, arr.begin() + high + 1);

      size_t i = 0;
      size_t j = 0;
      int k = low;
      while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
          arr[k] = left[i];
          ++i;
        } else {
          arr[k] = right[j];
          ++j;
        };
        ++k;
      }

      while (i < left.size()) {
        arr[k] = left[i];
        ++i;
        ++k;
      }

      while (j < right.size()) {
        arr[k] = right[j];
        ++j;
        ++k;
      }
    }
  }
}

void PmergeMe::merge_sort_vec() {
  if (vec.size() <= 1)
    return;

  std::vector<int> small, large;

  // Regroupement en pair;
  for (size_t i = 0; i + 1 < vec.size(); i += 2) {
    // Plus petit en premier;
    if (vec[i] > vec[i + 1])
      std::swap(vec[i], vec[i + 1]);
    small.push_back(vec[i]);
    large.push_back(vec[i + 1]);
  }

  // Si impair;
  if (vec.size() % 2 == 1)
    small.push_back(vec[vec.size() - 1]);

  // Tri merge_sort;
  // Efficace car fusionne rapidement => acces direct au indices et divise bien
  // le tableau;
  sort_vec(small);

  // Insert;
  for (size_t i = 0; i < large.size(); ++i) {
    small.insert(std::lower_bound(small.begin(), small.end(), large[i]),
                 large[i]);
  }

  vec = small;
}

void PmergeMe::sort_deq(std::deque<int> &arr) {
  for (size_t i = 0; i < arr.size(); ++i) {
    int key = arr[i];
    size_t j = i;

    // Element plus grands vers la droite;
    while (j > 0 && arr[j - 1] > key) {
      arr[j] = arr[j - 1];
      --j;
    }

    // Insert
    arr[j] = key;
  }
}

void PmergeMe::merge_sort_deq() {
  if (deq.size() <= 1)
    return;

  std::deque<int> small, large;

  // Regroupement en pair;
  for (size_t i = 0; i + 1 < deq.size(); i += 2) {
    // Plus petit en premier;
    if (deq[i] > deq[i + 1])
      std::swap(deq[i], deq[i + 1]);
    small.push_back(deq[i]);
    large.push_back(deq[i + 1]);
  }

  // Si impair;
  if (deq.size() % 2 == 1)
    small.push_back(deq[deq.size() - 1]);

  // Tri Insertion_sort;
  // Plus adapté car évite les copies couteuse et les problèmes d'accès.
  sort_deq(small);

  // Insert;
  for (size_t i = 0; i < large.size(); ++i) {
    small.insert(std::lower_bound(small.begin(), small.end(), large[i]),
                 large[i]);
  }

  deq = small;
}

void PmergeMe::process() {
  print_args("Before:");

  double start_vec = get_time();
  merge_sort_vec();
  double end_vec = get_time();
  double time_vec = end_vec - start_vec;

  double start_deq = get_time();
  merge_sort_deq();
  double end_deq = get_time();
  double time_deq = end_deq - start_deq;

  print_args("After:");

  if (!is_sorted(vec) || !is_sorted(deq))
    std::cerr << "Not sort" << std::endl;

  std::cout << "Time to process a range of " << vec.size()
            << " element with std::vector: " << time_vec << " us" << std::endl;
  std::cout << "Time to process a range of " << deq.size()
            << " element with std::deque: " << time_deq << " us" << std::endl;
}

double get_time() {
  struct timeval time;
  gettimeofday(&time, NULL);
  return time.tv_sec * 1000000.0 + time.tv_usec;
}
