/*
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
Input: coins = [1, 2, 5], amount = 11

Output: 3

Explanation:
11 = 5 + 5 + 1, 3 total coins

Example 2:
Input: coins = [3], amount = 1

Output: -1
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

const int INT_MAX = 2147483647;

int _coin_change(std::vector<int> &coins, int amount, int coin_num, int &global_min, std::string path) {
    
    int local_min;
    
    std::cout  << path << ", ";
    
    //Avoid to continue searching for more combinations if there is already a beter solution
    if((coin_num + 1) >= global_min) {
        
        return global_min;
    }
    
    //Try every coin combination
    for(int i=0; i < coins.size(); i++) {
        
        int new_amount = amount - coins[i];
        
        //A solution has been found
        if (new_amount == 0) {
            std::cout << "#C: " << coin_num+1 << "# ";
            local_min = coin_num + 1;
            
        } else if (new_amount > 0 ) {
            std::string newP = path;
            newP += std::to_string(coins[i]);
            newP +="-";
            local_min = _coin_change(coins, new_amount, ++coin_num, global_min, newP);
        }
        
        global_min = (local_min < global_min) ? local_min : global_min;
    }
    
    //global_min = (local_min < global_min) ? local_min : global_min;
       
    return global_min;
}

int coin_change(std::vector<int> coins, int amount) {
    // WRITE YOUR BRILLIANT CODE HERE
    int global_min = INT_MAX;
    
    int result = _coin_change(coins, amount, 0, global_min, "");
    
    return (result == INT_MAX) ? -1 : result;
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
    std::vector<int> coins = get_words<int>();
    int amount;
    std::cin >> amount;
    ignore_line();
    int res = coin_change(coins, amount);
    std::cout << res << '\n';
}
