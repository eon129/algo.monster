/*
Given a 2-dimensional matrix of values with 0 and 1, count the number of islands of 1. An island consists of all value 1 cells and is surrounded by either an edge or all 0 cells. A cell can only be adjacent to each other horizontally or vertically, not diagonally.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>
#include <utility>

void exploreIsland1(std::vector<std::vector<int>> &grid, int i, int j) {

    int delta_row[4] = {-1, 0, 1, 0};
    int delta_col[4] = {0, 1, 0, -1};
    int row_size = grid.size();
    int col_size = (grid[0]).size();
    std::deque<std::pair<int, int>> q;

    q.push_back(std::make_pair(i, j));
    
    grid[i][j] = -1;
    
    while (!q.empty()) {
        
        int n = q.size();
        
        while (n) {
            
            std::pair<int, int> curr = q.back();
            q.pop_back();
            
            int row = curr.first;
            int col = curr.second;
    
            //iterate over neighbors
            for (int i=0; i<4 ;i++) {
                
                int nRow = row+delta_row[i];
                int nCol = col+delta_col[i];

                if((nRow) >=0 &&
                   (nRow) < row_size &&
                   (nCol) >=0 &&
                   (nCol) < col_size &&
                   grid[nRow][nCol] == 1) {
                    
                    //set vertex as visited
                    grid[nRow][nCol] = -1;
                    
                    //push vertex to queue
                    q.push_front(std::make_pair(nRow, nCol));
                }
            }          
            n--;
        }
    } 
}

void exploreIsland(std::vector<std::vector<int>> &grid, int i, int j) {

    int delta_row[4] = {-1, 0, 1, 0};
    int delta_col[4] = {0, 1, 0, -1};
    int row_size = grid.size();
    int col_size = (grid[0]).size();
    std::deque<std::pair<int, int>> q;

    q.push_back(std::make_pair(i, j));
    
    grid[i][j] = -1;
    
    while (!q.empty()) {
  
        std::pair<int, int> curr = q.back();
        q.pop_back();
            
        int row = curr.first;
        int col = curr.second;
    
        //iterate over neighbors
        for (int i=0; i<4 ;i++) {
                
            int nRow = row+delta_row[i];
            int nCol = col+delta_col[i];

            if((nRow) >=0 &&
               (nRow) < row_size &&
               (nCol) >=0 &&
               (nCol) < col_size &&
               grid[nRow][nCol] == 1) {
                    
                //set vertex as visited
                grid[nRow][nCol] = -1;
                    
                //push vertex to queue
                q.push_front(std::make_pair(nRow, nCol));
            }
        }
    } 
}

int count_number_of_islands(std::vector<std::vector<int>> grid) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int row_size = grid.size();
    int col_size = (grid[0]).size();
    int nIsland = 0;
    
    for (int i=0; i<row_size; i++) {
        
        for (int j=0; j<col_size; j++) {
        
            if (grid[i][j] == 1) {
                exploreIsland(grid, i, j);
                nIsland++;
            }
        }
    }
    
    return nIsland;
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
    int res = count_number_of_islands(grid);
    std::cout << res << '\n';
}
