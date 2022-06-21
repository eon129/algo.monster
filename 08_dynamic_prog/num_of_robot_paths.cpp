/*A robot is located at the top-left corner of a m x n grid.
The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

Example 1:
Input: m = 2, n = 3

Output: 3

Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:

Right -> Right -> Down

Right -> Down -> Right

Down -> Right -> Right

Example 2:
Input: m = 5, n = 3

Output: 15
*/

#include <iostream> // cin, cout, streamsize
#include <limits> // numeric_limits

int unique_paths(int m, int n) {
    // WRITE YOUR BRILLIANT CODE HERE
    int grid[m][n];
    
    //Calculate number of paths
    for (int r=0; r<m; r++) {
    
        for(int c=0; c<n; c++) {
            
            if (r==0 || c==0) {
                grid[r][c] = 1;
            } else {
                grid[r][c] = grid[r][c-1] + grid[r-1][c];
            }            
        }
    }
    
    return grid[m-1][n-1];
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int m;
    std::cin >> m;
    ignore_line();
    int n;
    std::cin >> n;
    ignore_line();
    int res = unique_paths(m, n);
    std::cout << res << '\n';
}
