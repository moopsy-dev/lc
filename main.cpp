#include <iostream>
#include <stdlib.h>
#include "2025-05-27.hpp"

int main(int argc, char *argv[]) {
    Solution solution;

    struct test_case {
        int n;
        int m;
        int expected;
    };
    test_case test_cases[] = {
        {10, 3, 19},
        {5, 6, 15},
        {5, 1, -15}

    };

    for (const auto & test_case : test_cases) {
        auto result = solution.differenceOfSums(test_case.n, test_case.m);
        std::cout << "Test case n: " << test_case.n << ", m: " << test_case.m << ", expected: " << test_case.expected
                  << ", got: " << result << std::endl;
        if (result != test_case.expected) {
            std::cerr << "Test failed!" << std::endl;
            return EXIT_FAILURE;
        }
    }
    std::cout << "All tests passed!" << std::endl;
}