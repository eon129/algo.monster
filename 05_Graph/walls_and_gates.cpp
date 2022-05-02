/*
You are given an m by n grid of integers representing a map of a dungeon. In this map:

-1 represents a wall or an obstacle of some kind.
0 represents a gate out of the dungeon.
INF represents empty space.
For this question, let INF be 2^31 - 1 == 2147483647, which is the max value of the integer type in many programming languages.

Venturing into the dungeon is very dangerous, so you would like to know how close you are at each point in the dungeon to the exit. Given the map of the dungeon, return the same map, but for each empty space, that space is replaced by the number of steps it takes to reach any exit. If a space cannot reach the exit, that space remains INF.

Note that each step, you can move horizontally or vertically, but you cannot move pass a wall or an obstacle.

Input
dungeon_map: a matrix of integer representing the dungeon map.
Output
A matrix of integer representing the dungeon map with the addition of distance to an exit for each empty space.

Examples
Example 1:
Input:

dungeon_map = [
  [INF, -1, 0, INF],
  [INF, INF, INF, -1],
  [INF, -1, INF, -1],
  [0, -1, INF, INF],
]

Output: [ [3, -1, 0, 1], [2, 2, 1, -1], [1, -1, 2, -1], [0, -1, 3, 4], ]
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <deque>
#include <unordered_set>

void find_nearest_exit(std::vector<std::vector<int>> &dungeon_map,
                       std::vector<std::vector<int>> & result_map,
                       int curr_visited,
                       int i,
                       int j,
                       int max_row,
                       int max_col
                       ) {

    int level = 0;
    int delta_row[4] = {-1, 0, 1, 0};
    int delta_col[4] = {0, 1, 0, -1};
    std::deque<std::pair<int, int>> q;
    
    q.push_back(std::pair<int, int>(i, j));
    dungeon_map[i][j] = curr_visited;

    while (!q.empty()) {

        int n = q.size();
        level++;

        while (n) {

            std::pair<int, int> curr = q.back();
            q.pop_back();

            //Check for adjacent nodes
            for (int k = 0; k<4; k++) {

                int nRow = curr.first + delta_row[k];
                int nCol = curr.second + delta_col[k];

                //skip iteration if is out of boundaries
                if ((nRow) < 0 ||
                    (nRow) >= max_row ||
                    (nCol) < 0 ||
                    (nCol) >= max_col
                    ) {

                    continue;
                }
                //exit found
                if (dungeon_map[nRow][nCol] == 0) {
                    result_map[i][j] = level;
                    return;
                }
                //Not a wall or previously visited
                if (dungeon_map[nRow][nCol] != -1 &&
                    dungeon_map[nRow][nCol] != curr_visited
                    ) {

                    //set vertex as visited
                    dungeon_map[nRow][nCol] = curr_visited;

                    //push vertex to queue
                    q.push_front(std::make_pair(nRow, nCol));
                }
            }
            n--;
        }
    }    
}

std::vector<std::vector<int>> map_gate_distances1(std::vector<std::vector<int>> dungeon_map) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::vector<std::vector<int>> result_map = dungeon_map;
    int max_row = dungeon_map.size();
    int max_col = dungeon_map[0].size();
    int curr_visited = 1;
    
    for(int i=0; i<max_row; i++) {
        
        for(int j=0; j<max_col; j++, curr_visited++) {
            
            //don't check for walls or exits, skip node
            if (dungeon_map[i][j] == -1 || dungeon_map[i][j] == 0) { 
                continue;
            }
            
            find_nearest_exit(dungeon_map, result_map, curr_visited, i, j, max_row, max_col);
        }
    }
    
    return result_map;
}

std::vector<std::vector<int>> map_gate_distances(std::vector<std::vector<int>> dungeon_map) {
    // WRITE YOUR BRILLIANT CODE HERE
    int EMPTY_SPACE = 2147483647;
    int max_row = dungeon_map.size();
    int max_col = dungeon_map[0].size();
    int delta_row[4] = {-1, 0, 1, 0};
    int delta_col[4] = {0, 1, 0, -1};
    std::deque<std::pair<int, int>> q;
    
    
    for(int i=0; i<max_row; i++) {      
        for(int j=0; j<max_col; j++) {         
            if (dungeon_map[i][j] == 0) { 
                
                q.push_back(std::pair<int, int>(i, j));
            }
        }
    }
    
    //Since there is no need to do some process at every graph level,
    //We can use the 1 while approach instead of two
    while (!q.empty()) {
    
        std::pair<int, int> curr = q.back();
        q.pop_back();
        
        for (int k = 0; k<4; k++) { 
            
            int row = curr.first;
            int col = curr.second;
            int nRow = row + delta_row[k];
            int nCol = col + delta_col[k];

            //Check if node is valid and empty
            if ((nRow) >= 0 &&
                (nRow) < max_row &&
                (nCol) >= 0 &&
                (nCol) < max_col &&
                dungeon_map[nRow][nCol] == EMPTY_SPACE
                ) {

                dungeon_map[nRow][nCol] = dungeon_map[row][col] + 1;
                q.push_front(std::pair<int, int>(nRow, nCol));
            }             
        }
    }
    
    return dungeon_map;
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
    int dungeon_map_length;
    std::cin >> dungeon_map_length;
    ignore_line();
    std::vector<std::vector<int>> dungeon_map;
    for (int i = 0; i < dungeon_map_length; i++) {
        dungeon_map.emplace_back(get_words<int>());
    }
    std::vector<std::vector<int>> res = map_gate_distances(dungeon_map);
    for (const std::vector<int>& row : res) {
        put_words(row);
    }
}
