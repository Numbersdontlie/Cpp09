/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:06 by luifer            #+#    #+#             */
/*   Updated: 2025/10/06 01:28:02 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <sys/time.h>
#include <iomanip>
#include <sstream>
#include <climits>

class PmergeMe {
    private:
        //canonical form
        PmergeMe(const PmergeMe &other);
        PmergeMe& operator=(const PmergeMe &other);

        //vector implementation
        std::vector<int> vectorData;
        void fordJohnsonVector(std::vector<int> &arr);
        void insertionSortVector(std::vector<int> &arr, int left, int right);
        int binarySearchVector(const std::vector<int> &arr, int target, int left, int right);
        static void FordJohnsonSort(std::vector<int> &arr);

        //deque implementation
        std::deque<int> dequeData;
        void fordJohnsonDeque(std::deque<int> &arr);
        void insertionSortDeque(std::deque<int> &arr, int left, int right);
        int binarySearchDeque(const std::deque<int> &arr, int target, int left, int right);
        static void FordJohnsonSortDeque(std::deque<int> &arr);
        int binarySearchDequeV2(const std::deque<int> &arr, int target, int left, int right);

        //Utility functions
        bool isValidNumber(const std::string &str);
        void parseInput(int argc, char **argv);

    public:
        PmergeMe();
        ~PmergeMe();
        void run(int argc, char **argv);
};

#endif