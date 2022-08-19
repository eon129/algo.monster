/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Example 1:
Input: candidates = [2,3,6,7], target = 7

Output: [[2,2,3],[7]]

Explanation: 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.

7 is a candidate, and 7 = 7.

These are the only two combinations.

Example 2:
Input: candidates = [2,3,5], target = 8

Output: [[2,2,2,2],[2,3,3],[3,5]]

Example 3:
Input: candidates = [2], target = 1

Output: []

Example 4:
Input: candidates = [1], target = 1

Output: [[1]]

Example 5:
Input: candidates = [1], target = 2

Output: [[1, 1]]

Constrains:

1 <= candidates.length <= 30
1 <= candidates[i] <= 200
All elements of candidates are distinct.
1 <= target <= 500
*/

#include <algorithm> // copy
#include <iostream> // cin, cout, streamsize
#include <iterator> // back_inserter, istream_iterator, ostream_iterator, prev
#include <limits> // numeric_limits
#include <sstream> // istringstream
#include <string> // getline, string
#include <vector> // vector
#include <unordered_set>

void combination_sum_1(std::vector<int> &candidates, int target, std::vector<int> path, std::vector<std::vector<int>> &res, std::unordered_set<int> &visited) {
    
    if (target == 0) {
        
        //Calculate key for visited set
        int mul=1;
        for (auto elem : path) {
            mul*= elem;
        }
        
        //Current combination has not been added yet
        if (visited.find(mul) == visited.end()) {
            visited.insert(mul);
            
            std::vector<int> list(path);
            res.emplace_back(list);
        }
        return;
    }
    
    for (int i=0; i<candidates.size(); i++) {
        
        int nextTarget = target - candidates[i];
        
        if (nextTarget >=0 ) {
            path.push_back(candidates[i]);
            combination_sum_1(candidates, nextTarget, path, res, visited);
            path.pop_back();
        }
    }
}

void combination_sum_2(std::vector<int> &candidates, int target, std::vector<int> path,std::vector<std::vector<int>> &res, int start) {
    
    if (target == 0) {
        
        std::vector<int> list(path);
        res.emplace_back(list);
        return;
    }
    
    for (int i=start; i<candidates.size(); i++) {
        
        int nextTarget = target - candidates[i];
        
        if (nextTarget >=0 ) {
            path.push_back(candidates[i]);
            combination_sum_2(candidates, nextTarget, path, res, i);
            path.pop_back();
        }
    }
}
    
std::vector<std::vector<int>> combination_sum(std::vector<int> candidates, int target) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    /*std::vector<std::vector<int>> res;
    std::unordered_set<int> visited;
    combination_sum_1(candidates, target, {}, res, visited);*/
    
    std::vector<std::vector<int>> res;
    combination_sum_2(candidates, target, {}, res, 0);
    
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

template<typename T>
void put_words(const std::vector<T>& v) {
    if (!v.empty()) {
        std::copy(v.begin(), std::prev(v.end()), std::ostream_iterator<T>{std::cout, " "});
        std::cout << v.back();
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> candidates = get_words<int>();
    int target;
    std::cin >> target;
    ignore_line();
    std::vector<std::vector<int>> res = combination_sum(candidates, target);
    for (const std::vector<int>& row : res) {
        put_words(row);
    }
}
