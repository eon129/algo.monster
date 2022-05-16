/*
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:
Input:
matrix = [
  [ 1,  5,  9],
  [10, 11, 13],
  [12, 13, 15]
],
k = 8,
Output: 13
Note:
You may assume k is always valid, 1 ≤ k ≤ n^2. You may also assume that 1 <= n <= 1000.
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