/*
Input
nums: the integer sequence
Output
the length of longest subsequence

Examples
Example 1:
Input:

nums = [50, 3, 10, 7, 40, 80]
Output: 4

Explanation:

The longest subsequence is [3, 7, 40, 80] which has length 4.

Example 2:
Input:

nums = [1, 2, 4, 3]
Output: 3

Explanation:

Both [1, 2, 4] and [1, 2, 3] are longest subsequences which have length 3.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <unordered_map>

int _longest_sub_len(std::vector<int> &nums, int pos, std::unordered_map<int, int> &dic) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //Return value if already in mem
    if (dic.find(pos) != dic.end()) {
        return dic[pos];
    }
    
    int max = 0;
    for(int i=pos-1; i>=0; i--) {
    
        if (nums[pos] > nums[i]) {     
            int local_max = _longest_sub_len(nums, i, dic);
            max = (local_max > max) ? local_max : max;
        }
    }
    
    //Save local max to dictionary
    dic[pos] = max+1;
    
    return max+1;
}

int longest_sub_len(std::vector<int> nums) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::unordered_map<int, int> dic;
    
    if (nums.size() == 0) {
        return 0;
    }
    
    dic[0] = 1;
    return _longest_sub_len(nums, nums.size()-1, dic);
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
    int res = longest_sub_len(nums);
    std::cout << res << '\n';
}
