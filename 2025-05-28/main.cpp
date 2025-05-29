#include <iostream>
#include "Solution.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    Solution solution;

    // [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]], k = 2

    struct test_case {
        vector<vector<int>> edges1;
        vector<vector<int>> edges2;
        int k;
        vector<int> expected;
    };

    const test_case test_cases[] = {
    {
            {{0, 1}, {0, 2}, {2, 3}, {2, 4}},
            {{0, 1}, {0, 2}, {0, 3}, {2, 7}, {1, 4}, {4, 5}, {4, 6}},
            2,
            {9, 7, 9, 8, 8}
        },
    {
            {{0, 1}, {0, 2}, {0, 3}, {0, 4}},
            {{0, 1}, {1, 2}, {2, 3}},
            1,
            {6, 3, 3, 3, 3}
        },
        {
            {{0, 1}},
            {{0, 1}},
            0,
            {1, 1}
        }
    };

    for (const auto & test_case : test_cases) {
        auto result = solution.maxTargetNodes(test_case.edges1, test_case.edges2, test_case.k);
        std::cout << "Test case edges1: ";
        for (const auto & edge : test_case.edges1) {
            std::cout << "[" << edge[0] << "," << edge[1] << "] ";
        }
        std::cout << ", edges2: ";
        for (const auto & edge : test_case.edges2) {
            std::cout << "[" << edge[0] << "," << edge[1] << "] ";
        }
        std::cout << ", k: " << test_case.k << ", expected: ";
        if (result != test_case.expected) {
            std::cerr << "Test failed!" << std::endl;
            std::cerr << "Expected: ";
            for (const auto & val : test_case.expected) {
                std::cerr << val << " ";
            }
            std::cerr << ", got: ";
            for (const auto & val : result) {
                std::cerr << val << " ";
            }
            std::cerr << std::endl;
            return EXIT_FAILURE;
        }
    }
    std::cout << "All tests passed!" << std::endl;
}