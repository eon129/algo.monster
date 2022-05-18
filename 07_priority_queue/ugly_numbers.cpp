/*
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers whose prime factors only include 2, 3, 5.

Example 1:
Input:n = 10
Output: 12
Explanation: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note:
1 is typically treated as an ugly number.
n does not exceed 1690.
*/

#include <iostream> // cin, cout, streamsize
#include <limits> // numeric_limits
#include <queue>
#include <unordered_set>

int nth_ugly_number(int n) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    std::priority_queue<int> pq;
    std::unordered_set<int> seen;
    std::vector<int> u_numbers = {2, 3, 5};
    
    //Push first ugly number;
    pq.push(-1);
    seen.insert(1);
    
    for(int i=0; i<n-1; i++) {
    
        int curr = -pq.top();
        pq.pop();
        
        for(int j=0; j<u_numbers.size(); j++) {
            
            int next = curr * u_numbers[j];
            if (seen.find(next) == seen.end()) {
                
                pq.push(-next);
                seen.insert(next);
            }
        }
    }
    
    return -pq.top();
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int n;
    std::cin >> n;
    ignore_line();
    int res = nth_ugly_number(n);
    std::cout << res << '\n';
}
