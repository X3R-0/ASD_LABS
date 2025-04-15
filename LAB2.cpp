#include <iostream>
#include <vector>
#include <array>
#include <string_view>
#include <algorithm>
#include <numeric>
#include <random>
#include <functional>
#include <chrono>

constexpr int DATA_COUNT = 2; 
constexpr int SHUFFLE_COUNT = 3;
constexpr int EXPERIMENT_COUNT = 10;
constexpr int ALGORITHM_COUNT = 3;

std::vector<int> generateData(int size, int shuffleType) {
    std::vector<int> data(size);
    std::iota(data.begin(), data.end(), 0);

    switch (shuffleType) {
        case 0: break;
        case 1: std::shuffle(data.begin(), data.end(), std::mt19937{std::random_device{}()}); break;
        case 2: std::reverse(data.begin(), data.end()); break;
    }
    return data;
}

bool linearSearch(const std::vector<int>& data, int target) {
    return std::find(data.begin(), data.end(), target) != data.end();
}

bool binarySearch(const std::vector<int>& data, int target) {
    return std::binary_search(data.begin(), data.end(), target);
}

struct TreeNode {
    int value;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
    TreeNode(int v) : value(v) {}
};

class BST {
public:
    TreeNode* root = nullptr;

    void insert(int value) {
        root = insertRec(root, value);
    }

    bool search(int value) {
        return searchRec(root, value);
    }

private:
    TreeNode* insertRec(TreeNode* node, int value) {
        if (!node) return new TreeNode(value);
        if (value < node->value) node->left = insertRec(node->left, value);
        else node->right = insertRec(node->right, value);
        return node;
    }

    bool searchRec(TreeNode* node, int value) {
        if (!node) return false;
        if (value == node->value) return true;
        return searchRec(value < node->value ? node->left : node->right, value);
    }
};

int main() {
    std::array<std::string_view, DATA_COUNT> dataSizes = { "small", "medium" };
    std::array<int, DATA_COUNT> dataLengths = { 1000, 10000 };

    std::array<std::string_view, SHUFFLE_COUNT> shuffleTypes = {
        "Sorted", "Shuffled", "Reversed"
    };

    std::array<std::function<bool(const std::vector<int>&, int)>, ALGORITHM_COUNT> algorithms = {
        linearSearch,
        binarySearch,
        [](const std::vector<int>& data, int target) {
            BST tree;
            for (int val : data) tree.insert(val);
            return tree.search(target);
        }
    };

    std::array<std::string_view, ALGORITHM_COUNT> algorithmNames = {
        "Linear Search",
        "Binary Search",
        "Binary Search Tree"
    };

    for (int ai = 0; ai < ALGORITHM_COUNT; ai++) {
        std::cout << "=== " << algorithmNames[ai] << " ===\n";

        for (int di = 0; di < DATA_COUNT; di++) {
            int size = dataLengths[di];
            std::cout << "Data size: " << dataSizes[di] << " (" << size << " elements)\n";

            for (int si = 0; si < SHUFFLE_COUNT; si++) {
                long long totalTime = 0;

                for (int ei = 0; ei < EXPERIMENT_COUNT; ei++) {
                    std::vector<int> data = generateData(size, si);
                    int target = data[size / 2]; // цель — средний элемент

                    auto start = std::chrono::high_resolution_clock::now();
                    algorithms[ai](data, target);
                    auto end = std::chrono::high_resolution_clock::now();

                    totalTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                }

                double avgTime = static_cast<double>(totalTime) / EXPERIMENT_COUNT;
                std::cout << "  " << shuffleTypes[si] << ": " << avgTime << " microseconds\n";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}