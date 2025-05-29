#include <iostream>
#include <algorithm>
#include <vector>
#include "Solution.hpp"

// define a vector<vector<int>> as Edges for clarity
using namespace std;
using Edges = vector<vector<int>>;
using Edge = vector<int>;

const int countNodes(const Edges & edges) {
    int max = 0;
    for(const auto & edge : edges) {
        max = std::max(max, std::max(edge[0], edge[1]));
    }
    return max + 1;
}

class Tree {
    Edges adjacencyList;

public:
    int nodeCount;

    Tree(const Edges & edges) {
        nodeCount = countNodes(edges);
        adjacencyList.resize(nodeCount);
        for(const auto & edge : edges) {
            // We should check if the other node on this edge is already in the adjacency list.
            // If so, then this isn't a tree, it's a graph.
            adjacencyList[edge[0]].push_back(edge[1]);
            adjacencyList[edge[1]].push_back(edge[0]);
        }
    }

    std::string to_str(void) const {
        std::string result;
        for(int i = 0; i < adjacencyList.size(); i++) {
            result += "Node " + std::to_string(i) + ": ";
            for(const auto & adjacency : adjacencyList[i]) {
                result += std::to_string(adjacency) + " ";
            }
            result += "\n";
        }
        return result;
    }

    int countTargets(const int node, const int prevNode, const int k, const int d = 0) {
        int additionalTargets = 0;

        std::string dp = "[" + std::to_string(additionalTargets) + "] " + std::string(2 * d, ' ');

        // If k = 0, then this node and only this node is also a valid target.
        if(k == 0) {
            std::cerr << dp << "k is 0, returning 1 target." << std::endl;
            return 1;
        }

        // If we have reached the maximum depth, return the number of targets found.
        if(d == k) {
            std::cerr << dp << "Reached maximum depth " << k << " at node " << node << ". Returning " << additionalTargets << " targets." << std::endl;

            return additionalTargets;
        }

        // Start node is a valid target, because a node is always target to itself.
        if(node == prevNode) {
            additionalTargets = 1;
            std::cerr << dp << "Starting node " << node << " is a target." << std::endl;
        }

        // Count the number of targets in the current node's adjacency list.
        for(auto & adjacency : adjacencyList[node]) {
            if (adjacency == prevNode) continue; // skip the previous node
            std::cerr << dp << "Node " << adjacency << " is a target." << std::endl;
            additionalTargets++;
        }

        std::cerr << dp << "Node " << node << " has " << additionalTargets << " targets at depth " << d << "." << std::endl;
        for(auto & adjacency : adjacencyList[node]) {
            // leaf node
            if(additionalTargets == 0) {
                std::cerr << dp << "Node " << node << " is a leaf node, no additional targets." << std::endl;
                break;
            }
            if(adjacency == prevNode) {
                std::cerr << dp << "Node " << adjacency << " is the previous node, skipping." << std::endl;
                continue; // skip the previous node
            }
            std::cerr << dp << "Node " << node << " has an adjacency to " << adjacency << ", going deeper." << std::endl;
            additionalTargets += countTargets(adjacency, node, k, d + 1);
            std::cerr << dp << "After going deeper, node " << node << " has " << additionalTargets << " targets." << std::endl;
        }
        return additionalTargets;
    }

    vector<int> targetCounts(const int k) {
        int x = 0;
        // Special case: if k == 0, then each node is a target to itself.
        if(k == 0) x = 1;
        vector<int> nodeTargetCounts(nodeCount, x);
        if(k == 0) return nodeTargetCounts;
        for(int node = 0; node < nodeCount; node++) {
            std::cerr << "Counting targets for node " << node << std::endl;
            nodeTargetCounts[node] = countTargets(node, node, k);
            std::cerr << "Node " << node << " has " << nodeTargetCounts[node] << " targets." << std::endl;
        }

        return nodeTargetCounts;
    }
};

const vector<int> Solution::maxTargetNodes(const vector<vector<int>>& edges1, const vector<vector<int>>& edges2, const int k) {
    int m, n;
    m = countNodes(edges1);
    n = countNodes(edges2);
    std::cerr << "m: " << m << ", n: " << n << std::endl;
    vector<int> targets1(m, 0);
    vector<int> targets2(n, 0);
    vector<int> answer(m, 0);

    // Special case: if k == 0, then each node is a target to itself.
    if(k == 0) {
        vector<int> answer(m, 1);
        return answer;
    }

    // compute targets1(k) for each edges1[i]
    Tree tree1(edges1);
        // by doing DFS <= k
    targets1 = tree1.targetCounts(k);

    std::cerr << "targets1: ";
    for(const auto & target : targets1) {
        std::cerr << target << " ";
    }
    std::cerr << std::endl;

    // Each of these nodes will be connected over an edge to a node in edges1, so
    // compute targets2(k - 1) for each edges2[j].
    Tree tree2(edges2);
    targets2 = tree2.targetCounts(k - 1);

    std::cerr << "targets2: ";
    for(const auto & target : targets2) {
        std::cerr << target << " ";
    }
    std::cerr << std::endl;

    // for each target1[i]
    for(int i = 0; i < m; i++) {
        // for each target2[j]
        for(int j = 0; j < n; j++) {
            // answer[i] = max of target1[i] + target2[j]
            answer[i] = std::max(answer[i], targets1[i] + targets2[j]);
        }
    }

    return answer;
}
