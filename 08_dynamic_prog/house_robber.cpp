/*
You are a robber planning to rob houses along a street. Each house has a certain amount of treasure stashed, the only constraint stopping you from robbing every one of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given a list of integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight without alerting the police.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <unordered_map>

int _rob(std::vector<int> &nums, int pos, std::unordered_map<int, int> &mem) {
    
    if (pos >= nums.size()) {     
        return 0;
    }
    
    //Check if result was previously in dictionary
    if (mem.find(pos) != mem.end()) {      
        return mem[pos];
    }
    
    //Calculate value with and without the current position.
    int with = nums[pos] + _rob(nums, pos + 2, mem);
    int without = _rob(nums, pos + 1, mem);
    
    int res = std::max(with, without);
    //Save result in dictionary
    mem[pos] = res;
    
    return res;
}

int rob(std::vector<int> nums) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::unordered_map<int, int> mem;
        
    return _rob(nums, 0, mem);
}

template<typename T>
std::vector<T> get_words() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream ss{line};
    std::vector<T> v;
    std::copy(std::istream_iterator<T>{ss}, std::istream_iterator<T>{}, std::back_inserter(v));
    return v;
}

int main() {
    std::vector<int> nums = get_words<int>();
    int res = rob(nums);
    std::cout << res << '\n';
}
