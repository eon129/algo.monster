/*
Given a list of n items and their weights, find all sums that can be formed using their weights.

Input
weights: A list of items and their weights.
Output
A list of possible sums using the weights.

Examples
Example 1:
Input:

weights = [1, 3, 3, 5]
Output: [0, 1, 3, 4, 5, 6, 7, 8, 9, 11, 12]

Explanation:

We can form all sums from 0 to 12 except 2 and 10. Here is a short explanation for the sums:

0: use none of the weights
1: use item with weight 1
3: use item with weight 3
4: use weights 1 + 3 = 4
5: use item with weight 5
6: use weights 3 + 3 = 6
7: use weights 1 + 3 + 3 = 7
8: use weights 3 + 5 = 8
9: use weights 1 + 3 + 5 = 9
11: use weights 3 + 3 + 5 = 11
12: use all weights
Constraints
1 <= len(weights) <= 100
1 <= weights[i] <= 100
*/

#include <algorithm> // copy, sort
#include <iostream> // cin
#include <iterator> // back_inserter, istream_iterator
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <set>

void generate_sums(std::vector<int> &weights, std::set<int> &sums, int sum, int n) {
  if (n == 0) {
    sums.insert(sum);
    return;
  }
 
  generate_sums(weights, sums, sum, n - 1);
  generate_sums(weights, sums, sum + weights[n - 1], n - 1);
  
}

std::vector<int> brute_force(std::vector<int> &weights) {
  std::set<int> sums;
  int n = weights.size();
  generate_sums(weights, sums, 0, n);
    
  std::vector<int> ans(sums.begin(), sums.end());
  return ans;
}

void generate_sums_2(std::vector<int> &weights, std::set<int> &sums, int sum, int n, std::vector<std::vector<bool>> &memo) {
  
    //if branch already visited, avoid going there again
    if (memo[n][sum]) {
        return;
    }
    
    if (n == 0) {
        sums.insert(sum);
        return;
    }
 
    generate_sums_2(weights, sums, sum, n - 1, memo);
    generate_sums_2(weights, sums, sum + weights[n - 1], n - 1, memo);
    
    //Store already visited branch in memo
    memo[n][sum] = true; 
}

std::vector<int> top_down_memo(std::vector<int> &weights) {
    std::set<int> sums;
    int n = weights.size();
    int sum = 0;
 
    //Sum all elements
    for ( auto element : weights ) {      
        sum+= element;
    }
    
    //Create memo
    std::vector<std::vector<bool>> memo(n + 1, std::vector<bool>(sum + 1, false));
  
    generate_sums_2(weights, sums, 0, n, memo);
    
    std::vector<int> ans(sums.begin(), sums.end());
    
    return ans;
}

std::vector<int> bottom_up(std::vector<int> &weights) {
    std::set<int> sums;
    int n = weights.size();
    int sum = 0;
 
    //Sum all weights
    for ( auto element : weights ) {      
        sum+= element;
    }
    
    //Create dp matrix and fill it with false, with exception of column 0
    bool dp[n+1][sum+1];
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=sum; j++) {         
            if (j==0) {
                dp[i][j] = true;
            } else {
                dp[i][j] = false;
            }
        }   
    } 
    
    //Insert 0 which is allways a valid element in the result
    sums.insert(0);

    
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=sum; j++) { 
            
            //If result was already found, just update value in this row
            if (dp[i-1][j] == true) {              
                dp[i][j] = true;
                sums.insert(j);
                continue;
            }
            
            //Check if current sum - weight has already a correct result in the past
            if ((j - weights[i-1]) >=0 && dp[i-1][j-weights[i-1]] == true) {
                dp[i][j] = true;
                sums.insert(j);
            }
        }
    }
  
    //Convert set to vector
    std::vector<int> ans(sums.begin(), sums.end());
    
    return ans;
}

std::vector<int> knapsack_weight_only(std::vector<int> weights) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    //return brute_force(weights);
    //return top_down_memo(weights);
    return bottom_up(weights);
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
    std::vector<int> weights = get_words<int>();
    std::vector<int> res = knapsack_weight_only(weights);
    std::sort(res.begin(), res.end());
    for (int i = 0; i < res.size(); i++) {
      std::cout << res[i];
      if (i != res.size() - 1) {
        std::cout << " ";
      }
    }
    std::cout << "\n";
}
