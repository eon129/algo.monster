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
int kth_smallest(std::vector<std::vector<int>> matrix, int k) {
    // WRITE YOUR BRILLIANT CODE HERE
    std::priority_queue<int> pq;
    int n, pyramid, side, offset;
    
    n = matrix.size();
    
    for(int c=0, side = 1, pyramid=1, offset = 0; c < ((n*2) - 1); c++) {
    
        int i, j;
        for (i=0, j=pyramid-1; i < pyramid; i++, j--) {
            
            //Push elements with opposite sign to create a min heap
            pq.push(matrix[offset+(i*side)][offset+(j*side)] * -1);
        }
        
        if (c+1 >= n) {
            side = -1;
            offset = n-1;
        }
        pyramid += side; 
    }
    
    //Remove elements from the queue until k
    for(int i=1; i<k; i++) {    
        pq.pop();
    }
    
    return (pq.top() * -1);
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
    int matrix_length;
    std::cin >> matrix_length;
    ignore_line();
    std::vector<std::vector<int>> matrix;
    for (int i = 0; i < matrix_length; i++) {
        matrix.emplace_back(get_words<int>());
    }
    int k;
    std::cin >> k;
    ignore_line();
    int res = kth_smallest(matrix, k);
    std::cout << res << '\n';
}
