/*
Write a program to find the n-th ugly number.

Ugly numbers are positive numbers that are divisible by either a, b, or c.

Since the number can be too large, return the actual answer modulo 10^9 + 7

Example 1:
Input:n = 10, a = 2, b = 3, c = 5
Output: 14
Explanation: 2, 3, 4, 5, 6, 8, 9, 10, 12, 14 is the sequence of the first 10 ugly numbers.
Example 2:
Input:n = 2, a = 3, b = 4, c = 5
Output: 4
Explanation: 3, 4 is the sequence of the first 2 ugly numbers.
Constraints
1 <= n, a, b, c <= 10^9
1 <= a * b * c <= 10^18
*/

#include <iostream> // cin, cout, streamsize
#include <limits> // numeric_limits

int getTotalUglyNumbersIn(int n, int a, int b, int c)
{
    int total;
    
    total = (n/a + n/b + n/c) - (n/(a*b) + n/(a*c) + n/(b*c)) + (n/(a*b*c));
    
    //std::cout << "n: " << n << " tun: " << total << std::endl;
    
    return total;
}

int nth_ugly_number(int n, int a, int b, int c) {
    // WRITE YOUR BRILLIANT CODE HERE
    
    int min;
    
    //Get min value
    min = a;
    min = b < min ? b : min;
    min = c < min ? c : min;
    
    int l = n;
    int r = min * n;
    int boundary = 0;
    
    while (l <= r) {
        
        int m = (l+r)/2;
        
        if (getTotalUglyNumbersIn(m, a, b, c) < n) {
            
            l = m + 1;
        } else {
            
            r = m - 1;
            boundary = m;
        }
    }
    
    return boundary % (1<<9 + 7);
}

void ignore_line() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    int n;
    std::cin >> n;
    ignore_line();
    int a;
    std::cin >> a;
    ignore_line();
    int b;
    std::cin >> b;
    ignore_line();
    int c;
    std::cin >> c;
    ignore_line();
    int res = nth_ugly_number(n, a, b, c);
    std::cout << res << '\n';
}
