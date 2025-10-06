/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMeV2.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luifer <luifer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 22:18:17 by luifer            #+#    #+#             */
/*   Updated: 2025/10/06 01:02:14 by luifer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// ------------------- VECTOR VERSION OF FORD-JOHNSON SORT -------------------
//Generate Jacobsthal numbers up to a certain limit
std::vector<int> generateJacobsthalNumbers(int limit){
    std::vector<int> J;
    J.push_back(0); //J(0)
    if (limit < 1) return J;
    J.push_back(1); //J(1)
    while(true){
        int next = J[J.size() - 1] + 2 * J[J.size() - 2];
        if(next > limit) break;
        J.push_back(next);
    }
    return J;
}

//Build jacobsthal insertion order for m elements
std::vector<size_t> buildJacobsthalInsertionOrder(size_t m){
    std::vector<size_t> order;
    if (m == 0) return order;
    if (m == 1) {
        order.push_back(0);
        return order;
    }
    std::vector<int> J = generateJacobsthalNumbers(static_cast<int>(m));
    std::vector<char> used(m, 0);
    for(int k = static_cast<int>(J.size()) - 1; k >= 1; --k){
        int step = J[k];
        if(step <= 0) continue;
        for(int idx = step - 1; idx < static_cast<int>(m); idx += step){
            if(!used[idx]){
                order.push_back(static_cast<size_t>(idx));
                used[idx] = 1;
            }
        }
    }
    for(size_t i = 0; i < m; ++i){
        if(!used[i])
            order.push_back(i);
    }
    return order;
}

//Binary search for insertion position in vector
int binarySearchVectorV2(const std::vector<int> &arr, int target, int left, int right){
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

//Ford-Johnson sort implementation for vector
void FordJohnsonSort(std::vector<int> &arr){
    int n = arr.size();
    if (n <= 1)
        return;
    //Pairing phase
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
    //Recursive sort of larger elements
    std::vector<int> largers;
    for(size_t i = 0; i < pairs.size(); ++i){
        largers.push_back(pairs[i].first);
    }
    FordJohnsonSort(largers);
    
    //Reconstruct pairs according to sorted larger elements
    std::vector<std::pair<int, int> > sortedPairs;
    std::vector<bool> used(pairs.size(), false);
    for(size_t i = 0; i < largers.size(); ++i){
        for(size_t j = 0; j < pairs.size(); ++j){
            if(!used[j] && pairs[j].first == largers[i]){
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }

    //Build main chain with larger elements
    std::vector<int> mainChain;
    for(size_t i = 0; i < sortedPairs.size(); ++i)
        mainChain.push_back(sortedPairs[i].first);
    
        //Insert smaller elements using Jacobsthal order
    size_t m = sortedPairs.size();
    std::vector<size_t> insertionOrder = buildJacobsthalInsertionOrder(m);
    for(size_t idx = 0; idx < insertionOrder.size(); ++idx){
        size_t pairIdx = insertionOrder[idx];
        int smallValue = sortedPairs[pairIdx].second;
        int pos = binarySearchVectorV2(mainChain, smallValue, 0, static_cast<int>(mainChain.size()) - 1);
        mainChain.insert(mainChain.begin() + pos, smallValue);
    }
    
    // Insert odd element if exists
    if (hasOdd){
        int pos = binarySearchVectorV2(mainChain, oddElement, 0, static_cast<int>(mainChain.size()) - 1);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }
    arr = mainChain;
}

// ------------------- DEQUE VERSION OF FORD-JOHNSON SORT -------------------
int binarySearchDequeV2(const std::deque<int> &arr, int target, int left, int right){
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}

void FordJohnsonSortDeque(std::deque<int> &arr){
    int n = arr.size();
    if(n <= 1) return;
    //Pairing phase
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
    //Recursive sort of larger elements
    std::deque<int> largers;
    for(size_t i = 0; i < pairs.size(); ++i){
        largers.push_back(pairs[i].first);
    }
    FordJohnsonSortDeque(largers);
    //Reconstruct sorted pairs according to sorted larger elements
    std::deque<std::pair<int, int> > sortedPairs;
    std::deque<bool> used(pairs.size(), false);
    for (size_t i = 0; i < largers.size(); ++i) {
        for (size_t j = 0; j < pairs.size(); ++j) {
            if (!used[j] && pairs[j].first == largers[i]) {
                sortedPairs.push_back(pairs[j]);
                used[j] = true;
                break;
            }
        }
    }
    //Build main chain with larger elements
    std::deque<int> mainChain;
    for(size_t i = 0; i < sortedPairs.size(); ++i)
        mainChain.push_back(sortedPairs[i].first);
    //Insert smaller elements using Jacobsthal order
    size_t m = sortedPairs.size();
    std::vector<size_t> insertionOrder = buildJacobsthalInsertionOrder(m);
    for (size_t idx = 0; idx < insertionOrder.size(); ++idx) {
        size_t pairIndex = insertionOrder[idx];
        int smallValue = sortedPairs[pairIndex].second;
        int pos = binarySearchDequeV2(mainChain, smallValue, 0, static_cast<int>(mainChain.size()) - 1);
        mainChain.insert(mainChain.begin() + pos, smallValue);
    }
    // Insert odd element if exists
    if (hasOdd) {
        int pos = binarySearchDequeV2(mainChain, oddElement, 0, static_cast<int>(mainChain.size()) - 1);
        mainChain.insert(mainChain.begin() + pos, oddElement);
    }
    arr = mainChain;
}

/*
void MergeSort(std::vector<int> &arr){
    int n = arr.size();
    if(n <= 1)
        return;
    int mid = n / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

    int j = 0; //right array index
    for(int i = 0; i < n; i++){
        if(i < mid)
            left[i] = arr[i];
        else
            right[j] = arr[i];
            j++;
    }
    MergeSort(left);
    MergeSort(right);
    Merge(left, right, arr);
}

void Merge(std::vector<int> &left, std::vector<int> &right, std::vector<int> &arr){
    int leftSize = arr.size() / 2;
    int rightSize = arr.size() - leftSize;
    int i = 0, l = 0, r = 0;
    while(l < leftSize && r < rightSize){
        if(left[l] <= right[r]){
            arr[i++] = left[l++];
        }
        else{
            arr[i++] = right[r++];
        }
    }
    while(l < leftSize){
        arr[i++] = left[l++];
    }
    while(r < rightSize){
        arr[i++] = right[r++];
    }
}
*/