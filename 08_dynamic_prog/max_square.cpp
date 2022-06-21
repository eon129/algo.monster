/*
Given a binary matrix, find out the largest size square sub-matrix with all 1's and return its area.

Input
matrix: a binary matrix
Output
the area of the largest square in the input matrix

Examples
Example 1:
Input:

matrix = 
[[1, 0, 1, 0, 0],
 [1, 0, 1, 1, 1],
 [1, 1, 1, 1, 0],
 [1, 0, 0, 1, 0]]
Output: 4

Explanation:

The largest square is of size 2x2 and area 4.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector


int maximal_square(std::vector<std::vector<int>> matrix) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int n_col = matrix[0].size();
    int n_row = matrix.size();
    int res_grid[n_row][n_col];
    int max = 0;
    
    for(int r = 0; r<n_row; r++) {      
        for(int c = 0; c<n_col; c++) {
            
            if (r == 0 || c == 0) {         
                res_grid[r][c] =  matrix[r][c];    
            } else {
                
                if (matrix[r][c] == 0) {
                    res_grid[r][c] = 0;
                } else {
                    res_grid[r][c] = 1 + std::min(res_grid[r-1][c], std::min(res_grid[r][c-1], res_grid[r-1][c-1]));
                }
            } 
            //Check for max value
            max = res_grid[r][c] > max ? res_grid[r][c] : max;
        }    
    }    
     
    return max*max;
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
    int res = maximal_square(matrix);
    std::cout << res << '\n';
}