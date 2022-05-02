/*
On an infinitely large chessboard, a knight is located on [0, 0].

A knight can move in eight directions.

Given a destination coordinate [x, y], determine the minimum number of moves from [0, 0] to [x, y].
*/

#include <iostream> // cin, cout, streamsize
#include <limits> // numeric_limits
#include <unordered_set>
#include <deque>
#include <utility>

// Hash function 
struct hashFunction
{
  size_t operator()(const std::pair<int, int> &x) const
  {
    return x.first ^ x.second;
  }
};

int get_knight_shortest_path(int x, int y) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::unordered_set<std::pair<int, int>, hashFunction> visited;
    std::deque<std::pair<int, int>> q;
    int delta_row[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int delta_col[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int level = 0;
    
    q.push_back(std::pair<int, int>(0, 0));
    visited.insert(std::pair<int, int>(0, 0));
    
    //This problem has to do some process in every level, so we need to use the two while approach
    while(!q.empty()) {
        
        int n = q.size();
        level++;
        
        while (n) {
            
            std::pair<int, int> curr = q.back();
            q.pop_back();
            
            int row = curr.first;
            int col = curr.second;
            
            for (int i = 0; i<8; i++) {
                
                //A solution path has been found
                if ((row+delta_row[i]) == x && (col+delta_col[i]) == y) {
                    
                    return level;
                }

                std::pair<int, int> next((row+delta_row[i]), (col+delta_col[i]));
                //If element is not visited yet, push to queue
                //One improvement could be only to push the half of the nodes which are
                //near to the destination
                if(visited.find(next) == visited.end()) {
                    
                    visited.insert(next);
                    q.push_front(next);
                }
            }   
            n--;
        }
    }
        
    return 0;
}


void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int x;
    std::cin >> x;
    ignore_line();
    int y;
    std::cin >> y;
    ignore_line();
    int res = get_knight_shortest_path(x, y);
    std::cout << res << '\n';
}
