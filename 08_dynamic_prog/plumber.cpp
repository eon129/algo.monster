/*
Our favourite plumber is on his way to save the princess located in the castle. The castle is represented by a 2-D grid that contains obstacles (denoted by -1) and coins (denoted by 1). Empty squares in the castle are denoted by 0.

Our plumber will always start at the first row in the grid and the princess will always be at the last row in the grid. On the plumber's way to save the princess (reach any position in the last row), what is the maximal number of coins that can be obtained?

Restrictions:

The plumber can only move down, right, and left, but never up.
The plumber cannot move through the obstacles.
If the plumber cannot reach the last row, return -1.

Input
grid: Grid containing the castle layout
Output
Integer representing the maximal number of coins that can be obtained, return -1 if the plumber cannot reach the last row.

Examples
Example 1:
Input:

grid = [[0, 0], [1, 1]]
Output: 2

Explanation:

Both of the coins can be collected on the way to the princess.

Example 2:
Input:

grid = [[0, 0, 1], [0, 0, -1], [0, 0, 0]]
Output: 1

Explanation:

After getting the coin in the first row, the plumber can move to the left and down to avoid the obstacle.

Example 3:
Input:

grid = [[1,0,-1,1,0,1],[1,-1,1,-1,1,-1],[0,0,-1,-1,1,1]]
Output: 5

Explanation:

See solution.

Constraints
2 <= rows, columns <= 2000
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int plumber(std::vector<std::vector<int>> grid) {
    // WRITE YOUR BRILLIANT CODE HERE
    int n_col = grid[0].size();
    int n_row = grid.size();
    int res_grid[n_row][n_col];
    int max_global = 0;
    int r, c;
    
    for(r=0; r<n_row; r++) {
        
        //First pass
        int sum = 0;
        int prev = 0;
        for(c=0; c<n_col; c++) {
            
            //Row 0  doesn't have previous value
            if (r == 0) {
                prev = 0;
            } else if (res_grid[r-1][c] != -1){
                prev = (res_grid[r-1][c]>prev) ? res_grid[r-1][c] : prev;
            }
            
            //A barrier has been found
            if(grid[r][c] == -1) {
                //Add prev value to previous column if it exist
                if (c > 0 && res_grid[r][c-1] !=-1) {
                    res_grid[r][c-1]+= prev;
                }
                //Save barrier in result and reset flags
                res_grid[r][c] = -1;
                sum = 0;
                prev = 0;
            } else {
                //Sum until a barrier is found
                sum += grid[r][c];
                res_grid[r][c] = sum;
            }
        }
        
        //In case there is no barrier at the end of the row
        if (res_grid[r][c-1] !=-1) {
            res_grid[r][c-1]+= prev;
        }
        
        //Second pass, now backwards
        int max = -1;
        for(int c=n_col-1; c>=0; c--) {
            
            //max = res_grid[r][c] > max ? res_grid[r][c] : max;
            
            //Barrier is found, reset max flag
            if(res_grid[r][c] == -1) {
                max = -1;
            } else {
                //Only save first value (left to rigt) which is the max for each section
                if(max == -1) {
                    max = res_grid[r][c];
                }
                //Update all values in section with max
                res_grid[r][c] = max;
                
                //Save max global only at the last row
                if ( r == n_row-1) {
                    max_global =  res_grid[r][c] > max_global ? res_grid[r][c] : max_global;
                }
            }
        }
    }
    
    /*for(int r=0; r<n_row; r++) {
       
        for(int c=0; c<n_col; c++) {
            
            std::cout << res_grid[r][c] << ", ";
        }
        std::cout << std::endl;
    }*/
    
    return max_global;
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
    int res = plumber(grid);
    std::cout << res << '\n';
}
