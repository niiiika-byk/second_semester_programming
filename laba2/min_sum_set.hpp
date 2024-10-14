#include <iostream>
#include <numeric>
#include <cmath>
#include <vector>

#include "set.hpp"

void find_min_difference_partition(std::vector<int>& input_set) {
    int sum = 0;
    for (int i : input_set) {
        sum += i;
    }

    int target_sum = sum / 2;

    std::vector<bool> dp(target_sum + 1, false);
    dp[0] = true;

    for (int i : input_set) {
        for (int j = target_sum; j >= i; --j) {
            if (dp[j - i]) {
                dp[j] = true;
            }
        }
    }

    int max_sum = 0;
    for (int i = 0; i <= target_sum; ++i) {
        if (dp[i]) {
            max_sum = i;
        }
    }

    int diff = sum - 2 * max_sum;

    std::cout << "Разница между суммами: " << diff << std::endl;

    // Вывод подмножеств
    std::vector<int> subset1, subset2;
    for (int i : input_set) {
        if (dp[max_sum - i]) {
            subset1.push_back(i);
            max_sum -= i;
        } else {
            subset2.push_back(i);
        }
    }

    std::cout << "Подмножество 1: ";
    for (int i : subset1) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "Подмножество 2: ";
    for (int i : subset2) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}