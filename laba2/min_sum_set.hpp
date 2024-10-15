#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

#include "set.hpp"

void find_min_difference_partition(Set<int, 1>& input_set) {
    Set_node<int>* elements[1000];  //указетли на узлы сета
    int count = 0;

    input_set.get_all_elements(elements, count);

    int total_sum = 0;
    for (int i = 0; i < count; ++i) {
        total_sum += elements[i]->get_key();
    }

    int target = total_sum / 2;
    bool dp[1001] = {false};
    dp[0] = true;

    for (int i = 0; i < count; ++i) {
        int num = elements[i]->get_key();
        for (int j = target; j >= num; --j) {
            dp[j] = dp[j] || dp[j - num];
        }
    }

    int sum1;
    for (sum1 = target; sum1 >= 0; --sum1) {
        if (dp[sum1]) break;
    }

    int sum2 = total_sum - sum1;
    int difference = std::abs(sum2 - sum1);

    Set<int, 1000> subset1, subset2;
    int w = sum1;

    for (int i = count - 1; i >= 0; --i) {
        int num = elements[i]->get_key();
        if (w >= num && dp[w - num]) {
            subset1.add(num);
            w -= num;
        } else {
            subset2.add(num);
        }
    }

    std::cout << "Difference between sums: " << difference << std::endl;

    std::cout << "Subset 1: ";
    subset1.display();

    std::cout << "Subset 2: ";
    subset2.display();
}