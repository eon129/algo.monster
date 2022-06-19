/*
Suppose we have a m x n matrix filled with non-negative integers, find a path from top left corner to bottom right corner. which minimizes the sum of all numbers along its path.

Note: Movements can only be either down or right at any point in time.

Example:
Input:
  [
    [1,3,1],
    [1,5,1],
    [4,2,1]
  ]
Output:
7
Explanation:
Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int min_path_sum(std::vector<std::vector<int>> grid) {
    // WRITE YOUR BRILLIANT CODE HERE
    int INT_MAX = 2147483647;
    int n_row = grid.size();
    int n_col = grid[0].size();
    int result[n_row][n_col];
    
    for(int r=0; r<n_row; r++) {
        
        for(int c=0; c<n_col; c++) {
            
            if(r == 0 && c == 0) {
                result[r][c] = grid[r][c]; 
            } else if(r == 0 && c!= 0) {
                result[r][c] = grid[r][c] + result[r][c-1]; 
            } else if(c == 0 && r!= 0) {
                result[r][c] = grid[r][c] + result[r-1][c]; 
            } else {          
                result[r][c] = grid[r][c] + std::min(result[r-1][c], result[r][c-1]);
            }            
        }  
    }
    
    return result[n_row-1][n_col-1];
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
    int grid_length;
    std::cin >> grid_length;
    ignore_line();
    std::vector<std::vector<int>> grid;
    for (int i = 0; i < grid_length; i++) {
        grid.emplace_back(get_words<int>());
    }
    int res = min_path_sum(grid);
    std::cout << res << '\n';
}
