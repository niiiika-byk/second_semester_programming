#include <iostream>
#include <numeric>
#include <cmath>

#include "set.hpp"

void find_min_difference_partition(Set<int>& input_set) {
    // int sum = 0;
    // for (int i : S) {
    //     sum += i;
    // }

    // int target_sum = sum / 2;

    // std::vector<bool> dp(target_sum + 1, false);
    // dp[0] = true;

    // for (int i : S) {
    //     for (int j = target_sum; j >= i; --j) {
    //         if (dp[j - i]) {
    //             dp[j] = true;
    //         }
    //     }
    // }

    // int max_sum = 0;
    // for (int i = target_sum; i >= 0; --i) {
    //     if (dp[i]) {
    //         max_sum = i;
    //         break;
    //     }
    // }

    // std::vector<int> subset1, subset2;
    // for (int i : S) {
    //     if (max_sum >= i && dp[max_sum - i]) {
    //         subset1.push_back(i);
    //         max_sum -= i;
    //     } else {
    //         subset2.push_back(i);
    //     }
    // }

    // std::cout << "Subset 1: ";
    // for (int i : subset1) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Subset 2: ";
    // for (int i : subset2) {
    //     std::cout << i << " ";
    // }
    // std::cout << std::endl;

    // std::cout << "Difference: " << abs(sum - 2 * max_sum) << std::endl;
}