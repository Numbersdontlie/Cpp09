/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:53:25 by luifer            #+#    #+#             */
/*   Updated: 2025/10/06 18:13:32 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

//Function to check if the number passed as parameter has a valid format
bool PmergeMe::isValidNumber(const std::string &str){
    if(str.empty())
        return false;
    for(size_t i = 0; i < str.length(); ++i){
        if(!std::isdigit(str[i]))
            return false;
    }
    //check overflow
    std::istringstream iss(str);
    long num;
    iss >> num;
    return(num >= 0 && num <= INT_MAX);
}

//Function to parse the input and create the data structures
//from the command line arguments
void PmergeMe::parseInput(int argc, char **argv){
    if(argc < 2){
        throw std::runtime_error("Error: No input numbers provided.");
    }
    for(int i = 1; i < argc; ++i){
        if(!isValidNumber(argv[i])){
            throw std::runtime_error("Error: Invalid number format.");
        }
        int num = std::atoi(argv[i]);
        vectorData.push_back(num);
        dequeData.push_back(num);
    }
    if(vectorData.size() > 3000){
        throw std::runtime_error("Error: Too many input numbers (max 3000).");
    }
}

//Vector implementation of the binary search
//Find the position to insert the target in the sorted vector
int PmergeMe::binarySearchVector(const std::vector<int> &arr, int target, int left, int right){
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

//Function to perform insertion sort on a vector
//it iterate the vector and insert elements into their correct position
//it calls the binary search to find the correct position
//to make the insertion more efficient
void PmergeMe::insertionSortVector(std::vector<int> &arr, int left, int right){
    for(int i = left + 1; i <= right; ++i){
        int key = arr[i];
        int pos = binarySearchVector(arr, key, left, i - 1);
        for(int j = i; j > pos; --j){
            arr[j] = arr[j - 1];
        }
        arr[pos] = key;
    }
}

//Function to implement the Ford-Johnson sorting network
//in a vector. It first creates pairs of elements and sorts them and checks that there
//If there is an odd element, it will be handled separately
//it will recursively sort the pairs by their larger elements
//and reconstruct the sorted array with the largest merged elements
//it build the main chain with the largest merged elements and insert smallest elements
//it will insert the odd element if it exists
void PmergeMe::fordJohnsonVector(std::vector<int> &arr){
    int n = arr.size();
    if(n <= 1)
        return;
    //small arrays -> use insertion sorts
    if(n <= 20){
        insertionSortVector(arr, 0, n - 1);
        return;
    }
    //create pairs of numbers and sort them
    std::vector<std::pair<int, int> > pairs;
    bool hasOdd = (n % 2 == 1);
    int oddElement = hasOdd ? arr[n - 1] : 0;

    for(int i = 0; i < n - (hasOdd ? 1 : 0); i += 2){
        if(arr[i] > arr[i + 1]){
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        } else {
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        }
    }

    //sort pairs by their larger elements (recursive call)
    std::vector<int> largers;
    for(size_t i = 0; i < pairs.size(); ++i){
        largers.push_back(pairs[i].first);
    }
    fordJohnsonVector(largers);

    //Reconstruct pairs according to sorted larger elements
    std::vector<std::pair<int, int> > sortedPairs;
    for(size_t i = 0; i < largers.size(); ++i){
        for(size_t j = 0; j < pairs.size(); ++j){
            if(pairs[j].first == largers[i]){
                sortedPairs.push_back(pairs[j]);
                break;
            }
        }
    }

    //Use a 'used' flag to avoid reusing the same pair
    std::vector<std::pair<int, int> > sortedPairsFlagged;
    std::vector<bool> used(pairs.size(), false);
    for(size_t i = 0; i < largers.size(); ++i){
        for(size_t j = 0; j < pairs.size(); ++j){
            if(!used[j] && pairs[j].first == largers[i]){
                sortedPairsFlagged.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    //Build main chain with larger elements
    std::vector<int> mainChain;
    for(size_t i = 0; i < sortedPairs.size(); ++i)
        mainChain.push_back(sortedPairs[i].first);
    
    //Insert smaller elements using binary search
    for(size_t i = 0; i < sortedPairs.size(); ++i){
        int pos = binarySearchVector(mainChain, sortedPairs[i].second, 0, mainChain.size() - 1);
        mainChain.insert(mainChain.begin() + pos, sortedPairs[i].second);
    }

    //insert odd element if exists
    if(hasOdd){
        int pos = binarySearchVector(mainChain, oddElement, 0, mainChain.size() - 1);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }
    arr = mainChain;
}

//Deque implementation (similar structure to vector)
int PmergeMe::binarySearchDeque(const std::deque<int> &arr, int target, int left, int right){
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(arr[mid] < target){
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;
}

void PmergeMe::insertionSortDeque(std::deque<int> &arr, int left, int right){
    for(int i = left + 1; i <= right; ++i){
        int key = arr[i];
        int pos = binarySearchDeque(arr, key, left, i - 1);
        
        for(int j = i; j > pos; --j){
            arr[j] = arr[j - 1];
        }
        arr[pos] = key;
    }
}

//Deque implementation
//Function to implement the Ford-Johnson sorting network
//in a deque. It first creates pairs of elements and sorts them and checks that there
//If there is an odd element, it will be handled separately
//it will recursively sort the pairs by their larger elements
//and reconstruct the sorted array with the largest merged elements
//it build the main chain with the largest merged elements and insert smallest elements
//it will insert the odd element if it exists
void PmergeMe::fordJohnsonDeque(std::deque<int> &arr){
    int n = arr.size();
    if (n <= 1)
        return;
    if(n <= 20){
        insertionSortDeque(arr, 0, n - 1);
        return;
    }
    //Similar implementation as vector but using deque
    std::deque<std::pair<int, int> > pairs;
    bool hasOdd = (n % 2 == 1);
    int oddElement = hasOdd ? arr[n - 1] : 0;

    for(int i = 0; i < n - (hasOdd ? 1 : 0); i += 2){
        if(arr[i] > arr[i + 1]){
            pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
        } else {
            pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
        }
    }

    std::deque<int> largers;
    for(size_t i = 0; i < pairs.size(); ++i){
        largers.push_back(pairs[i].first);
    }
    fordJohnsonDeque(largers);

    std::deque<std::pair<int, int> > sortedPairs;
    for(size_t i = 0; i < largers.size(); ++i){
        for(size_t j = 0; j < pairs.size(); ++j){
            if(pairs[j].first == largers[i]){
                sortedPairs.push_back(pairs[j]);
                break;
            }
        }
    }

    //avoid reusing same pair index when values duplicate
    std::deque<bool> used(pairs.size(), false);
    for(size_t i = 0; i < largers.size(); ++i){
        for(size_t j = 0; j < pairs.size(); ++j){
            if(!used[j] && pairs[j].first == largers[i]){
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    //create main chain 
    std::deque<int> mainChain;
    for(size_t i = 0; i < sortedPairs.size(); ++i)
        mainChain.push_back(sortedPairs[i].first);

    //Insert smaller elements using binary search
    for(size_t i = 0; i < sortedPairs.size(); ++i){
        int pos = binarySearchDeque(mainChain, sortedPairs[i].second, 0, mainChain.size() - 1);
        mainChain.insert(mainChain.begin() + pos, sortedPairs[i].second);
    }

    //insert odd element if exists
    if(hasOdd){
        int pos = binarySearchDeque(mainChain, oddElement, 0, mainChain.size() - 1);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }
    arr = mainChain;
}

void PmergeMe::run(int argc, char **argv){
    try {
        parseInput(argc, argv);

        //display original sequence
        std::cout << "Before: ";
        for(size_t i = 0; i < vectorData.size(); ++i){
            std::cout << vectorData[i] << " ";
            if(i < vectorData.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;

        //Sort with vector structure and measure the time elapsed
        std::vector<int> vectorCopy = vectorData;
        struct timeval tv_startV, tv_endV;
        gettimeofday(&tv_startV, NULL);
        fordJohnsonVector(vectorCopy);
        gettimeofday(&tv_endV, NULL);
        double timeVector = (tv_endV.tv_sec - tv_startV.tv_sec) * 1e6 + (tv_endV.tv_usec - tv_startV.tv_usec);

        //Sort with Deque structure and measure the time elapsed
        std::deque<int> dequeCopy = dequeData;
        struct timeval tv_startD, tv_endD;
        gettimeofday(&tv_startD, NULL);
        fordJohnsonDeque(dequeCopy);
        gettimeofday(&tv_endD, NULL);
        double timeDeque = (tv_endD.tv_sec - tv_startD.tv_sec) * 1e6 + (tv_endD.tv_usec - tv_startD.tv_usec);

        //Display sorted sequence
        std::cout << "After vector: ";
        for(size_t i = 0; i < vectorCopy.size(); ++i){
            std::cout << vectorCopy[i] << " ";
            if(i < vectorCopy.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;

        //Display sorted sequence
        std::cout << "After deque: ";
        for(size_t i = 0; i < dequeCopy.size(); ++i){
            std::cout << dequeCopy[i] << " ";
            if(i < dequeCopy.size() - 1)
                std::cout << " ";
        }
        std::cout << std::endl;

        
        //Display time taken
        std::cout << std::fixed << std::setprecision(8);
        std::cout << "Time to process a range of " << vectorData.size() << " elements with std::vector : " << timeVector << " us" << std::endl;
        std::cout << "Time to process a range of " << dequeData.size() << " elements with std::deque : " << timeDeque << " us" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}