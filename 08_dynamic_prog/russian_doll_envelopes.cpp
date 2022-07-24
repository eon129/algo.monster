/*
Russian Doll Envelopes
You have a list of envelopes, who each have an integer width and height. An envelope can fit into another envelope if and only if the first envelope's width and height is smaller than the other envelope's width and height (you cannot rotate either envelopes).

Given a list of envelopes, find the maximum number of envelopes that you can fit inside one another like a Russian Doll.

Input
envelopes: a list of integer pairings representing the envelopes. For each pair, the first integer represents the width, and the second integer represents the height.
Output
The number representing the max envelope layers.

Examples
Example 1:
Input:

envelopes = [[5, 4], [6, 4], [6, 7], [2, 3]]
Output: 3

Explanation:

[2, 3] goes inside [5, 4], which goes inside [6, 7]

Constraints
1 <= len(envelopes) <= 5000
1 <= width[i], height[i] <= 10^4
*/


#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <queue>

int max_layers(std::vector<std::vector<int>> envelopes) 
{
    
    //First sort vector. N log(N)
    std::sort(envelopes.begin(), envelopes.end(), [](std::vector<int> a, std::vector<int> b) {
        return a[0] + a[1] < b[0] + b[1];
    });
    
    std::vector<int> dp;
    
    int max_global = 0;
    
    for (int i = 0; i < envelopes.size(); i++) {
        
        int max_previous_layers = 0;
        for (int j = 0; j < i; j++) {
            if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1]) {
                max_previous_layers = std::max(max_previous_layers, dp[j]);
            }
        }
        
        //Add current envelope to the result
        dp.push_back(max_previous_layers + 1);
        max_global = (max_previous_layers+1) > max_global ? (max_previous_layers+1) : max_global;
    }
    
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
    int envelopes_length;
    std::cin >> envelopes_length;
    ignore_line();
    std::vector<std::vector<int>> envelopes;
    for (int i = 0; i < envelopes_length; i++) {
        envelopes.emplace_back(get_words<int>());
    }
    int res = max_layers(envelopes);
    std::cout << res << '\n';
}
