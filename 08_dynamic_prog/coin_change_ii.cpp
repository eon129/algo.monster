/*
Coin Change II
You are given coins of different denominations and a total amount of money amount. Write a function to compute the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.

Input
coins: A list of the coins and their denominations.
amount: The target amount
Output
The number of combinations that make up that amount.

Examples
Example 1:
Input:

coins = [1, 2, 5]
amount = 5
Output: 4

Explanation:

There are four ways to make up the amount:

5 = 5
5 = 2 + 2 + 1
5 = 2 + 1 + 1 + 1
5 = 1 + 1 + 1 + 1 + 1
Example 2:
Input:

coins = [2]
amount = 3
Output: 0

Explanation:

The amount of 3 cannot be made up with just coins of 2.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int top_down(std::vector<int> &coins, int amount, std::vector<std::vector<int>> &memo, int start) {
    
    int res = 0;
    
    //Invalid branch
    if (amount < 0) {
        return 0;
    }
    
    //Branch already visited
    if ( memo[start][amount] != -1) {
        return memo[start][amount];
    }
    
    //Solution found
    if (amount == 0) {
        return 1;
    }
    
    
    for (int i = start; i < coins.size(); i++) {
        
        res+= top_down(coins, amount-coins[i], memo, i);
    }
    
    memo[start][amount] = res;
    
    return res;
}

int coin_game(std::vector<int> coins, int amount) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int res;
    
    std::vector<std::vector<int>> memo(coins.size()+1, std::vector<int>(amount+1, -1));
    res = top_down(coins, amount, memo, 0);
    
    return res;
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
    int res = coin_game(coins, amount);
    std::cout << res << '\n';
}
