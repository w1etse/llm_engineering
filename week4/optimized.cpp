#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>

// Linear Congruential Generator
class LCG {
    uint32_t a = 1664525;
    uint32_t c = 1013904223;
    uint64_t value;
    static constexpr uint64_t m = 1ULL << 32; // Simulate 2**32 using uint64_t to avoid overflow
public:
    LCG(uint32_t seed) : value(seed) {}
    uint32_t next() {
        value = (a * value + c) % m;
        return static_cast<uint32_t>(value);
    }
};

// Maximum Subarray Sum using Kadane's Algorithm
int64_t maxSubarraySum(const std::vector<int>& nums) {
    int64_t max_sum = INT64_MIN, current_sum = 0;
    for (int x : nums) {
        current_sum += x;
        if (current_sum > max_sum) max_sum = current_sum;
        if (current_sum < 0) current_sum = 0;
    }
    return max_sum;
}

// Total Maximum Subarray Sum
int64_t totalMaxSubarraySum(int n, uint32_t initial_seed, int min_val, int max_val) {
    int64_t total_sum = 0;
    LCG lcg_gen(initial_seed);
    
    for (int run = 0; run < 20; ++run) {
        uint32_t seed = lcg_gen.next();
        LCG random_lcg(seed);
        std::vector<int> random_numbers(n);
        int range = max_val - min_val + 1;
        
        for (int i = 0; i < n; ++i) {
            random_numbers[i] = random_lcg.next() % range + min_val;
        }
        
        total_sum += maxSubarraySum(random_numbers);
    }

    return total_sum;
}

int main() {
    int n = 10000;
    uint32_t initial_seed = 42;
    int min_val = -10;
    int max_val = 10;

    auto start = std::chrono::steady_clock::now();
    int64_t result = totalMaxSubarraySum(n, initial_seed, min_val, max_val);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    
    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << elapsed_seconds.count() << " seconds" << std::endl;

    return 0;
}
