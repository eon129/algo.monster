/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not necessarily the kth distinct element.

Example 1:
Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:
Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.
*/


#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <queue>

int find_kth_largest_old(std::vector<int> nums, int k) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::priority_queue<int> pq;
    
    //Put the numbers in a heap
    //It would be better if we can "make a heap" from the array since complexity is O(n)
    for(int i=0; i<nums.size(); i++) {
    
        pq.push(nums[i]);
    }
    
    //pop k-1 numbers from pq
    for(int i=1; i<k; i++) {
        pq.pop();
    }
    
    return pq.top();
}


int find_kth_largest(std::vector<int> nums, int k) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //make a heap from vector
    std::make_heap(nums.begin(), nums.end());
    
    //pop k-1 numbers from heapifyed vector
    for(int i=1; i<k; i++) {
        pop_heap(nums.begin(), nums.end());
        nums.pop_back();
    }
    
    return nums.front();
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

int main() {
    std::vector<int> nums = get_words<int>();
    int k;
    std::cin >> k;
    ignore_line();
    int res = find_kth_largest(nums, k);
    std::cout << res << '\n';
}