/*
Interval DP is another sub-type of the dynamic programming technique that deals with ranges or intervals. In general, the final answer to interval DP problems will be the answer to the entire range [1, n], where subproblems are computed by finding the answer to all possible ranges, [l, r] where l <= r. Alternate names for interval DP are left-right DP or L-R DP.

Interval DP is one of the more challenging types of dynamic programming problems. They might be too difficult for the real interviews. We are including them here for completeness. Don't sweat if you can't get it the firs time.

Coin Game
There are n coins in a straight line. The ith coin has a value of coins[i]. You play this game with a friend alternating turns, starting with you, remove one coin from one end of the line and add that coin's value to your score.

If your friend plays perfectly in such a way that maximizes their score, what is your maximum possible score?

Input
coins: A list of the coins.
Output
Your maximum possible score, provided that you go first and your friend plays perfectly.

Examples
Example 1:
Input:

coins = [4, 4, 9, 4]
Output: 13

Explanation:

The coins start like this:

4, 4, 9, 4

You always go first, so you take the 4 from the left side:

4, 9, 4

Your friend takes any of the 4s (it doesn't matter)

9, 4

Now you take the 9, and your friend takes the remaining 4.

Your score in this case, is 4 + 9 = 13.

Constraints
1 <= len(coins) <= 1000
1 <= coins[i] <= 5 * 10^5
*/

#include <algorithm> // copy
#include <iostream> // cin, cout
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <numeric>


int max_score_brute_force(std::vector<int> &coins, int l, int r) {

    if (l == r) {
        return coins[l];
    }
    
    int sum = 0;
    for (int i=l; i<=r; i++) {
        sum+= coins[i];
    }
    
    return std::max(sum - max_score_brute_force(coins, l+1, r), sum - max_score_brute_force(coins, l, r-1));
}

int max_score_memo(std::vector<std::vector<int>> &dp, std::vector<int> &coins, int l, int r) {
    
    if (dp[l][r] != 0) {
        return dp[l][r];
    }
    
    //coins are already precomputed with prefix sum
    int sum = coins[r] - coins[l - 1];

    if (l == r) {
        dp[l][r] = sum;
    } else {
       dp[l][r] = std::max(sum - max_score_memo(dp, coins, l+1, r), sum - max_score_memo(dp, coins, l, r-1));
    }
        
    return dp[l][r];
}

int coin_game(std::vector<int> coins) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //return max_score_brute_force(coins, 0, coins.size()-1);
    int n = coins.size();
    
    //Precompute prefix sum
    std::vector<int> prefix_sum(n + 1, 0); // precompute prefix sum
    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + coins[i - 1];
    }
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));
    
    //Instead of passing 0 to n-1, we pass 1 to n, since it already precomputed
    return max_score_memo(dp, prefix_sum, 1, n);
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

int main() {
    std::vector<int> coins = get_words<int>();
    int res = coin_game(coins);
    std::cout << res << '\n';
}