/*
Given an array of integers and an integer target, find a subarray that sums to target and return the start and end indices of the subarray.

Input: arr: 1 -20 -3 30 5 4 target: 7

Output: 1 4

Explanation: -20 - 3 + 30 = 7. The indices for subarray [-20,-3,30] is 1 and 4 (right exclusive).
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <unordered_map>

std::vector<int> subarray_sum_old(std::vector<int> arr, int target) {
    // WRITE YOUR BRILLIANT CODE HERE
    int fast, slow, k;  
    
    for(slow = 0; slow < arr.size(); slow++) {
    
        int sum = 0;
        for (fast = slow; fast < arr.size(); fast++) {
            
            sum+=arr[fast];
            
            if (sum == target) {
                
                return {slow, fast+1};
            }
        }
    }
    return {};
}

std::vector<int> subarray_sum(std::vector<int> arr, int target) {
    // WRITE YOUR BRILLIANT CODE HERE
    int i, j, sum;
    std::unordered_map<int, int> prefix;
    
    //Adding this to the map we are able to return the result
    //if it is found at the forward pass
    prefix[0] = 0;
    
    for(i = 0, sum = 0; i < arr.size(); i++) {
        
        sum+=arr[i];
        
        //If result is in forward pass
        /*if (sum == target) {
            return {0, i+1};
        }*/
        
        //Check if complement is in map
        int complement = sum - target;
        if (prefix.find(complement) != prefix.end()) { 
            return {prefix[complement], i+1};
        }
        
        //Add prefix to map
        prefix[sum] = i+1;  
    }
    
    return {};
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

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> arr = get_words<int>();
    int target;
    std::cin >> target;
    ignore_line();
    std::vector<int> res = subarray_sum(arr, target);
    put_words(res);
}
