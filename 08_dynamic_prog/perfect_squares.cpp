/*
Given a number that is less than 10^5 determine the smallest amount of perfect squares needed to sum to a particular number? The same number can be used multiple times.

Examples
Example 1:
Input: 12
Output: 3
Explanation:
12 = 4 + 4 + 4

Example 2:
Input: 13
Output: 2
Explanation:
13 = 4 + 9
*/

#include <iostream> // cin, cout, streamsize
#include <limits> // numeric_limits
#include <unordered_map>
#include <math.h>

int perfect_squares_top_down(int n, std::unordered_map<int, int> &map) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    if (map.find(n) != map.end()) {
        return map[n];
    }
    
    double n_sqrt = sqrt(n);
    
    if (ceil(n_sqrt) == floor(n_sqrt)) {
        
        map[n] = 1;
        return 1;
    }
    
    
    int curr_floor = floor(n_sqrt);
    int min = 2147483647;
    
    while (curr_floor > 0) {
        
        int local_min = perfect_squares_top_down(n-(curr_floor * curr_floor), map);
        min = (local_min < min) ? local_min : min;
        
        curr_floor--;
    }
    
    map[n] = min + 1;
    
    return map[n];
}

int perfect_squares_bottom_up(int n) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int dp[n+1];
    
    //Zero is not used
    dp[0] = 0;
    //Prefill 1 value
    dp[1] = 1;
    
    for (int i=2; i<=n; i++) {
        
        //Check if i is not perfect sqr root
        double s = sqrt(i);
        if (ceil(s) != floor(s)) {
        
            int curr_square = floor(s);
            int min = 2147483647;
            
            //Get the min value using previous results
            while (curr_square > 0) {
                
                min = (dp[i-(curr_square*curr_square)] < min) ? dp[i-(curr_square*curr_square)] : min;
                curr_square--;
            }
            
            dp[i] = min + 1;
        } else {
            //Save value 1 since is perfect sqr root
            dp[i] = 1;
        }
    }
    
    return dp[n];
}

int perfect_squares(int n) {
    // WRITE YOUR BRILLIANT CODE HERE
    //std::unordered_map<int, int> map;
    //return perfect_squares_top_down(n, map);
    
    return perfect_squares_bottom_up(n);
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int n;
    std::cin >> n;
    ignore_line();
    int res = perfect_squares(n);
    std::cout << res << '\n';
}