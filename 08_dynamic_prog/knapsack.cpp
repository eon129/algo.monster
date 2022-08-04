/*
We want to discuss a classic dynamic programming problem, which is 0-1 knapsack. Given a series of objects with a weight and a value and a knapsack that can carry a set amount of weight, what is the maximum object value we can put in our knapsack without exceeding the weight constraint?

Input
weights: an array of integers that denote the weights of objects
values: an array of integers that denote the values of objects
max_weight: the maximum weight capacity of the knapsack
Output
the maximum value in the knapsack

Examples
Example 1:
Input:

weights = [3, 4, 7]
values = [4, 5, 8]
max_weight = 7
Output: 9

Explanation:

We have a knapsack of max limit 7 with 3 objects of weight-value pairs of [3,4], [4,5], [7,8], then the maximal value we can achieve is using the first 2 objects to obtain value 4 + 5 = 9.

The other possibilities would all be only 1 object in our knapsack, which would only yield values 4, 5, and 9.
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector

int recursive_1(std::vector<int> weights, std::vector<int> values, int max_weight) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int max = 0;
    
    for (int i=0; i < weights.size(); i++) {
    
        if (weights[i] < max_weight) {
            //Copy vectors
            std::vector<int> w_temp = weights;
            std::vector<int> v_temp = values;
            w_temp.erase(w_temp.begin()+i);
            v_temp.erase(v_temp.begin()+i);
            //Iterate over all posibilities
            int temp = recursive_1(
                w_temp,
                v_temp,
                max_weight - weights[i]) + values[i];
            
            //Store global max value
            max = (temp>max) ? temp : max;
            
        } else if (weights[i] == max_weight) {
            //If this condition is reached, only one element fits into the knapsack
            max = (values[i]>max) ? values[i] : max;
        } else {
            //Do nothing
        }
    }
    return max;
}

int recursive_2(std::vector<int> &weights, std::vector<int> &values, int max_weight, int curr_idx, std::vector<std::vector<int>> &memo) {
    
    if (memo[curr_idx][max_weight] != -1) {
        return memo[curr_idx][max_weight];
    }
    
    if (curr_idx == weights.size() || max_weight == 0) {
        memo[curr_idx][max_weight] = 0;
        return memo[curr_idx][max_weight];
    }
     
    if ( max_weight - weights[curr_idx] < 0) {
        
        memo[curr_idx][max_weight] = recursive_2(weights, values, max_weight, curr_idx+1, memo);
        
        return memo[curr_idx][max_weight];
    }
    
    memo[curr_idx][max_weight] = std::max(recursive_2(weights, values, max_weight-weights[curr_idx], curr_idx+1, memo) + values[curr_idx],
                              recursive_2(weights, values, max_weight, curr_idx+1, memo));
    
    return memo[curr_idx][max_weight];
}

int knapsack(std::vector<int> weights, std::vector<int> values, int max_weight) {
    // WRITE YOUR BRILLIANT CODE HERE

    //return recursive_1(weights, values, max_weight);
    
    std::vector<std::vector<int>> memo(weights.size() + 1, std::vector<int>(max_weight + 1, -1));
    return recursive_2(weights, values, max_weight, 0, memo);
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
    std::vector<int> weights = get_words<int>();
    std::vector<int> values = get_words<int>();
    int max_weight;
    std::cin >> max_weight;
    ignore_line();
    int res = knapsack(weights, values, max_weight);
    std::cout << res << '\n';
}
